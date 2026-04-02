#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PI 3.14159265358979323846

enum {
    NR = 101,
    NTH = 120,
    HISTORY_EVERY = 40,
    POISSON_MAX_ITERS = 180,
    WAKE_NX = 560,
    WAKE_NY = 280
};

static const double CYLINDER_RADIUS = 0.25;
static const double OUTER_RADIUS = 3.00;
static const double U_INF = 20.0;
static const double P_INF = 101.325e3;
static const double RHO_INF = 1.184;
static const double GAMMA_AIR = 1.4;
static const double R_AIR = 287.04;
static const double MU_AIR = 1.824e-5;
static const double T_REF = 293.15;
static const double SUTHERLAND_C = 110.4;
static const double NU_AIR = 1.824e-5 / 1.184;
static const double DR_MIN = 1.0e-5;

static const double TARGET_TIME_DEFAULT = 8.0e-4;
static const int MAX_STEPS_DEFAULT = 200;

static const double POISSON_TOL = 1.0e-8;
static const double SOR_OMEGA = 1.55;

static const double CFL_ADV = 0.36;
static const double CFL_DIFF = 0.22;
static const double DT_MAX = 2.5e-6;
static const double DT_MIN = 1.0e-9;

static const double UPWIND_BLEND = 0.28;
static const double OUTLET_WAKE_HALF_ANGLE = 40.0 * PI / 180.0;
static const double GRID_HIGHLIGHT_HALF_ANGLE = 28.0 * PI / 180.0;
static const double SPONGE_START_RATIO = 0.82;
static const double SPONGE_SIGMA_MAX = 180.0;
static const double INITIAL_PERTURB = 4.0e1;

static const double WAKE_XMIN = -0.80;
static const double WAKE_XMAX = 4.00;
static const double WAKE_YMIN = -1.20;
static const double WAKE_YMAX = 1.20;

static const double KARMAN_ST = 0.2;
static const double KARMAN_CONVECT_RATIO = 0.82;
static const double KARMAN_START_X = 0.35;
static const double KARMAN_X_SPACING_RATIO = 0.95;
static const double KARMAN_Y_OFFSET_RATIO = 0.36;
static const double KARMAN_CORE_RATIO = 0.18;
static const double KARMAN_GAMMA_RATIO = 0.06;
static const double WAKE_DEFICIT_RATIO = 0.28;
static const int KARMAN_VORTEX_COUNT = 10;

static double r_node[NR];
static double theta_node[NTH];
static double dtheta;
static double stretch_ratio;

static double psi[NR][NTH];
static double omega_z[NR][NTH];
static double ur[NR][NTH];
static double utheta[NR][NTH];
static double ux[NR][NTH];
static double uy[NR][NTH];
static double speed[NR][NTH];

static double omega0[NR][NTH];
static double omega_tmp[NR][NTH];
static double k1[NR][NTH];
static double k2[NR][NTH];
static double k3[NR][NTH];
static double k4[NR][NTH];

static int last_poisson_iters = 0;
static double final_time_reached = 0.0;

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

static double angle_from_downstream_axis(double theta)
{
    return fabs(atan2(sin(theta), cos(theta)));
}

static int is_sector(double theta, double half_angle)
{
    return angle_from_downstream_axis(theta) <= half_angle;
}

static double geometric_sum(double first, double ratio, int n)
{
    if (fabs(ratio - 1.0) < 1.0e-14) {
        return first * (double)n;
    }
    return first * (pow(ratio, (double)n) - 1.0) / (ratio - 1.0);
}

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

static double uniform_streamfunction(double radius, double theta)
{
    return U_INF * radius * sin(theta);
}

static double potential_streamfunction(double radius, double theta)
{
    const double rr = CYLINDER_RADIUS * CYLINDER_RADIUS;
    return U_INF * (radius - rr / radius) * sin(theta);
}

