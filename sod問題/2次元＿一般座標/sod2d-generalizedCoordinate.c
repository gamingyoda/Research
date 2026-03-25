/*  
2次元の衝撃波管問題(Sod問題)の一般座標
2次元Euler方程式 + FDS（Roe-FDS）+ Runge–Kutta


γ=1.4
左 : ρ=1.0, u=0, v=0, p=1.0
右: ρ=0.125, u=0, v=0, p=0.1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define GAMMA 1.4    // 比熱比（理想気体）

// グリッド定義
#define NX 400       // x方向の格子数
#define NY 400       // y方向の格子数
#define X0 0.0       // x座標の最小値
#define X1 1.0       // x座標の最大値
#define Y0 0.0       // y座標の最小値
#define Y1 1.0       // y座標の最大値

// 計算条件
#define XDIFF 0.5    // 初期不連続面の位置
#define CFL 0.5      // CFL数（時間ステップの安定性条件の係数）
#define T_END 0.20   // 計算終了時刻

// 初期条件：左領域
#define RHO_L  1.0   // 密度（左）
#define U_L    0.0   // x方向速度（左）
#define P_L    1.0   // 圧力（左）

// 初期条件：右領域
#define RHO_R  0.125 // 密度（右）
#define U_R    0.0   // x方向速度（右）
#define P_R    0.1   // 圧力（右）

//  データ構造体定義 

// 保存量（Conservative variables）
// 有限体積法では保存量で方程式を解く
typedef struct { 
    double rho;    // 密度
    double rho_u;  // x方向運動量
    double rho_v;  // y方向運動量
    double E;      // 全エネルギー
} Conservative;

// 原始変数（Primitive variables）
// 物理量として見やすい形式
typedef struct { 
    double rho;    // 密度
    double u;      // x方向速度
    double v;      // y方向速度
    double p;      // 圧力
} Primitive;

// 面の幾何情報（一般座標対応）
typedef struct { 
    double nx;     // 法線ベクトルのx成分
    double ny;     // 法線ベクトルのy成分
    double L;      // 面の長さ
} FaceGeom;

//  保存量の基本演算 

// 保存量どうしの加算
static inline Conservative c_add(Conservative a, Conservative b) {
    return (Conservative){a.rho+b.rho, a.rho_u+b.rho_u, a.rho_v+b.rho_v, a.E+b.E};
}

// 保存量どうしの減算
static inline Conservative c_sub(Conservative a, Conservative b) {
    return (Conservative){a.rho-b.rho, a.rho_u-b.rho_u, a.rho_v-b.rho_v, a.E-b.E};
}

// 保存量のスカラー倍
static inline Conservative c_scale(Conservative a, double s) {
    return (Conservative){a.rho*s, a.rho_u*s, a.rho_v*s, a.E*s};
}

//  変数変換関数 

// 保存量から原始変数への変換
// U = (ρ, ρu, ρv, E) → W = (ρ, u, v, p)
static Primitive cons_to_prim(Conservative U)
{
    Primitive W;
    W.rho = U.rho;
    W.u   = U.rho_u / U.rho;              // 速度: u = ρu / ρ
    W.v   = U.rho_v / U.rho;              // 速度: v = ρv / ρ
    // 圧力: p = (γ-1)(E - 0.5ρ(u²+v²))
    W.p   = (GAMMA - 1.0) * (U.E - 0.5 * U.rho * (W.u*W.u + W.v*W.v));
    return W;
}

// 原始変数から保存量への変換
// W = (ρ, u, v, p) → U = (ρ, ρu, ρv, E)
static Conservative prim_to_cons(Primitive W)
{
    Conservative U;
    U.rho  = W.rho;
    U.rho_u = W.rho * W.u;                // 運動量: ρu
    U.rho_v = W.rho * W.v;                // 運動量: ρv
    // 全エネルギー: E = p/(γ-1) + 0.5ρ(u²+v²)
    U.E    = W.p/(GAMMA-1.0) + 0.5 * W.rho * (W.u*W.u + W.v*W.v);
    return U;
}

//  物理的フラックス計算 

// x方向のフラックス（デカルト座標）
// F = (ρu, ρu²+p, ρuv, u(E+p))
static Conservative FluxX(Primitive W)
{
    const double E = W.p/(GAMMA-1.0) + 0.5*W.rho*(W.u*W.u + W.v*W.v);
    Conservative F;
    F.rho  = W.rho * W.u;
    F.rho_u = W.rho * W.u * W.u + W.p;
    F.rho_v = W.rho * W.u * W.v;
    F.E    = W.u * (E + W.p);
    return F;
}

// y方向のフラックス（デカルト座標）
// G = (ρv, ρuv, ρv²+p, v(E+p))
static Conservative FluxY(Primitive W)
{
    const double E = W.p/(GAMMA-1.0) + 0.5*W.rho*(W.u*W.u + W.v*W.v);
    Conservative G;
    G.rho  = W.rho * W.v;
    G.rho_u = W.rho * W.u * W.v;
    G.rho_v = W.rho * W.v * W.v + W.p;
    G.E    = W.v * (E + W.p);
    return G;
}

//  Roe の数値フラックス計算（一般座標版） 
// 面の法線方向に沿った1次元Riemann問題として解く
// 入力: 左右の原始変数、面の法線ベクトル(nx, ny)
// 出力: 法線方向のフラックス
static void ROE_Flux_Normal(Primitive WL, Primitive WR, double nx, double ny, Conservative *Fout)
{
    // 法線方向と接線方向のベクトルを定義
    // (tx, ty) は法線に垂直な方向
    const double tx = -ny;
    const double ty =  nx;

    // 保存量に変換
    Conservative UL = prim_to_cons(WL);
    Conservative UR = prim_to_cons(WR);

    // 全エンタルピー（比エンタルピー）
    const double HL = (UL.E + WL.p) / WL.rho;  // H = (E+p)/ρ
    const double HR = (UR.E + WR.p) / WR.rho;

    // 速度を法線方向と接線方向の成分に分解
    const double uL_n = WL.u*nx + WL.v*ny;    // 左の法線方向速度
    const double uR_n = WR.u*nx + WR.v*ny;    // 右の法線方向速度
    const double uL_t = WL.u*tx + WL.v*ty;    // 左の接線方向速度
    const double uR_t = WR.u*tx + WR.v*ty;    // 右の接線方向速度

    // Roeの平均値を計算（√ρで重み付けした平均）
    const double sqL = sqrt(WL.rho);
    const double sqR = sqrt(WR.rho);
    const double inv = 1.0 / (sqL + sqR);

    // Roe平均値
    const double uT_n = (sqL*uL_n + sqR*uR_n) * inv;    // 法線方向Roe平均速度
    const double uT_t = (sqL*uL_t + sqR*uR_t) * inv;    // 接線方向Roe平均速度
    const double HT = (sqL*HL  + sqR*HR ) * inv;        // Roe平均エンタルピー

    // Roe平均音速を計算
    double aT2 = (GAMMA - 1.0) * (HT - 0.5*(uT_n*uT_n + uT_t*uT_t));
    double aT = (aT2 > 0.0) ? sqrt(aT2) : 0.0;  // 音速（負値対策）

    // 状態量の左右での差
    const double dr  = WR.rho - WL.rho;        // 密度の差
    const double dp  = WR.p   - WL.p;          // 圧力の差
    const double dut = uR_t - uL_t;            // 接線速度の差
    const double dun = uR_n - uL_n;            // 法線速度の差

    const double rhoT = sqL*sqR;               // Roe平均密度の関連量

    // Roeの固有ベクトル展開係数αを計算
    // 左右の状態量の差を固有ベクトルで展開
    const double alpha2 = dr - dp/aT2;                  // 音速が0でない固有ベクトル成分
    const double alpha1 = (dp - rhoT*aT*dun)/(2*aT2);  // 音波（負）の成分
    const double alpha4 = (dp + rhoT*aT*dun)/(2*aT2);  // 音波（正）の成分
    const double alpha3 = rhoT * dut;                   // エントロピー波の成分

    // Roeの固有値（代数的な波の伝播速度）
    const double lam1 = uT_n - aT;             // 音速を持つ左向きの波
    const double lam2 = uT_n;                  // エントロピー波（接線速度の不連続）
    const double lam3 = uT_n;                  // エントロピー波
    const double lam4 = uT_n + aT;             // 音速を持つ右向きの波

    // 数値拡散項：Harten-Hyman修正を使用して、固有値が0に近い場合の安定性を確保
    const double delta = 0.1 * aT;             // 修正パラメータ
    // |λ| < δ のとき滑らかに |λ| に遷移
    const double a1 = (fabs(lam1) >= delta) ? fabs(lam1) : (lam1*lam1 + delta*delta)/(2.0*delta);
    const double a2 = (fabs(lam2) >= delta) ? fabs(lam2) : (lam2*lam2 + delta*delta)/(2.0*delta);
    const double a3 = (fabs(lam3) >= delta) ? fabs(lam3) : (lam3*lam3 + delta*delta)/(2.0*delta);
    const double a4 = (fabs(lam4) >= delta) ? fabs(lam4) : (lam4*lam4 + delta*delta)/(2.0*delta);
    
    // FDS（Flux Difference Splitting）の計算
    // 各固有ベクトル方向の変化を計算
    const double d_rho    = a1*alpha1 + a2*alpha2 + a4*alpha4;                               // 密度変化
    const double d_rho_un = a1*alpha1*(uT_n - aT) + a2*alpha2*uT_n + a4*alpha4*(uT_n + aT); // 法線運動量変化
    const double d_rho_ut = a1*alpha1*uT_t + a2*alpha2*uT_t + a3*alpha3*1.0 + a4*alpha4*uT_t; // 接線運動量変化
    const double d_E      = a1*alpha1*(HT - uT_n*aT) + a2*alpha2*0.5*(uT_n*uT_n + uT_t*uT_t) + a3*alpha3*(uT_t) + a4*alpha4*(HT + uT_n*aT); // エネルギー変化
    
    // 左右のデカルト座標フラックスを計算
    const Conservative FL = FluxX(WL);
    const Conservative GL = FluxY(WL);
    const Conservative FR = FluxX(WR);
    const Conservative GR = FluxY(WR);

    // フラックスを法線方向に投影（法線方向フラックス = F*nx + G*ny）
    const Conservative FnL = c_add(c_scale(FL, nx), c_scale(GL, ny));
    const Conservative FnR = c_add(c_scale(FR, nx), c_scale(GR, ny));

    // 数値拡散項の運動量成分をデカルト座標に変換back
    const double d_rho_u = d_rho_un*nx + d_rho_ut*tx;  // x方向
    const double d_rho_v = d_rho_un*ny + d_rho_ut*ty;  // y方向

    // Roe-FDS: 数値フラックス = 平均フラックス - 0.5 × 数値拡散項
    Fout->rho   = 0.5*(FnL.rho   + FnR.rho  ) - 0.5*d_rho;
    Fout->rho_u = 0.5*(FnL.rho_u + FnR.rho_u) - 0.5*d_rho_u;
    Fout->rho_v = 0.5*(FnL.rho_v + FnR.rho_v) - 0.5*d_rho_v;
    Fout->E     = 0.5*(FnL.E     + FnR.E    ) - 0.5*d_E;
}

//  境界条件処理 
// Zero-slope（0勾配）境界条件：幽霊格子に内部の値をコピー
static void zero_slope(Conservative *U, int nx_end, int ny_end, int ng)
{
    // x方向の境界処理
    for (int j = 0; j < ny_end; j++) {
        // 左辺界（i < ng）に内部値をコピー
        for (int i = 0; i < ng; i++) {
            U[j * nx_end + i] = U[j * nx_end + ng];
        }
        // 右境界（i >= nx_end - ng）に内部値をコピー
        for (int i = 0; i < ng; i++) {
            U[j * nx_end + (nx_end - 1 - i)] = U[j * nx_end + (nx_end - 1 - ng)];
        }
    }

    // y方向の境界処理
    for (int i = 0; i < nx_end; i++) {
        // 下境界（j < ng）に内部値をコピー
        for (int j = 0; j < ng; j++) {
            U[j * nx_end + i] = U[ng * nx_end + i];
        }
        // 上境界（j >= ny_end - ng）に内部値をコピー
        for (int j = 0; j < ng; j++) {
            U[(ny_end - 1 - j) * nx_end + i] = U[(ny_end - 1 - ng) * nx_end + i];
        }
    }
}

//  インデックス計算（1次元配列への要素アクセス） 

// ノード（格子点）のインデックス
static inline int idxN(int i, int j, int nxN) { return j*nxN + i; }

// セル（格子セル中心）のインデックス
static inline int idxC(int i, int j, int nxC) { return j*nxC + i; }

// x方向の面のインデックス
static inline int idxFX(int i, int j, int nxC) { return j*(nxC-1) + i; }

// y方向の面のインデックス
static inline int idxFY(int i, int j, int nxC) { return j*nxC + i; }

//  グリッド生成 
// デカルト座標系（直交格子）上にノードを生成
static void build_cartesian_grid(double *xN, double *yN, int nxC, int nyC, int ng)
{
    const int nxN = nxC + 1;               // ノード数 = セル数 + 1
    const int nyN = nyC + 1;

    const double dx = (X1 - X0)/NX;        // グリッド間隔
    const double dy = (Y1 - Y0)/NY;

    // ノードの座標を設定
    for (int j = 0; j < nyN; j++) {
        for (int i = 0; i < nxN; i++) {
            // 幽霊格子を考慮した座標計算
            const double x = X0 + (i - ng) * dx;
            const double y = Y0 + (j - ng) * dy;
            const int id = idxN(i, j, nxN);
            xN[id] = x;
            yN[id] = y;
        }
    }
}

//  幾何計算補助関数 
// 四角形セルの面積を計算（Shoelace公式）
static double quad_area(double x0,double y0,double x1,double y1,double x2,double y2,double x3,double y3)
{
    // 四つのノード (x0,y0), (x1,y1), (x2,y2), (x3,y3) で囲まれた四角形の面積
    const double s = x0*y1 - x1*y0 + x1*y2 - x2*y1 + x2*y3 - x3*y2 + x3*y0 - x0*y3;
    return 0.5 * fabs(s);
}

//  幾何情報計算 
// セルの面積と面の法線・長さを計算（一般座標対応）
static void compute_geometry(const double *xN, const double *yN, int nxC, int nyC, double *cellA, FaceGeom *faceX, FaceGeom *faceY)
{
    const int nxN = nxC + 1;

    // ステップ1: セルの面積を計算
    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC; i++) {
            // セル (i, j) の四つのノードのインデックス
            const int n00 = idxN(i,   j,   nxN);
            const int n10 = idxN(i+1, j,   nxN);
            const int n11 = idxN(i+1, j+1, nxN);
            const int n01 = idxN(i,   j+1, nxN);

            // 四角形の面積を計算
            const double A = quad_area(
                xN[n00], yN[n00],
                xN[n10], yN[n10],
                xN[n11], yN[n11],
                xN[n01], yN[n01]
            );
            // 面積が0に近い場合は最小値を使用（数値計算の安定性）
            cellA[idxC(i,j,nxC)] = (A > 1e-14) ? A : 1e-14;
        }
    }

    // ステップ2: x方向の面（セルを右に分ける面）の法線と長さを計算
    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC-1; i++) {
            // 面の下と上のノード
            const int nb = idxN(i+1, j,   nxN);    // bottom
            const int nt = idxN(i+1, j+1, nxN);    // top
            
            // 面の方向ベクトル
            const double ex = xN[nt] - xN[nb];
            const double ey = yN[nt] - yN[nb];
            const double L  = hypot(ex, ey);        // 面の長さ
            const double invL = (L > 1e-14) ? 1.0 / L : 0.0;
            
            // 外向き法線（反時計回りで90度回転）
            const double nx = ey * invL;
            const double ny = -ex * invL;
            faceX[idxFX(i,j,nxC)] = (FaceGeom){nx, ny, (L > 1e-14 ? L : 1e-14)};
        }
    }

    // ステップ3: y方向の面（セルを上に分ける面）の法線と長さを計算
    for (int j = 0; j < nyC-1; j++) {
        for (int i = 0; i < nxC; i++) {
            // 面の左と右のノード
            const int nl = idxN(i,   j+1, nxN);    // left
            const int nr = idxN(i+1, j+1, nxN);    // right
            
            // 面の方向ベクトル
            const double ex = xN[nr] - xN[nl];
            const double ey = yN[nr] - yN[nl];
            const double L  = hypot(ex, ey);        // 面の長さ
            const double invL = (L > 1e-14) ? 1.0 / L : 0.0;
            
            // 外向き法線（反時計回りで90度回転）
            const double nx = -ey * invL;
            const double ny = ex * invL;
            faceY[idxFY(i,j,nxC)] = (FaceGeom){nx, ny, (L > 1e-14 ? L : 1e-14)};
        }
    }
}

// セルの重心座標を計算
static void cell_center(const double *xN, const double *yN, int nxC, int i, int j, double *xc, double *yc)
{
    const int nxN = nxC + 1;
    const int n00 = idxN(i,   j,   nxN);
    const int n10 = idxN(i+1, j,   nxN);
    const int n11 = idxN(i+1, j+1, nxN);
    const int n01 = idxN(i,   j+1, nxN);
    // 四つのノードの座標の平均（デカルト座標では重心）
    *xc = 0.25 * (xN[n00] + xN[n10] + xN[n11] + xN[n01]);
    *yc = 0.25 * (yN[n00] + yN[n10] + yN[n11] + yN[n01]);
}


//  右辺項（残差）の計算 
// dU/dt = -div F => 右辺項は発散（フラックスの差分）
static void calculate_rhs(Conservative *U, Conservative *rhs, int nxC, int nyC, int ng, double *cellA, FaceGeom *faceX, const FaceGeom *faceY, Conservative *FxInt, Conservative *FyInt)
{
    // 右辺項を初期化
    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC; i++) {
            rhs[idxC(i,j,nxC)] = (Conservative){0,0,0,0};
        }
    }

    // ステップ1: x方向の面でのフラックスを計算
    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC-1; i++) {
            // セル(i,j)と(i+1,j)の状態を原始変数に変換
            Primitive WL = cons_to_prim(U[idxC(i,j,nxC)]);
            Primitive WR = cons_to_prim(U[idxC(i+1,j,nxC)]);
            FaceGeom fg = faceX[idxFX(i,j,nxC)];

            // Roe数値フラックスを計算
            Conservative Fn;
            ROE_Flux_Normal(WL, WR, fg.nx, fg.ny, &Fn);
            // フラックスに面の長さをかけて整分フラックスに
            FxInt[idxFX(i,j,nxC)] = c_scale(Fn, fg.L);
        }
    }

    // ステップ2: y方向の面でのフラックスを計算
    for (int j = 0; j < nyC - 1; j++) {
        for (int i = 0; i < nxC; i++) {
            // セル(i,j)と(i,j+1)の状態を原始変数に変換
            Primitive WL = cons_to_prim(U[idxC(i,j,nxC)]);
            Primitive WR = cons_to_prim(U[idxC(i,j+1,nxC)]);
            FaceGeom fg = faceY[idxFY(i,j,nxC)];

            // Roe数値フラックスを計算
            Conservative Fn;
            ROE_Flux_Normal(WL, WR, fg.nx, fg.ny, &Fn);
            // フラックスに面の長さをかけて整分フラックスに
            FyInt[idxFY(i,j,nxC)] = c_scale(Fn, fg.L);
        }
    }

    // ステップ3: 発散を計算して右辺項を求める
    // dU/dt = -1/A * (ΔF) (有限体積法の形式)
    for (int j = ng; j < nyC-ng; j++) {
        for (int i = ng; i < nxC-ng; i++) {
            const double A = cellA[idxC(i,j,nxC)];              // セル面積

            // セルの四方の面のフラックス
            const Conservative FxR = FxInt[idxFX(i,   j, nxC)]; // 右の面
            const Conservative FxL = FxInt[idxFX(i-1, j, nxC)]; // 左の面
            const Conservative FyT = FyInt[idxFY(i, j,   nxC)]; // 上の面
            const Conservative FyB = FyInt[idxFY(i, j-1, nxC)]; // 下の面

            // フラックスの発散 = (右-左) + (上-下)
            Conservative div = c_add(c_sub(FxR, FxL), c_sub(FyT, FyB));
            
            // 右辺項 = -発散 / セル面積
            rhs[idxC(i,j,nxC)] = c_scale(div, -1.0/A);
        }
    }
}

//  タイムステップの計算 
// CFL条件に基づいて安定性を保つ最大時間ステップを決定
static double calculate_dt(Conservative *U, int nxC, int nyC, int ng, double *cellA, FaceGeom *faceX, FaceGeom *faceY)
{
    double dt_min = 1e300;  // 最小値の初期化

    for (int j = ng; j < nyC-ng; j++) {
        for (int i = ng; i < nxC-ng; i++) {
            const Primitive W = cons_to_prim(U[idxC(i,j,nxC)]);
            // 物理的に不正な値をスキップ
            if (W.rho <= 0.0 || W.p <= 0.0) continue;
            
            // 音速を計算
            const double a = sqrt(GAMMA * W.p / W.rho);

            // セルの四方の面の寄与を合計
            double sum = 0.0;

            // 右の面: セルを抜ける最大速度を計算
            {
                const FaceGeom fg = faceX[idxFX(i, j, nxC)];
                const double un = W.u*fg.nx + W.v*fg.ny;  // 法線方向速度
                sum += (fabs(un) + a) * fg.L;              // |u_n| + a: 左右の信号速度
            }
            // 左の面
            {
                const FaceGeom fg = faceX[idxFX(i-1, j, nxC)];
                const double un = W.u*fg.nx + W.v*fg.ny;
                sum += (fabs(un) + a) * fg.L;
            }
            // 上の面
            {
                const FaceGeom fg = faceY[idxFY(i, j, nxC)];
                const double un = W.u*fg.nx + W.v*fg.ny;
                sum += (fabs(un) + a) * fg.L;
            }
            // 下の面
            {
                const FaceGeom fg = faceY[idxFY(i, j-1, nxC)];
                const double un = W.u*fg.nx + W.v*fg.ny;
                sum += (fabs(un) + a) * fg.L;
            }

            // このセルでのCFL条件: dt ≤ CFL * A / sum
            const double A = cellA[idxC(i,j,nxC)];
            const double dt_cell = CFL * A / sum;
            
            // 全セルでの最小値を取る（最も厳しい条件）
            if (dt_cell < dt_min) dt_min = dt_cell;
        }
    }

    return dt_min;
}


static void write_and_plot(const Conservative *U,
                           const double *xN, const double *yN,
                           int nxC, int nyC, int ng)
{
    FILE *fp = fopen("sod2d.dat", "w");
    if (!fp) { perror("sod2d.dat"); return; }

    fprintf(fp, "# x y rho u v p\n");
    for (int j = ng; j < nyC-ng; j++) {
        for (int i = ng; i < nxC-ng; i++) {
            double x,y;
            cell_center(xN, yN, nxC, i, j, &x, &y);
            Primitive W = cons_to_prim(U[idxC(i,j,nxC)]);
            fprintf(fp, "%.10f %.10f %.10f %.10f %.10f %.10f\n", x, y, W.rho, W.u, W.v, W.p);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    {
        const char *gpname = "sod2d_rho.gp";
        FILE *gp = fopen(gpname, "w");
        if (gp) {
            fprintf(gp, "set grid\n");
            fprintf(gp, "set pm3d map\n");
            fprintf(gp, "set title 'Sod 2D (general coords): Density (t=%.3f, NX=%d, NY=%d)'\n", T_END, NX, NY);
            fprintf(gp, "set xlabel 'x'\n");
            fprintf(gp, "set ylabel 'y'\n");
            fprintf(gp, "set cblabel 'Density rho'\n");
            fprintf(gp, "splot 'sod2d.dat' using 1:2:3 with pm3d notitle\n");
            fclose(gp);
            char cmd[256];
#ifdef _WIN32
            snprintf(cmd, sizeof(cmd), "cmd /c gnuplot -persist \"%s\"", gpname);
#else
            snprintf(cmd, sizeof(cmd), "gnuplot -persist \"%s\"", gpname);
#endif
            system(cmd);
        }
    }

    {
        const char *gpname = "sod2d_u.gp";
        FILE *gp = fopen(gpname, "w");
        if (gp) {
            fprintf(gp, "set grid\n");
            fprintf(gp, "set pm3d map\n");
            fprintf(gp, "set title 'Sod 2D (general coords): Velocity u (t=%.3f, NX=%d, NY=%d)'\n", T_END, NX, NY);
            fprintf(gp, "set xlabel 'x'\n");
            fprintf(gp, "set ylabel 'y'\n");
            fprintf(gp, "set cblabel 'Velocity u'\n");
            fprintf(gp, "splot 'sod2d.dat' using 1:2:4 with pm3d notitle\n");
            fclose(gp);
            char cmd[256];
#ifdef _WIN32
            snprintf(cmd, sizeof(cmd), "cmd /c gnuplot -persist \"%s\"", gpname);
#else
            snprintf(cmd, sizeof(cmd), "gnuplot -persist \"%s\"", gpname);
#endif
            system(cmd);
        }
    }

    {
        const char *gpname = "sod2d_p.gp";
        FILE *gp = fopen(gpname, "w");
        if (gp) {
            fprintf(gp, "set grid\n");
            fprintf(gp, "set pm3d map\n");
            fprintf(gp, "set title 'Sod 2D (general coords): Pressure (t=%.3f, NX=%d, NY=%d)'\n", T_END, NX, NY);
            fprintf(gp, "set xlabel 'x'\n");
            fprintf(gp, "set ylabel 'y'\n");
            fprintf(gp, "set cblabel 'Pressure p'\n");
            fprintf(gp, "splot 'sod2d.dat' using 1:2:6 with pm3d notitle\n");
            fclose(gp);
            char cmd[256];
#ifdef _WIN32
            snprintf(cmd, sizeof(cmd), "cmd /c gnuplot -persist \"%s\"", gpname);
#else
            snprintf(cmd, sizeof(cmd), "gnuplot -persist \"%s\"", gpname);
#endif
            system(cmd);
        }
    }
}

//  メイン関数 
int main(void)
{
    // グリッド管理パラメータ
    const int ng  = 2;                 // 幽霊格子数
    const int nxC = NX + 2*ng;         // 計算領域のセル数（幽霊格子含む）
    const int nyC = NY + 2*ng;

    const int nxN = nxC + 1;           // ノード数（セル数より1多い）
    const int nyN = nyC + 1;

    // 1次元配列でメモリ確保（(i,j) → j*nx+i でアクセス）
    // 保存量
    Conservative *U   = (Conservative*)malloc(sizeof(Conservative) * nxC * nyC);
    Conservative *U1  = (Conservative*)malloc(sizeof(Conservative) * nxC * nyC);
    Conservative *rhs = (Conservative*)malloc(sizeof(Conservative) * nxC * nyC);

    // グリッド座標
    double *xN = (double*)malloc(sizeof(double) * nxN * nyN);
    double *yN = (double*)malloc(sizeof(double) * nxN * nyN);

    // 幾何情報
    double   *cellA = (double*)malloc(sizeof(double) * nxC * nyC);
    FaceGeom *faceX = (FaceGeom*)malloc(sizeof(FaceGeom) * (nxC-1) * nyC);
    FaceGeom *faceY = (FaceGeom*)malloc(sizeof(FaceGeom) * nxC * (nyC-1));

    // フラックス
    Conservative *FxInt = (Conservative*)malloc(sizeof(Conservative) * (nxC-1) * nyC);
    Conservative *FyInt = (Conservative*)malloc(sizeof(Conservative) * nxC * (nyC-1));

    // メモリ確保チェック
    if (!U || !U1 || !rhs || !xN || !yN || !cellA || !faceX || !faceY || !FxInt || !FyInt) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // 初期設定
    build_cartesian_grid(xN, yN, nxC, nyC, ng);
    compute_geometry(xN, yN, nxC, nyC, cellA, faceX, faceY);

    // 初期条件の設定（Sod問題）
    const Primitive WL = (Primitive){RHO_L, U_L, 0.0, P_L};  // 左領域の初期状態
    const Primitive WR = (Primitive){RHO_R, U_R, 0.0, P_R};  // 右領域の初期状態

    // 全セルに初期条件を設定
    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC; i++) {
            double x,y;
            cell_center(xN, yN, nxC, i, j, &x, &y);
            // 不連続面（x=0.5）の位置で左右を分ける
            Primitive W = (x < XDIFF) ? WL : WR;
            U[idxC(i,j,nxC)] = prim_to_cons(W);
        }
    }

    // 幽霊格子を設定
    zero_slope(U, nxC, nyC, ng);

    // 時間ループ：終了時刻まで進める
    double t = 0.0;
    int step = 0;

    while (t < T_END) {
        // 1: CFL条件から時間ステップを計算
        double dt = calculate_dt(U, nxC, nyC, ng, cellA, faceX, faceY);
        if (t + dt > T_END) dt = T_END - t;  // 終了時刻を超えないように調整

        // 2段階Runge-Kutta法のステップ1
        zero_slope(U, nxC, nyC, ng);
        calculate_rhs(U, rhs, nxC, nyC, ng, cellA, faceX, faceY, FxInt, FyInt);
        // U1 = U + dt*rhs
        for (int j = 0; j < nyC; j++) {
            for (int i = 0; i < nxC; i++) {
                const int id = idxC(i,j,nxC);
                U1[id].rho   = U[id].rho   + dt * rhs[id].rho;
                U1[id].rho_u = U[id].rho_u + dt * rhs[id].rho_u;
                U1[id].rho_v = U[id].rho_v + dt * rhs[id].rho_v;
                U1[id].E     = U[id].E     + dt * rhs[id].E;
            }
        }

        // 2段階Runge-Kutta法のステップ2
        zero_slope(U1, nxC, nyC, ng);
        calculate_rhs(U1, rhs, nxC, nyC, ng, cellA, faceX, faceY, FxInt, FyInt);
        // U = 0.5*(U + (U1 + dt*rhs)) = 0.5*U + 0.5*U1 + 0.5*dt*rhs
        for (int j = 0; j < nyC; j++) {
            for (int i = 0; i < nxC; i++) {
                const int id = idxC(i,j,nxC);
                U[id].rho   = 0.5 * (U[id].rho   + U1[id].rho   + dt * rhs[id].rho);
                U[id].rho_u = 0.5 * (U[id].rho_u + U1[id].rho_u + dt * rhs[id].rho_u);
                U[id].rho_v = 0.5 * (U[id].rho_v + U1[id].rho_v + dt * rhs[id].rho_v);
                U[id].E     = 0.5 * (U[id].E     + U1[id].E     + dt * rhs[id].E);
            }
        }

        // 時間とステップ数を更新
        t += dt;
        step++;
        printf("Step: %d, Time: %.6f, dt: %.6e\n", step, t, dt);
    }

    write_and_plot(U, xN, yN, nxC, nyC, ng);

    free(U);
    free(U1);
    free(rhs);
    free(xN);
    free(yN);
    free(cellA);
    free(faceX);
    free(faceY);
    free(FxInt);
    free(FyInt);

    return 0;
}
