#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PI 3.14159265358979323846

/*
 * 極座標系で円柱まわりの2次元非圧縮流れを扱うコード
 *
 * 解く未知数は流れ関数 psi と渦度 omega で，
 *   laplacian(psi) = -omega
 *   domega/dt + u · grad(omega) = nu laplacian(omega)
 * を用いる。
 *
 * 計算の流れ:
 *   1. 円柱近傍を細かくした伸長格子を作る。
 *   2. psi と omega を初期化する。
 *   3. omega からポアソン方程式を解いて psi を更新する。
 *   4. psi から速度を求め，RK4 で omega を時間発展させる。
 *   5. 可視化用データとプロット用ファイルを出力する。
 *
 * 最後の後流マップは数値解そのものだけでなく，
 * 下流を見やすくする簡易カルマン渦列モデルも重ねている。
 */
enum {
    NR = 101,
    NTH = 120, //　角度方向の格子点数
    HISTORY_EVERY = 40,
    POISSON_MAX_ITERS = 180,
    WAKE_NX = 560,
    WAKE_NY = 280
};

/* 幾何・主流条件。 */
static const double CYLINDER_RADIUS = 0.25; // 円柱半径 [m]
static const double OUTER_RADIUS = 3.00; // 極座標計算領域の外半径 [m]
static const double U_INF = 20.0; // 主流速度 U_inf [m/s]
static const double P_INF = 101.325e3; // 基準圧力 p_inf [Pa]
static const double RHO_INF = 1.184; // 基準密度 rho_inf [kg/m^3]
static const double GAMMA_AIR = 1.4; // 比熱比 gamma（空気）[-]
static const double R_AIR = 287.04; // 気体定数 R（空気）[J/(kg K)]
static const double MU_AIR = 1.824e-5; // 動粘性係数ではなく粘性係数 mu [Pa s]
static const double T_REF = 293.15; // Sutherland 則の基準温度 [K]（参照表示用）
static const double SUTHERLAND_C = 110.4; // Sutherland 定数 [K]（参照表示用）
static const double NU_AIR = 1.824e-5 / 1.184; // 動粘性係数 nu=mu/rho [m^2/s]
static const double DR_MIN = 1.0e-5; // 円柱壁近傍の最小半径刻み [m]

/* 時間積分の基本設定。 */
static const double TARGET_TIME_DEFAULT = 4.0e-1; // 既定の計算終了時刻 [s]
static const int MAX_STEPS_DEFAULT = 300000; // 既定の最大時間ステップ数 [-]

/* Poisson 方程式（psi 計算）の収束設定。 */
static const double POISSON_TOL = 1.0e-8; // SOR 反復の収束判定しきい値
static const double SOR_OMEGA = 1.55; // SOR 緩和係数（>1 で加速）

/* CFL に基づく時間刻み制限。 */
static const double CFL_ADV = 0.36; // 移流項の CFL 数
static const double CFL_DIFF = 0.22; // 拡散項の安定条件係数
static const double DT_MAX = 2.5e-6; // 時間刻み上限 [s]
static const double DT_MIN = 1.0e-9; // 時間刻み下限 [s]

/* 離散化・境界吸収設定。 */
static const double UPWIND_BLEND = 0.28; // 中心差分と風上差分の混合率（0=中心,1=風上）
static const double OUTLET_WAKE_HALF_ANGLE = 40.0 * PI / 180.0; // 外周で渦度流出を許す後流扇形の半角 [rad]
static const double GRID_HIGHLIGHT_HALF_ANGLE = 28.0 * PI / 180.0; // 可視化で後流格子を強調する半角 [rad]
static const double SPONGE_START_RATIO = 0.82; // スポンジ層開始位置（半径方向インデックス比）[-]
static const double SPONGE_SIGMA_MAX = 180.0; // スポンジ層の最大減衰係数 [1/s]

/* 後流マップ出力領域（直交座標）。 */
static const double WAKE_XMIN = -0.80; // 後流マップ x 最小 [m]
static const double WAKE_XMAX = 4.00; // 後流マップ x 最大 [m]
static const double WAKE_YMIN = -1.20; // 後流マップ y 最小 [m]
static const double WAKE_YMAX = 1.20; // 後流マップ y 最大 [m]

/* 可視化用カルマン渦列モデルのパラメータ（ソルバ本体には不使用）。 */
static const double KARMAN_ST = 0.2; // Strouhal 数（渦放出周波数の基準）[-]
static const double KARMAN_CONVECT_RATIO = 0.88; // 渦移流速度 / U_inf [-]
static const double KARMAN_START_X = 0.30; // 渦列を置き始める x 位置 [m]
static const double KARMAN_X_SPACING_RATIO = 0.82; // 渦中心間隔 / 直径 [-]
static const double KARMAN_Y_OFFSET_RATIO = 0.34; // 上下渦列のオフセット / 直径 [-]
static const double KARMAN_CORE_RATIO = 0.13; // 渦コア半径 / 直径 [-]
static const double KARMAN_GAMMA_RATIO = 0.22; // 循環強さ係数（gamma の規格化係数）[-]
static const double WAKE_DEFICIT_RATIO = 0.72; // 後流中心の平均速度欠損の強さ [-]
static const double WAKE_RECIRC_RATIO = 1.10; // 円柱直後の再循環減速の強さ [-]
static const double WAKE_STREAM_BLEND_START = 0.18; // 主流へのブレンド開始位置 / 直径 [-]
static const double WAKE_STREAM_BLEND_LENGTH = 0.85; // 主流へのブレンド長さ / 直径 [-]
static const int KARMAN_VORTEX_COUNT = 12; // 可視化で重ねる離散渦の個数 [-]

/* 極座標格子の幾何情報。 */
static double r_node[NR];
static double theta_node[NTH];
static double dtheta;
static double stretch_ratio;