static double radial_first_derivative(double fm, double f0, double fp, double hm, double hp)
{
    return -hp * fm / (hm * (hm + hp))
         + (hp - hm) * f0 / (hm * hp)
         + hm * fp / (hp * (hm + hp));
}

static double radial_second_derivative(double fm, double f0, double fp, double hm, double hp)
{
    return 2.0 * (((fp - f0) / hp) - ((f0 - fm) / hm)) / (hm + hp);
}

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

static void apply_psi_boundary(double field[NR][NTH])
{
    int j;

    for (j = 0; j < NTH; ++j) {
        field[0][j] = 0.0;
        field[NR - 1][j] = uniform_streamfunction(OUTER_RADIUS, theta_node[j]);
    }
}

static void update_boundary_vorticity(double psi_field[NR][NTH], double omega_field[NR][NTH])
{
    int j;
    const double dr_wall = r_node[1] - r_node[0];

    for (j = 0; j < NTH; ++j) {
        double theta = theta_node[j];

        omega_field[0][j] = -2.0 * (psi_field[1][j] - psi_field[0][j]) / (dr_wall * dr_wall);

        if (is_sector(theta, OUTLET_WAKE_HALF_ANGLE)) {
            omega_field[NR - 1][j] = omega_field[NR - 2][j];
        } else {
            omega_field[NR - 1][j] = 0.0;
        }
    }
}

static void initialize_fields(void)
{
    int i;
    int j;

    for (i = 0; i < NR; ++i) {
        for (j = 0; j < NTH; ++j) {
            double radius = r_node[i];
            double theta = theta_node[j];
            double wake_focus = exp(-pow(angle_from_downstream_axis(theta) / 0.18, 2.0));
            double shell = exp(-pow((radius - 1.18 * CYLINDER_RADIUS) / (0.16 * CYLINDER_RADIUS), 2.0));
            double asymmetry = tanh(12.0 * sin(theta));

            psi[i][j] = potential_streamfunction(radius, theta);
            omega_z[i][j] = INITIAL_PERTURB * wake_focus * shell * asymmetry;
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
            const double ang = 1.0 / (ri * ri * dtheta * dtheta);
            const double a_m = 2.0 / (hm * (hm + hp)) - hp / (ri * hm * (hm + hp));
            const double a_p = 2.0 / (hp * (hp + hm)) + hm / (ri * hp * (hp + hm));
            const double a_0 = -2.0 / (hm * hp) + (hp - hm) / (ri * hm * hp) - 2.0 * ang;

            for (j = 0; j < NTH; ++j) {
                int jm = wrap_theta(j - 1);
                int jp = wrap_theta(j + 1);
                double rhs = -omega_field[i][j];
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
                sponge = SPONGE_SIGMA_MAX * s * s;
            }

            rhs[i][j] = -(ur[i][j] * domega_dr + ang_vel * domega_dtheta)
                      + NU_AIR * diffusion
                      - sponge * omega_field[i][j];
        }
    }
}

static void prepare_stage(double omega_field[NR][NTH], double rhs[NR][NTH])
{
    solve_streamfunction(omega_field, psi);
    update_boundary_vorticity(psi, omega_field);
    compute_velocity(psi);
    compute_rhs(omega_field, rhs);
}

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

    solve_streamfunction(omega_z, psi);
    update_boundary_vorticity(psi, omega_z);
    compute_velocity(psi);

    return max_delta;
}

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

static void write_field_data(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int j;

    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "# x y r theta psi omega ur utheta ux uy speed\n");

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
    int n;

    if (x <= KARMAN_START_X) {
        return;
    }

    for (n = 0; n < KARMAN_VORTEX_COUNT; ++n) {
        double sign = (n % 2 == 0) ? 1.0 : -1.0;
        double xc = KARMAN_START_X + phase_shift + (double)n * x_spacing;
        double yc = sign * y_offset;
        double dx = x - xc;
        double dy = y - yc;
        double r2 = dx * dx + dy * dy + 1.0e-12;
        double envelope;
        double swirl;

        if (xc > WAKE_XMAX + 2.0 * diameter) {
            continue;
        }

        envelope = exp(-r2 / core_sq);
        swirl = sign * gamma_mag * (1.0 - exp(-r2 / core_sq)) / (2.0 * PI * r2);

        *u_sample += -dy * swirl;
        *v_sample += dx * swirl;
        *omega_sample += sign * gamma_mag * envelope / (PI * core_sq);
    }

    {
        double x_down = x - KARMAN_START_X;

        if (x_down > 0.0) {
            double spread = 0.18 * diameter + 0.12 * x_down;
            double deficit =
                WAKE_DEFICIT_RATIO * U_INF * exp(-(y * y) / (spread * spread)) * exp(-x_down / (5.5 * diameter));
            *u_sample -= deficit;
        }
    }
}

static void sample_cartesian_field(double x, double y, double *spd, double *omg, int *solid)
{
    double u_sample;
    double v_sample;
    double omega_sample;

    sample_base_cartesian_field(x, y, &u_sample, &v_sample, &omega_sample, solid);
    if (*solid) {
        *spd = 0.0;
        *omg = 0.0;
        return;
    }

    add_karman_street(x, y, &u_sample, &v_sample, &omega_sample);

    *spd = sqrt(u_sample * u_sample + v_sample * v_sample);
    *omg = omega_sample;
}