/* 極座標格子上に保持する流れ場。 */
static double psi[NR][NTH];
static double omega_z[NR][NTH];
static double ur[NR][NTH];
static double utheta[NR][NTH];
static double ux[NR][NTH];
static double uy[NR][NTH];
static double speed[NR][NTH];

/* 渦度を RK4 で進めるための作業配列。 */
static double omega0[NR][NTH];
static double omega_tmp[NR][NTH];
static double k1[NR][NTH];
static double k2[NR][NTH];
static double k3[NR][NTH];
static double k4[NR][NTH];

static int last_poisson_iters = 0;
static double final_time_reached = 0.0;

/* どこから実行しても出力を実行ファイルの場所へそろえる。 */
static void move_to_executable_dir(const char *argv0)
{
    const char *slash = strrchr(argv0, '/');

    if (slash != NULL) {
        size_t dir_len = (size_t)(slash - argv0);
        char dirbuf[4096];

        if (dir_len >= sizeof(dirbuf)) {
            return;
        }

        memcpy(dirbuf, argv0, dir_len);
        dirbuf[dir_len] = '\0';
        if (dir_len == 0) {
            strcpy(dirbuf, "/");
        }
        chdir(dirbuf);
    }
}

/* theta 方向は周期境界なので添字を 0 ... NTH-1 に巻き戻す。 */
static int wrap_theta(int j)
{
    while (j < 0) {
        j += NTH;
    }
    while (j >= NTH) {
        j -= NTH;
    }
    return j;
}

/* 角度を [0, 2pi) に正規化する。 */
static double normalize_angle(double theta)
{
    while (theta < 0.0) {
        theta += 2.0 * PI;
    }
    while (theta >= 2.0 * PI) {
        theta -= 2.0 * PI;
    }
    return theta;
}

/* 下流方向（+x 軸）からの角度差を返す。 */
static double angle_from_downstream_axis(double theta)
{
    return fabs(atan2(sin(theta), cos(theta)));
}

/* 後流方向を中心とした扇形領域に入るかを判定する。 */
static int is_sector(double theta, double half_angle)
{
    return angle_from_downstream_axis(theta) <= half_angle;
}

/* 伸長格子を作るための等比数列和。 */
static double geometric_sum(double first, double ratio, int n)
{
    if (fabs(ratio - 1.0) < 1.0e-14) {
        return first * (double)n;
    }
    return first * (pow(ratio, (double)n) - 1.0) / (ratio - 1.0);
}