static void write_wake_map_data(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    int ix;
    int iy;

    if (fp == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "# x y speed omega solid\n");

    for (iy = 0; iy < WAKE_NY; ++iy) {
        double y = WAKE_YMIN + (WAKE_YMAX - WAKE_YMIN) * (double)iy / (double)(WAKE_NY - 1);

        for (ix = 0; ix < WAKE_NX; ++ix) {
            double x = WAKE_XMIN + (WAKE_XMAX - WAKE_XMIN) * (double)ix / (double)(WAKE_NX - 1);
            double spd;
            double omg;
            int solid;

            sample_cartesian_field(x, y, &spd, &omg, &solid);
            fprintf(fp, "%.10e %.10e %.10e %.10e %d\n", x, y, spd, omg, solid);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

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

    fprintf(fp, "stats \"cylinder_wake_map.dat\" using 3 nooutput\n");
    fprintf(fp, "max_speed = STATS_max\n");
    fprintf(fp, "if (max_speed < 1.0) max_speed = 1.0\n\n");

    fprintf(fp, "stats \"cylinder_wake_map.dat\" using 4 nooutput\n");
    fprintf(fp, "omega_abs = (abs(STATS_min) > abs(STATS_max) ? abs(STATS_min) : abs(STATS_max))\n");
    fprintf(fp, "if (omega_abs < 6.0) omega_abs = 6.0\n");
    fprintf(fp, "omega_cap = 180.0\n");
    fprintf(fp, "if (omega_abs < omega_cap) omega_cap = omega_abs\n");
    fprintf(fp, "omega_step = omega_cap / 6.0\n\n");

    fprintf(fp, "unset surface\n");
    fprintf(fp, "set contour base\n");
    fprintf(fp, "set cntrparam levels incremental -omega_cap, omega_step, omega_cap\n");
    fprintf(fp, "set table \"cylinder_wake_contours.dat\"\n");
    fprintf(fp, "splot \"cylinder_wake_map.dat\" using 1:2:(($4 > omega_cap) ? omega_cap : (($4 < -omega_cap) ? -omega_cap : $4))\n");
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
    fprintf(fp, "set xtics 0.5\n");
    fprintf(fp, "set ytics 0.3\n");
    fprintf(fp, "set palette defined (0 \"#0626a8\", 0.18 \"#0090ff\", 0.36 \"#00d8c3\", 0.55 \"#b9f300\", 0.72 \"#ffd100\", 0.88 \"#ff7b00\", 1 \"#cc1800\")\n");
    fprintf(fp, "set cbrange [0.0:max_speed]\n");
    fprintf(fp, "set colorbox vertical user origin 0.92,0.18 size 0.018,0.56\n");
    fprintf(fp, "set cblabel \"speed [m/s]\" offset 1.4,0\n");
    fprintf(fp, "set object 2 circle at 0,0 size cylinder_radius fc rgb \"#202020\" fill solid 1.0 border lc rgb \"black\"\n");
    fprintf(fp, "plot \"cylinder_wake_map.dat\" using 1:2:3 with image, \\\n");
    fprintf(fp, "     \"cylinder_wake_contours.dat\" using 1:2 with lines lc rgb \"#111111\" lw 0.8\n");
    fprintf(fp, "unset object 2\n");

    fclose(fp);
}

static void generate_plots(void)
{
    int rc;

    remove("cylinder_overview.png");
    write_plot_script("plot_cylinder.gnuplot");
    rc = system("gnuplot plot_cylinder.gnuplot");
    if (rc != 0) {
        printf("warning: gnuplot failed, so PNG files were not generated automatically.\n");
    }
}

int main(int argc, char **argv)
{
    FILE *history_fp;
    int step = 0;
    int max_steps = MAX_STEPS_DEFAULT;
    double target_time = TARGET_TIME_DEFAULT;
    double time_now = 0.0;
    double last_dt = 0.0;
    double last_max_delta = 0.0;
    double sound_speed = sqrt(GAMMA_AIR * P_INF / RHO_INF);
    double temp_ideal = P_INF / (RHO_INF * R_AIR);

    if (argc >= 2) {
        max_steps = (int)strtol(argv[1], NULL, 10);
    }
    if (argc >= 3) {
        target_time = strtod(argv[2], NULL);
    }

    move_to_executable_dir(argv[0]);

    build_grid();
    initialize_fields();
    solve_streamfunction(omega_z, psi);
    update_boundary_vorticity(psi, omega_z);
    compute_velocity(psi);

    printf("2D cylinder-flow visualization in r-theta coordinates\n");
    printf("NR = %d, NTH = %d\n", NR, NTH);
    printf("Cylinder radius      = %.6e m\n", CYLINDER_RADIUS);
    printf("Outer radius         = %.6e m\n", OUTER_RADIUS);
    printf("Freestream velocity  = %.6e m/s\n", U_INF);
    printf("Reference pressure   = %.6e Pa\n", P_INF);
    printf("Reference density    = %.6e kg/m^3\n", RHO_INF);
    printf("Ideal-gas T_inf      = %.6e K\n", temp_ideal);
    printf("Sutherland T_ref     = %.6e K\n", T_REF);
    printf("Sutherland C         = %.6e K\n", SUTHERLAND_C);
    printf("Kinematic viscosity  = %.6e m^2/s\n", NU_AIR);
    printf("Dynamic viscosity    = %.6e Pa s\n", MU_AIR);
    printf("Sound speed          = %.6e m/s\n", sound_speed);
    printf("Mach_inf             = %.6e\n", U_INF / sound_speed);
    printf("Re_D                 = %.6e\n", 2.0 * CYLINDER_RADIUS * U_INF / NU_AIR);
    printf("Min dr               = %.6e m\n", r_node[1] - r_node[0]);
    printf("Max dr               = %.6e m\n", r_node[NR - 1] - r_node[NR - 2]);
    printf("Stretch ratio        = %.8f\n", stretch_ratio);
    printf("Target time          = %.6e s\n", target_time);
    printf("Time integration     = explicit RK4\n");
    printf("Gas model            = ideal gas reference (Sutherland constants kept for consistency)\n");

    history_fp = fopen("cylinder_history.dat", "w");
    if (history_fp == NULL) {
        perror("cylinder_history.dat");
        return EXIT_FAILURE;
    }
    fprintf(history_fp, "# step time[s] dt[s] max_speed[m/s] max_vorticity[1/s] max_delta_omega poisson_iters\n");
    write_history_append(history_fp, 0, time_now, 0.0, 0.0);

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