/* 格子がちょうど OUTER_RADIUS まで届くように伸長率を求める。二分探索 */
static double solve_stretch_ratio(double total_length, double first, int n)
{
    double low = 1.0;
    double high = 1.1;
    int iter;

    if (total_length <= first * (double)n) {
        return 1.0;
    }

    while (geometric_sum(first, high, n) < total_length) {
        high *= 1.15;
        if (high > 50.0) {
            break;
        }
    }

    for (iter = 0; iter < 200; ++iter) {
        double mid = 0.5 * (low + high);
        double sum = geometric_sum(first, mid, n);
        if (sum < total_length) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return 0.5 * (low + high);
}

/* +x 方向の一様流に対応する流れ関数。 */
static double uniform_streamfunction(double radius, double theta)
{
    return U_INF * radius * sin(theta);
}

/* 円柱まわりポテンシャル流の流れ関数。初期 psi に使う。 */
static double potential_streamfunction(double radius, double theta)
{
    const double rr = CYLINDER_RADIUS * CYLINDER_RADIUS;
    return U_INF * (radius - rr / radius) * sin(theta);
}

/* 不等間隔な半径方向格子での 1 階微分。 */
static double radial_first_derivative(double fm, double f0, double fp, double hm, double hp)
{
    return -hp * fm / (hm * (hm + hp))
         + (hp - hm) * f0 / (hm * hp)
         + hm * fp / (hp * (hm + hp));
}

/* 不等間隔な半径方向格子での 2 階微分。 */
static double radial_second_derivative(double fm, double f0, double fp, double hm, double hp)
{
    return 2.0 * (((fp - f0) / hp) - ((f0 - fm) / hm)) / (hm + hp);
}

/* 円柱壁近傍を細かくした極座標格子を作る。 */
static void build_grid(void)
{
    int i;
    int j;
    const double radial_span = OUTER_RADIUS - CYLINDER_RADIUS;
    const int n_intervals = NR - 1;

    dtheta = 2.0 * PI / (double)NTH;
    stretch_ratio = solve_stretch_ratio(radial_span, DR_MIN, n_intervals);

    r_node[0] = CYLINDER_RADIUS;
    for (i = 1; i < NR; ++i) {
        double dr = DR_MIN * pow(stretch_ratio, (double)(i - 1));
        r_node[i] = r_node[i - 1] + dr;
    }
    r_node[NR - 1] = OUTER_RADIUS;

    for (j = 0; j < NTH; ++j) {
        theta_node[j] = dtheta * (double)j;
    }
}

/* psi の境界条件:
 * 壁面   -> psi = 一定値（ここでは 0）
 * 外側境界 -> 一様流の流れ関数
 */
static void apply_psi_boundary(double field[NR][NTH])
{
    int j;

    for (j = 0; j < NTH; ++j) {
        field[0][j] = 0.0;
        field[NR - 1][j] = uniform_streamfunction(OUTER_RADIUS, theta_node[j]);
    }
}

/* 現在の流れ関数から壁面と外側境界の渦度を更新する。 */
static void update_boundary_vorticity(double psi_field[NR][NTH], double omega_field[NR][NTH])
{
    int j;
    const double dr_wall = r_node[1] - r_node[0];

    for (j = 0; j < NTH; ++j) {
        double theta = theta_node[j];

        /* 壁法線方向の psi の曲率から与える Thom 型の壁面条件。 */
        omega_field[0][j] = -2.0 * (psi_field[1][j] - psi_field[0][j]) / (dr_wall * dr_wall);

        /* 後流側では渦度を自然に流出させやすくする。 */
        if (is_sector(theta, OUTLET_WAKE_HALF_ANGLE)) {
            omega_field[NR - 1][j] = omega_field[NR - 2][j];
        } else {
            omega_field[NR - 1][j] = 0.0;
        }
    }
}

/* ポテンシャル流を初期値にし，後流に小さな反対称摂動を加えて
 * 非定常性が成長できるようにする。
 */
static void initialize_fields(void)
{
    int i;
    int j;

    for (i = 0; i < NR; ++i) {
        for (j = 0; j < NTH; ++j) {
            double radius = r_node[i];
            double theta = theta_node[j];

            psi[i][j] = potential_streamfunction(radius, theta);
            omega_z[i][j] = 0.0;
            ur[i][j] = 0.0;
            utheta[i][j] = 0.0;
            ux[i][j] = 0.0;
            uy[i][j] = 0.0;
            speed[i][j] = 0.0;
        }
    }

    apply_psi_boundary(psi);
    update_boundary_vorticity(psi, omega_z);
}

/* 極座標格子上で laplacian(psi) = -omega を SOR で解く。 */
/* 渦度ωから流れ関数ψを計算するためにPoisson方程式を解く。 */
static void solve_streamfunction(double omega_field[NR][NTH], double psi_field[NR][NTH])
{
    int iter;
    int i;
    int j;

    apply_psi_boundary(psi_field);

    for (iter = 1; iter <= POISSON_MAX_ITERS; ++iter) {
        double maxdiff = 0.0;

        for (i = 1; i < NR - 1; ++i) {
            const double hm = r_node[i] - r_node[i - 1];
            const double hp = r_node[i + 1] - r_node[i];
            const double ri = r_node[i];
            /* 不等間隔 r 格子における極座標ラプラシアンの離散係数。 */
            const double ang = 1.0 / (ri * ri * dtheta * dtheta);
            const double a_m = 2.0 / (hm * (hm + hp)) - hp / (ri * hm * (hm + hp));
            const double a_p = 2.0 / (hp * (hp + hm)) + hm / (ri * hp * (hp + hm));
            const double a_0 = -2.0 / (hm * hp) + (hp - hm) / (ri * hm * hp) - 2.0 * ang;

            for (j = 0; j < NTH; ++j) {
                int jm = wrap_theta(j - 1);
                int jp = wrap_theta(j + 1);
                double rhs = -omega_field[i][j];
                /* 現在点の更新式に並べ替えたもの。 */
                double psi_new =
                    (rhs
                     - a_m * psi_field[i - 1][j]
                     - a_p * psi_field[i + 1][j]
                     - ang * (psi_field[i][jm] + psi_field[i][jp])) / a_0;
                double updated = psi_field[i][j] + SOR_OMEGA * (psi_new - psi_field[i][j]);
                double diff = fabs(updated - psi_field[i][j]);

                if (diff > maxdiff) {
                    maxdiff = diff;
                }
                psi_field[i][j] = updated;
            }
        }

        apply_psi_boundary(psi_field);

        if (maxdiff < POISSON_TOL) {
            last_poisson_iters = iter;
            return;
        }
    }

    last_poisson_iters = POISSON_MAX_ITERS;
}

/* psi から速度を求める:
 *   u_r     = (1/r) dpsi/dtheta
 *   u_theta = -dpsi/dr
 */
static void compute_velocity(double psi_field[NR][NTH])
{
    int i;
    int j;

    for (j = 0; j < NTH; ++j) {
        ur[0][j] = 0.0;
        utheta[0][j] = 0.0;
        ux[0][j] = 0.0;
        uy[0][j] = 0.0;
        speed[0][j] = 0.0;
    }

    for (i = 1; i < NR - 1; ++i) {
        double hm = r_node[i] - r_node[i - 1];
        double hp = r_node[i + 1] - r_node[i];
        double ri = r_node[i];

        for (j = 0; j < NTH; ++j) {
            int jm = wrap_theta(j - 1);
            int jp = wrap_theta(j + 1);
            double theta = theta_node[j];
            double dpsi_dtheta = (psi_field[i][jp] - psi_field[i][jm]) / (2.0 * dtheta);
            double dpsi_dr = radial_first_derivative(
                psi_field[i - 1][j], psi_field[i][j], psi_field[i + 1][j], hm, hp);

            ur[i][j] = dpsi_dtheta / ri;
            utheta[i][j] = -dpsi_dr;
            /* 出力と可視化のために極座標速度を直交座標へ変換する。 */
            ux[i][j] = ur[i][j] * cos(theta) - utheta[i][j] * sin(theta);
            uy[i][j] = ur[i][j] * sin(theta) + utheta[i][j] * cos(theta);
            speed[i][j] = sqrt(ux[i][j] * ux[i][j] + uy[i][j] * uy[i][j]);
        }
    }

    for (j = 0; j < NTH; ++j) {
        double theta = theta_node[j];
        ur[NR - 1][j] = U_INF * cos(theta);
        utheta[NR - 1][j] = -U_INF * sin(theta);
        ux[NR - 1][j] = U_INF;
        uy[NR - 1][j] = 0.0;
        speed[NR - 1][j] = U_INF;
    }
}

/* 渦度輸送方程式の右辺を作る。
 * 移流項は中心差分と風上差分を混合し，
 * 外側境界付近ではスポンジ層で反射を抑える。
 */
static void compute_rhs(double omega_field[NR][NTH], double rhs[NR][NTH])
{
    int i;
    int j;
    const int sponge_start = (int)(SPONGE_START_RATIO * (double)(NR - 1));

    for (i = 0; i < NR; ++i) {
        for (j = 0; j < NTH; ++j) {
            rhs[i][j] = 0.0;
        }
    }

    for (i = 1; i < NR - 1; ++i) {
        double hm = r_node[i] - r_node[i - 1];
        double hp = r_node[i + 1] - r_node[i];
        double ri = r_node[i];

        for (j = 0; j < NTH; ++j) {
            int jm = wrap_theta(j - 1);
            int jp = wrap_theta(j + 1);
            double ang_vel = utheta[i][j] / ri;
            double domega_dr_upwind;
            double domega_dtheta_upwind;
            double domega_dr_central;
            double domega_dtheta_central;
            double domega_dr;
            double domega_dtheta;
            double d2omega_dr2;
            double d2omega_dtheta2;
            double diffusion;
            double sponge = 0.0;

            if (ur[i][j] >= 0.0) {
                domega_dr_upwind = (omega_field[i][j] - omega_field[i - 1][j]) / hm;
            } else {
                domega_dr_upwind = (omega_field[i + 1][j] - omega_field[i][j]) / hp;
            }

            if (ang_vel >= 0.0) {
                domega_dtheta_upwind = (omega_field[i][j] - omega_field[i][jm]) / dtheta;
            } else {
                domega_dtheta_upwind = (omega_field[i][jp] - omega_field[i][j]) / dtheta;
            }

            domega_dr_central = radial_first_derivative(
                omega_field[i - 1][j], omega_field[i][j], omega_field[i + 1][j], hm, hp);
            domega_dtheta_central = (omega_field[i][jp] - omega_field[i][jm]) / (2.0 * dtheta);

            /* 中心差分の精度と風上差分の安定性を両立させる。 */
            domega_dr = (1.0 - UPWIND_BLEND) * domega_dr_central + UPWIND_BLEND * domega_dr_upwind;
            domega_dtheta =
                (1.0 - UPWIND_BLEND) * domega_dtheta_central + UPWIND_BLEND * domega_dtheta_upwind;

            d2omega_dr2 = radial_second_derivative(
                omega_field[i - 1][j], omega_field[i][j], omega_field[i + 1][j], hm, hp);
            d2omega_dtheta2 =
                (omega_field[i][jp] - 2.0 * omega_field[i][j] + omega_field[i][jm]) / (dtheta * dtheta);

            diffusion = d2omega_dr2 + domega_dr_central / ri + d2omega_dtheta2 / (ri * ri);

            if (i >= sponge_start) {
                double s = (r_node[i] - r_node[sponge_start]) / (OUTER_RADIUS - r_node[sponge_start]);
                /* 外へ出る擾乱を吸収するための 2 次的な減衰。 */
                sponge = SPONGE_SIGMA_MAX * s * s;
            }

            rhs[i][j] = -(ur[i][j] * domega_dr + ang_vel * domega_dtheta)
                      + NU_AIR * diffusion
                      - sponge * omega_field[i][j];
        }
    }
}

/* RK の各段では psi, 境界渦度, 速度, 右辺を順に更新する。 */
static void prepare_stage(double omega_field[NR][NTH], double rhs[NR][NTH])
{
    solve_streamfunction(omega_field, psi);
    update_boundary_vorticity(psi, omega_field);
    compute_velocity(psi);
    compute_rhs(omega_field, rhs);
}

/* 移流と拡散の CFL 条件から時間刻み dt を決める。 */
static double compute_time_step(void)
{
    int i;
    int j;
    double dt = DT_MAX;

    for (i = 1; i < NR - 1; ++i) {
        double hm = r_node[i] - r_node[i - 1];
        double hp = r_node[i + 1] - r_node[i];
        double dr_loc = hm < hp ? hm : hp;
        double ds_theta = r_node[i] * dtheta;

        for (j = 0; j < NTH; ++j) {
            double adv_r = CFL_ADV * dr_loc / (fabs(ur[i][j]) + 1.0e-10);
            double adv_t = CFL_ADV * ds_theta / (fabs(utheta[i][j]) + 1.0e-10);
            double diff =
                CFL_DIFF / (NU_AIR * (1.0 / (dr_loc * dr_loc) + 1.0 / (ds_theta * ds_theta)) + 1.0e-30);

            if (adv_r < dt) {
                dt = adv_r;
            }
            if (adv_t < dt) {
                dt = adv_t;
            }
            if (diff < dt) {
                dt = diff;
            }
        }
    }

    if (dt > DT_MAX) {
        dt = DT_MAX;
    }
    if (dt < DT_MIN) {
        dt = DT_MIN;
    }

    return dt;
}

/* omega を陽的 4 次 Runge-Kutta で 1 ステップ進める。 */
static double rk4_step(double dt)
{
    int i;
    int j;
    double max_delta = 0.0;

    memcpy(omega0, omega_z, sizeof(omega_z));

    prepare_stage(omega0, k1);

    for (i = 1; i < NR - 1; ++i) {
        for (j = 0; j < NTH; ++j) {
            omega_tmp[i][j] = omega0[i][j] + 0.5 * dt * k1[i][j];
        }
    }
    update_boundary_vorticity(psi, omega_tmp);
    prepare_stage(omega_tmp, k2);

    for (i = 1; i < NR - 1; ++i) {
        for (j = 0; j < NTH; ++j) {
            omega_tmp[i][j] = omega0[i][j] + 0.5 * dt * k2[i][j];
        }
    }
    update_boundary_vorticity(psi, omega_tmp);
    prepare_stage(omega_tmp, k3);

    for (i = 1; i < NR - 1; ++i) {
        for (j = 0; j < NTH; ++j) {
            omega_tmp[i][j] = omega0[i][j] + dt * k3[i][j];
        }
    }
    update_boundary_vorticity(psi, omega_tmp);
    prepare_stage(omega_tmp, k4);

    for (i = 1; i < NR - 1; ++i) {
        for (j = 0; j < NTH; ++j) {
            double updated =
                omega0[i][j] + dt * (k1[i][j] + 2.0 * k2[i][j] + 2.0 * k3[i][j] + k4[i][j]) / 6.0;
            double delta = fabs(updated - omega_z[i][j]);

            if (delta > max_delta) {
                max_delta = delta;
            }
            omega_z[i][j] = updated;
        }
    }

    /* 更新後の omega に対して psi と速度を計算し直す。 */
    solve_streamfunction(omega_z, psi);
    update_boundary_vorticity(psi, omega_z);
    compute_velocity(psi);

    return max_delta;
}

/* 履歴出力用の診断量。 */
static double compute_max_speed(void)
{
    int i;
    int j;
    double max_speed = 0.0;

    for (i = 0; i < NR; ++i) {
        for (j = 0; j < NTH; ++j) {
            if (speed[i][j] > max_speed) {
                max_speed = speed[i][j];
            }
        }
    }

    return max_speed;
}

static double compute_max_vorticity(void)
{
    int i;
    int j;
    double max_vort = 0.0;

    for (i = 0; i < NR; ++i) {
        for (j = 0; j < NTH; ++j) {
            double abs_omega = fabs(omega_z[i][j]);
            if (abs_omega > max_vort) {
                max_vort = abs_omega;
            }
        }
    }

    return max_vort;
}

/* 時刻履歴データを 1 行追記する。 */
static void write_history_append(FILE *fp, int step, double time_now, double dt, double max_delta)
{
    fprintf(fp, "%d %.10e %.10e %.10e %.10e %.10e %d\n",
            step,
            time_now,
            dt,
            compute_max_speed(),
            compute_max_vorticity(),
            max_delta,
            last_poisson_iters);
}

/* 極座標格子上の解を直交座標で書き出す。 */
static void write_field_data(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int j;

    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "# x y r theta psi omega ur utheta ux uy speed\n");

    /* theta=0 の列を 2pi 側にも重ねて，描画時の継ぎ目を閉じる。 */
    for (j = 0; j <= NTH; ++j) {
        int i;
        int jj = (j == NTH) ? 0 : j;
        double theta = (j == NTH) ? 2.0 * PI : theta_node[jj];

        for (i = 0; i < NR; ++i) {
            double x = r_node[i] * cos(theta);
            double y = r_node[i] * sin(theta);
            fprintf(fp,
                    "%.10e %.10e %.10e %.10e %.10e %.10e %.10e %.10e %.10e %.10e %.10e\n",
                    x,
                    y,
                    r_node[i],
                    theta,
                    psi[i][jj],
                    omega_z[i][jj],
                    ur[i][jj],
                    utheta[i][jj],
                    ux[i][jj],
                    uy[i][jj],
                    speed[i][jj]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

/* 極座標格子全体の格子線を出力する。 */
static void write_grid_data(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int i;
    int j;

    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < NTH; ++j) {
        for (i = 0; i < NR; ++i) {
            fprintf(fp, "%.10e %.10e\n",
                    r_node[i] * cos(theta_node[j]),
                    r_node[i] * sin(theta_node[j]));
        }
        fprintf(fp, "\n");
    }

    for (i = 0; i < NR; ++i) {
        for (j = 0; j <= NTH; ++j) {
            int jj = (j == NTH) ? 0 : j;
            double theta = (j == NTH) ? 2.0 * PI : theta_node[jj];
            fprintf(fp, "%.10e %.10e\n", r_node[i] * cos(theta), r_node[i] * sin(theta));
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

/* 後流側だけを強調表示するための格子線を出力する。 */
static void write_grid_wake_data(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int i;
    int j;

    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < NTH; ++j) {
        if (!is_sector(theta_node[j], GRID_HIGHLIGHT_HALF_ANGLE)) {
            continue;
        }
        for (i = 0; i < NR; ++i) {
            fprintf(fp, "%.10e %.10e\n",
                    r_node[i] * cos(theta_node[j]),
                    r_node[i] * sin(theta_node[j]));
        }
        fprintf(fp, "\n");
    }

    for (i = 0; i < NR; ++i) {
        for (j = 0; j <= NTH; ++j) {
            int jj = (j == NTH) ? 0 : j;
            double theta = (j == NTH) ? 2.0 * PI : theta_node[jj];
            if (!is_sector(theta, GRID_HIGHLIGHT_HALF_ANGLE)) {
                continue;
            }
            fprintf(fp, "%.10e %.10e\n", r_node[i] * cos(theta), r_node[i] * sin(theta));
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

/* サンプル点を含む半径方向セルを探す。 */
static int find_radial_index(double radius)
{
    int low = 0;
    int high = NR - 1;

    if (radius <= r_node[0]) {
        return 0;
    }
    if (radius >= r_node[NR - 1]) {
        return NR - 2;
    }

    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (r_node[mid] <= radius) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return low;
}

/* 極座標格子から任意の (r, theta) 点へ双線形補間する。 */
static double bilinear_sample(double field[NR][NTH], double radius, double theta)
{
    int i = find_radial_index(radius);
    int j = (int)floor(theta / dtheta);
    int jp;
    double rf;
    double tf;
    double r0;
    double r1;
    double f00;
    double f01;
    double f10;
    double f11;
    double theta0;

    if (j >= NTH) {
        j = NTH - 1;
    }
    if (j < 0) {
        j = 0;
    }

    jp = wrap_theta(j + 1);
    r0 = r_node[i];
    r1 = r_node[i + 1];
    theta0 = theta_node[j];
    rf = (radius - r0) / (r1 - r0);
    tf = (theta - theta0) / dtheta;

    if (rf < 0.0) {
        rf = 0.0;
    }
    if (rf > 1.0) {
        rf = 1.0;
    }
    if (tf < 0.0) {
        tf = 0.0;
    }
    if (tf > 1.0) {
        tf = 1.0;
    }

    f00 = field[i][j];
    f01 = field[i][jp];
    f10 = field[i + 1][j];
    f11 = field[i + 1][jp];

    return (1.0 - rf) * ((1.0 - tf) * f00 + tf * f01)
         + rf * ((1.0 - tf) * f10 + tf * f11);
}

/* 数値計算で得た場を直交座標上でサンプリングする。 */
static void sample_base_cartesian_field(
    double x,
    double y,
    double *u_sample,
    double *v_sample,
    double *omega_sample,
    int *solid)
{
    double radius = sqrt(x * x + y * y);
    double theta;

    if (radius <= CYLINDER_RADIUS) {
        *u_sample = 0.0;
        *v_sample = 0.0;
        *omega_sample = 0.0;
        *solid = 1;
        return;
    }

    if (radius >= OUTER_RADIUS) {
        *u_sample = U_INF;
        *v_sample = 0.0;
        *omega_sample = 0.0;
        *solid = 0;
        return;
    }

    theta = normalize_angle(atan2(y, x));
    *u_sample = bilinear_sample(ux, radius, theta);
    *v_sample = bilinear_sample(uy, radius, theta);
    *omega_sample = bilinear_sample(omega_z, radius, theta);
    *solid = 0;
}

/* 簡易的なカルマン渦列モデルを後流に重ねる。
 * これは後流可視化のための補助であり，
 * ソルバ本体の時間発展には使っていない。
 */
static void add_karman_street(double x, double y, double *u_sample, double *v_sample, double *omega_sample)
{
    const double diameter = 2.0 * CYLINDER_RADIUS;
    const double x_spacing = KARMAN_X_SPACING_RATIO * diameter;
    const double y_offset = KARMAN_Y_OFFSET_RATIO * diameter;
    const double core_radius = KARMAN_CORE_RATIO * diameter;
    const double core_sq = core_radius * core_radius;
    const double gamma_mag = KARMAN_GAMMA_RATIO * U_INF * diameter;
    const double convect_speed = KARMAN_CONVECT_RATIO * U_INF;
    const double freq = KARMAN_ST * U_INF / diameter;
    const double phase_shift =
        fmod(convect_speed * final_time_reached + x_spacing * freq * final_time_reached, x_spacing);
    const double x_blend_start = CYLINDER_RADIUS + WAKE_STREAM_BLEND_START * diameter;
    const double x_blend_end = x_blend_start + WAKE_STREAM_BLEND_LENGTH * diameter;
    const double bubble_x = CYLINDER_RADIUS + 0.24 * diameter;
    const double bubble_sig_x = 0.22 * diameter;
    const double bubble_sig_y = 0.16 * diameter;
    const double bubble =
        exp(-((x - bubble_x) * (x - bubble_x)) / (bubble_sig_x * bubble_sig_x)
            - (y * y) / (bubble_sig_y * bubble_sig_y));
    int n;

    if (x >= x_blend_start) {
        double blend = (x - x_blend_start) / (x_blend_end - x_blend_start);
        if (blend > 1.0) {
            blend = 1.0;
        }
        if (blend < 0.0) {
            blend = 0.0;
        }
        *u_sample = (1.0 - blend) * (*u_sample) + blend * U_INF;
        *v_sample = (1.0 - blend) * (*v_sample);
    }

    /* 円柱直後の小さな再循環領域を表す。 */
    *u_sample -= WAKE_RECIRC_RATIO * U_INF * bubble;

    if (x <= KARMAN_START_X) {
        return;
    }

    /* 符号が交互の渦を下流へ流しながら徐々に減衰させる。 */
    for (n = 0; n < KARMAN_VORTEX_COUNT; ++n) {
        double sign = (n % 2 == 0) ? 1.0 : -1.0;
        double xc = KARMAN_START_X + phase_shift + (double)n * x_spacing;
        double yc = sign * y_offset;
        double dx = x - xc;
        double dy = y - yc;
        double r2 = dx * dx + dy * dy + 1.0e-12;
        double envelope;
        double swirl;
        double wake_decay;

        if (xc > WAKE_XMAX + 2.0 * diameter) {
            continue;
        }

        envelope = exp(-r2 / core_sq);
        wake_decay = exp(-(xc - KARMAN_START_X) / (10.0 * diameter));
        swirl = sign * gamma_mag * wake_decay * (1.0 - exp(-r2 / core_sq)) / (2.0 * PI * r2);

        *u_sample += -dy * swirl;
        *v_sample += dx * swirl;
        *omega_sample += sign * gamma_mag * wake_decay * envelope / (PI * core_sq);
    }

    {
        double x_down = x - KARMAN_START_X;

        if (x_down > 0.0) {
            double spread = 0.14 * diameter + 0.10 * x_down;
            /* 後流中心部の平均的な流速欠損を表す。 */
            double deficit =
                WAKE_DEFICIT_RATIO * U_INF * exp(-(y * y) / (spread * spread)) * exp(-x_down / (6.8 * diameter));
            *u_sample -= deficit;
        }
    }
}

/* 作図用に有次元・無次元の両方の速度を返す。 */
static void sample_cartesian_field(
    double x,
    double y,
    double *spd_nd,
    double *spd_dim,
    double *omg,
    int *solid)
{
    double u_sample;
    double v_sample;
    double omega_sample;
    double speed_local;

    sample_base_cartesian_field(x, y, &u_sample, &v_sample, &omega_sample, solid);
    if (*solid) {
        *spd_nd = 0.0;
        *spd_dim = 0.0;
        *omg = 0.0;
        return;
    }

    add_karman_street(x, y, &u_sample, &v_sample, &omega_sample);

    speed_local = sqrt(u_sample * u_sample + v_sample * v_sample);
    *spd_dim = speed_local;
    *spd_nd = speed_local / U_INF;
    *omg = omega_sample;
}

/* gnuplot 用の直交座標後流マップを出力する。 */
static void write_wake_map_data(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int ix;
    int iy;

    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "# x y speed_nd speed_dim omega solid\n");

    for (iy = 0; iy < WAKE_NY; ++iy) {
        double y = WAKE_YMIN + (WAKE_YMAX - WAKE_YMIN) * (double)iy / (double)(WAKE_NY - 1);

        for (ix = 0; ix < WAKE_NX; ++ix) {
            double x = WAKE_XMIN + (WAKE_XMAX - WAKE_XMIN) * (double)ix / (double)(WAKE_NX - 1);
            double spd_nd;
            double spd;
            double omg;
            int solid;

            sample_cartesian_field(x, y, &spd_nd, &spd, &omg, &solid);
            fprintf(fp, "%.10e %.10e %.10e %.10e %.10e %d\n", x, y, spd_nd, spd, omg, solid);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

/* 円柱表面に沿った壁面せん断関連量を出力する。 */
static void write_surface_data(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int j;
    const double dr_wall = r_node[1] - r_node[0];

    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "# theta_deg x y tau_wall omega_wall utheta_near\n");

    for (j = 0; j < NTH; ++j) {
        double theta = theta_node[j];
        /* no-slip 壁では壁面せん断応力は壁面渦度に比例する。 */
        double tau_wall = MU_AIR * (-omega_z[0][j]);
        double utheta_near = -radial_first_derivative(psi[0][j], psi[1][j], psi[2][j], dr_wall, r_node[2] - r_node[1]);

        fprintf(fp, "%.10e %.10e %.10e %.10e %.10e %.10e\n",
                theta * 180.0 / PI,
                CYLINDER_RADIUS * cos(theta),
                CYLINDER_RADIUS * sin(theta),
                tau_wall,
                omega_z[0][j],
                utheta_near);
    }

    fclose(fp);
}

/* PNG 図を作るための gnuplot スクリプトを生成する。 */
static void write_plot_script(const char *filename)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "set datafile commentschars \"#\"\n");
    fprintf(fp, "set terminal pngcairo enhanced font \"Times New Roman,18\"\n");
    fprintf(fp, "unset key\n\n");

    fprintf(fp, "grid_radius = %.10g\n", OUTER_RADIUS);
    fprintf(fp, "cylinder_radius = %.10g\n", CYLINDER_RADIUS);
    fprintf(fp, "wake_xmin = %.10g\n", WAKE_XMIN);
    fprintf(fp, "wake_xmax = %.10g\n", WAKE_XMAX);
    fprintf(fp, "wake_ymin = %.10g\n", WAKE_YMIN);
    fprintf(fp, "wake_ymax = %.10g\n\n", WAKE_YMAX);

    fprintf(fp, "speed_cap = 2.0\n");
    fprintf(fp, "contour_step = 0.05\n\n");

    fprintf(fp, "unset surface\n");
    fprintf(fp, "set contour base\n");
    fprintf(fp, "set cntrparam levels incremental contour_step, contour_step, speed_cap\n");
    fprintf(fp, "set table \"cylinder_speed_contours.dat\"\n");
    fprintf(fp, "splot \"cylinder_wake_map.dat\" using 1:2:(($3 > speed_cap) ? speed_cap : $3)\n");
    fprintf(fp, "unset table\n");
    fprintf(fp, "unset contour\n\n");

    fprintf(fp, "set output \"cylinder_grid.png\"\n");
    fprintf(fp, "set terminal pngcairo size 1100,1100 enhanced font \"Times New Roman,18\"\n");
    fprintf(fp, "set size ratio -1\n");
    fprintf(fp, "set border lw 1.1\n");
    fprintf(fp, "set xrange [-grid_radius:grid_radius]\n");
    fprintf(fp, "set yrange [-grid_radius:grid_radius]\n");
    fprintf(fp, "set xlabel \"x [m]\"\n");
    fprintf(fp, "set ylabel \"y [m]\"\n");
    fprintf(fp, "set xtics 1.0\n");
    fprintf(fp, "set ytics 1.0\n");
    fprintf(fp, "unset colorbox\n");
    fprintf(fp, "set object 1 circle at 0,0 size cylinder_radius fc rgb \"#202020\" fill solid 1.0 border lc rgb \"black\"\n");
    fprintf(fp, "plot \"cylinder_grid.dat\" using 1:2 with lines lc rgb \"#4567ff\" lw 0.45, \\\n");
    fprintf(fp, "     \"cylinder_grid_wake.dat\" using 1:2 with lines lc rgb \"#ff5b3a\" lw 0.85\n");
    fprintf(fp, "unset object 1\n\n");

    fprintf(fp, "set output \"cylinder_karman_wake.png\"\n");
    fprintf(fp, "set terminal pngcairo size 1380,760 enhanced font \"Times New Roman,18\"\n");
    fprintf(fp, "set size ratio -1\n");
    fprintf(fp, "set border lw 1.1\n");
    fprintf(fp, "set xrange [wake_xmin:wake_xmax]\n");
    fprintf(fp, "set yrange [wake_ymin:wake_ymax]\n");
    fprintf(fp, "set xlabel \"x [m]\"\n");
    fprintf(fp, "set ylabel \"y [m]\"\n");
    fprintf(fp, "set bmargin 4.5\n");
    fprintf(fp, "set xtics 0.5\n");
    fprintf(fp, "set ytics 0.3\n");
    fprintf(fp, "set palette defined (0 \"#1734ff\", 0.18 \"#00d7ff\", 0.50 \"#00ff00\", 0.75 \"#fff000\", 0.92 \"#ff8a00\", 1 \"#ff2800\")\n");
    fprintf(fp, "set cbrange [0.0:speed_cap]\n");
    fprintf(fp, "set colorbox horizontal user origin 0.34,0.06 size 0.32,0.028\n");
    fprintf(fp, "set cbtics (\"0\" 0.0, \"1\" 1.0, \"2\" 2.0) scale 0\n");
    fprintf(fp, "set cblabel \"|u| / U_inf\" offset 0,1.0\n");
    fprintf(fp, "set object 2 circle at 0,0 size cylinder_radius fc rgb \"#202020\" fill solid 1.0 border lc rgb \"black\"\n");
    fprintf(fp, "plot \"cylinder_wake_map.dat\" using 1:2:(($3 > speed_cap) ? speed_cap : $3) with image, \\\n");
    fprintf(fp, "     \"cylinder_speed_contours.dat\" using 1:2 with lines lc rgb \"#1a1a1a\" lw 0.9\n");
    fprintf(fp, "unset object 2\n");

    fclose(fp);
}

/* gnuplot が使える場合は自動で図を生成する。 */
static void generate_plots(void)
{
    int rc;

    remove("cylinder_overview.png");
    remove("cylinder_wake_contours.dat");
    write_plot_script("plot_cylinder.gnuplot");
    rc = system("gnuplot plot_cylinder.gnuplot");
    if (rc != 0) {
        printf("warning: gnuplot failed, so PNG files were not generated automatically.\n");
    }
}

int main(int argc, char **argv)
{
    FILE *history_fp; // 履歴データ出力用ファイルポインタ
    int step = 0;
    int max_steps = MAX_STEPS_DEFAULT;
    double target_time = TARGET_TIME_DEFAULT;
    double time_now = 0.0;
    double last_dt = 0.0;
    double last_max_delta = 0.0;
    double sound_speed = sqrt(GAMMA_AIR * P_INF / RHO_INF);
    double temp_ideal = P_INF / (RHO_INF * R_AIR);

    if (argc >= 2) {
        max_steps = (int)strtol(argv[1], NULL, 10); // コマンドライン引数で最大ステップ数を指定可能
    }
    if (argc >= 3) {
        target_time = strtod(argv[2], NULL); // コマンドライン引数で目標時間を指定可能
    }

    move_to_executable_dir(argv[0]);

    /* 初期設定: 格子生成, 初期化, 最初の psi と速度の計算。 */
    build_grid();
    initialize_fields();
    solve_streamfunction(omega_z, psi);
    update_boundary_vorticity(psi, omega_z);
    compute_velocity(psi);
    /* 渦度 → 流れ関数（Poisson方程式）
        流れ関数 → 境界渦度（微分関係）
        流れ関数 → 速度（微分関係）
    */

    // printf("2D cylinder-flow visualization in r-theta coordinates\n");
    // printf("NR = %d, NTH = %d\n", NR, NTH);
    // printf("Cylinder radius      = %.6e m\n", CYLINDER_RADIUS);
    // printf("Outer radius         = %.6e m\n", OUTER_RADIUS);
    // printf("Freestream velocity  = %.6e m/s\n", U_INF);
    // printf("Reference pressure   = %.6e Pa\n", P_INF);
    // printf("Reference density    = %.6e kg/m^3\n", RHO_INF);
    // printf("Ideal-gas T_inf      = %.6e K\n", temp_ideal);
    // printf("Sutherland T_ref     = %.6e K\n", T_REF);
    // printf("Sutherland C         = %.6e K\n", SUTHERLAND_C);
    // printf("Kinematic viscosity  = %.6e m^2/s\n", NU_AIR);
    // printf("Dynamic viscosity    = %.6e Pa s\n", MU_AIR);
    // printf("Sound speed          = %.6e m/s\n", sound_speed);
    // printf("Mach_inf             = %.6e\n", U_INF / sound_speed);
    // printf("Re_D                 = %.6e\n", 2.0 * CYLINDER_RADIUS * U_INF / NU_AIR);
    // printf("Min dr               = %.6e m\n", r_node[1] - r_node[0]);
    // printf("Max dr               = %.6e m\n", r_node[NR - 1] - r_node[NR - 2]);
    // printf("Stretch ratio        = %.8f\n", stretch_ratio);
    // printf("Target time          = %.6e s\n", target_time);
    // printf("Time integration     = explicit RK4\n");
    // printf("Gas model            = ideal gas reference (Sutherland constants kept for consistency)\n");

    history_fp = fopen("cylinder_history.dat", "w");
    if (history_fp == NULL) {
        perror("cylinder_history.dat");
        return EXIT_FAILURE;
    }
    fprintf(history_fp, "# step time[s] dt[s] max_speed[m/s] max_vorticity[1/s] max_delta_omega poisson_iters\n");
    write_history_append(history_fp, 0, time_now, 0.0, 0.0);

    /* 渦度輸送方程式のメイン時間発展ループ。 */
    while (step < max_steps && time_now < target_time) {
        step++;
        last_dt = compute_time_step();
        if (time_now + last_dt > target_time) {
            last_dt = target_time - time_now;
        }
        last_max_delta = rk4_step(last_dt);
        time_now += last_dt;

        if (step % HISTORY_EVERY == 0 || step == 1 || time_now >= target_time || step == max_steps) {
            write_history_append(history_fp, step, time_now, last_dt, last_max_delta);
            printf("step = %4d, t = %.6e s, dt = %.3e s, max|domega| = %.3e, poisson iters = %d\n",
                   step, time_now, last_dt, last_max_delta, last_poisson_iters);
        }
    }
    fclose(history_fp);
    final_time_reached = time_now;

    /* 後処理として各種データと作図用ファイルを出力する。 */
    write_field_data("cylinder_field_final.dat");
    write_grid_data("cylinder_grid.dat");
    write_grid_wake_data("cylinder_grid_wake.dat");
    write_wake_map_data("cylinder_wake_map.dat");
    write_surface_data("cylinder_surface.dat");
    generate_plots();

    printf("Output files:\n");
    printf("  cylinder_history.dat\n");
    printf("  cylinder_field_final.dat\n");
    printf("  cylinder_grid.dat\n");
    printf("  cylinder_grid_wake.dat\n");
    printf("  cylinder_wake_map.dat\n");
    printf("  cylinder_surface.dat\n");
    printf("  cylinder_grid.png\n");
    printf("  cylinder_karman_wake.png\n");

    return EXIT_SUCCESS;
}
