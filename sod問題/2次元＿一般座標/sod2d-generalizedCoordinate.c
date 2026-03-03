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

#define GAMMA 1.4

#define NX 400
#define NY 400
#define X0 0.0
#define X1 1.0
#define Y0 0.0
#define Y1 1.0

#define XDIFF 0.5
#define CFL 0.5
#define T_END 0.20

#define RHO_L  1.0
#define U_L    0.0
#define P_L    1.0

#define RHO_R  0.125
#define U_R    0.0
#define P_R    0.1

typedef struct { double rho, rho_u, rho_v, E; } Conservative;
typedef struct { double rho, u, v, p; } Primitive;
typedef struct { double nx, ny, L;} FaceGeom;

static inline Conservative c_add(Conservative a, Conservative b) {
    return (Conservative){a.rho+b.rho, a.rho_u+b.rho_u, a.rho_v+b.rho_v, a.E+b.E};
}
static inline Conservative c_sub(Conservative a, Conservative b) {
    return (Conservative){a.rho-b.rho, a.rho_u-b.rho_u, a.rho_v-b.rho_v, a.E-b.E};
}
static inline Conservative c_scale(Conservative a, double s) {
    return (Conservative){a.rho*s, a.rho_u*s, a.rho_v*s, a.E*s};
}

static Primitive cons_to_prim(Conservative U)
{
    Primitive W;
    W.rho = U.rho;
    W.u   = U.rho_u / U.rho;
    W.v   = U.rho_v / U.rho;
    W.p   = (GAMMA - 1.0) * (U.E - 0.5 * U.rho * (W.u*W.u + W.v*W.v));
    return W;
}

static Conservative prim_to_cons(Primitive W)
{
    Conservative U;
    U.rho  = W.rho;
    U.rho_u = W.rho * W.u;
    U.rho_v = W.rho * W.v;
    U.E    = W.p/(GAMMA-1.0) + 0.5 * W.rho * (W.u*W.u + W.v*W.v);
    return U;
}

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

static void ROE_Flux_Normal(Primitive WL, Primitive WR, double nx, double ny, Conservative *Fout)
{

    const double tx = -ny;
    const double ty =  nx;

    Conservative UL = prim_to_cons(WL);
    Conservative UR = prim_to_cons(WR);

    const double HL = (UL.E + WL.p) / WL.rho;
    const double HR = (UR.E + WR.p) / WR.rho;

    const double uL_n = WL.u*nx + WL.v*ny;
    const double uR_n = WR.u*nx + WR.v*ny;
    const double uL_t = WL.u*tx + WL.v*ty;
    const double uR_t = WR.u*tx + WR.v*ty;

    const double sqL = sqrt(WL.rho);
    const double sqR = sqrt(WR.rho);
    const double inv = 1.0 / (sqL + sqR);

    const double uT_n = (sqL*uL_n + sqR*uR_n) * inv;
    const double uT_t = (sqL*uL_t + sqR*uR_t) * inv;
    const double HT = (sqL*HL  + sqR*HR ) * inv;

    double aT2 = (GAMMA - 1.0) * (HT - 0.5*(uT_n*uT_n + uT_t*uT_t));
    double aT = (aT2 > 0.0) ? sqrt(aT2) : 0.0;

    const double dr  = WR.rho - WL.rho;
    const double dp  = WR.p   - WL.p;
    const double dut = uR_t - uL_t;
    const double dun = uR_n - uL_n;

    const double rhoT = sqL*sqR;

    const double alpha2 = dr - dp/aT2;
    const double alpha1 = (dp - rhoT*aT*dun)/(2*aT2);
    const double alpha4 = (dp + rhoT*aT*dun)/(2*aT2);
    const double alpha3 = rhoT * dut;

    const double lam1 = uT_n - aT;
    const double lam2 = uT_n;
    const double lam3 = uT_n;
    const double lam4 = uT_n + aT;

    const double delta = 0.1 * aT;
    const double a1 = (fabs(lam1) >= delta) ? fabs(lam1) : (lam1*lam1 + delta*delta)/(2.0*delta);
    const double a2 = (fabs(lam2) >= delta) ? fabs(lam2) : (lam2*lam2 + delta*delta)/(2.0*delta);
    const double a3 = (fabs(lam3) >= delta) ? fabs(lam3) : (lam3*lam3 + delta*delta)/(2.0*delta);
    const double a4 = (fabs(lam4) >= delta) ? fabs(lam4) : (lam4*lam4 + delta*delta)/(2.0*delta);
    
    const double d_rho   = a1*alpha1 + a2*alpha2 + a4*alpha4;
    const double d_rho_un= a1*alpha1*(uT_n - aT) + a2*alpha2*uT_n + a4*alpha4*(uT_n + aT);
    const double d_rho_ut= a1*alpha1*uT_t + a2*alpha2*uT_t + a3*alpha3*1.0 + a4*alpha4*uT_t;
    const double d_E     = a1*alpha1*(HT - uT_n*aT) + a2*alpha2*0.5*(uT_n*uT_n + uT_t*uT_t) + a3*alpha3*(uT_t) + a4*alpha4*(HT + uT_n*aT);
    
    const Conservative FL = FluxX(WL);
    const Conservative GL = FluxY(WL);
    const Conservative FR = FluxX(WR);
    const Conservative GR = FluxY(WR);

    const Conservative FnL = c_add(c_scale(FL, nx), c_scale(GL, ny));
    const Conservative FnR = c_add(c_scale(FR, nx), c_scale(GR, ny));

    const double d_rho_u = d_rho_un*nx + d_rho_ut*tx;
    const double d_rho_v = d_rho_un*ny + d_rho_ut*ty;

    Fout->rho   = 0.5*(FnL.rho   + FnR.rho  ) - 0.5*d_rho;
    Fout->rho_u = 0.5*(FnL.rho_u + FnR.rho_u) - 0.5*d_rho_u;
    Fout->rho_v = 0.5*(FnL.rho_v + FnR.rho_v) - 0.5*d_rho_v;
    Fout->E     = 0.5*(FnL.E     + FnR.E    ) - 0.5*d_E;
}

static void zero_slope(Conservative *U, int nx_end, int ny_end, int ng)
{
    for (int j = 0; j < ny_end; j++) {
        for (int i = 0; i < ng; i++) {
            U[j * nx_end + i] = U[j * nx_end + ng];
            U[j * nx_end + (nx_end - 1 - i)] = U[j * nx_end + (nx_end - 1 - ng)];
        }
    }

    for (int i = 0; i < nx_end; i++) {
        for (int j = 0; j < ng; j++) {
            U[j * nx_end + i] = U[ng * nx_end + i];
            U[(ny_end - 1 - j) * nx_end + i] = U[(ny_end - 1 - ng) * nx_end + i];
        }
    }

}

static inline int idxN(int i, int j, int nxN) { return j*nxN + i; }
static inline int idxC(int i, int j, int nxC) { return j*nxC + i; }
static inline int idxFX(int i, int j, int nxC) { return j*(nxC-1) + i; }
static inline int idxFY(int i, int j, int nxC) { return j*nxC + i; }

static void build_cartesian_grid(double *xN, double *yN, int nxC, int nyC, int ng)
{
    const int nxN = nxC + 1;
    const int nyN = nyC + 1;

    const double dx = (X1 - X0)/NX;
    const double dy = (Y1 - Y0)/NY;

    for (int j = 0; j < nyN; j++) {
        for (int i = 0; i < nxN; i++) {
            const double x = X0 + (i - ng) * dx;
            const double y = Y0 + (j - ng) * dy;
            const int id = idxN(i, j, nxN);
            xN[id] = x;
            yN[id] = y;
        }
    }
}

static double quad_area(double x0,double y0,double x1,double y1,double x2,double y2,double x3,double y3)
{
    const double s = x0*y1 - x1*y0 + x1*y2 - x2*y1 + x2*y3 - x3*y2 + x3*y0 - x0*y3;
    return 0.5 * fabs(s);
}

static void compute_geometry(const double *xN, const double *yN, int nxC, int nyC, double *cellA, FaceGeom *faceX, FaceGeom *faceY)
{
    const int nxN = nxC + 1;

    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC; i++) {
            const int n00 = idxN(i,   j,   nxN);
            const int n10 = idxN(i+1, j,   nxN);
            const int n11 = idxN(i+1, j+1, nxN);
            const int n01 = idxN(i,   j+1, nxN);

            const double A = quad_area(
                xN[n00], yN[n00],
                xN[n10], yN[n10],
                xN[n11], yN[n11],
                xN[n01], yN[n01]
            );
            cellA[idxC(i,j,nxC)] = (A > 1e-14) ? A : 1e-14;
        }
    }

    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC-1; i++) {
            const int nb = idxN(i+1, j,   nxN);
            const int nt = idxN(i+1, j+1, nxN);
            const double ex = xN[nt] - xN[nb];
            const double ey = yN[nt] - yN[nb];
            const double L  = hypot(ex, ey);
            const double invL = (L > 1e-14) ? 1.0 / L : 0.0;
            const double nx = ey * invL;
            const double ny = -ex * invL;
            faceX[idxFX(i,j,nxC)] = (FaceGeom){nx, ny, (L > 1e-14 ? L : 1e-14)};
        }
    }

    for (int j = 0; j < nyC-1; j++) {
        for (int i = 0; i < nxC; i++) {
            const int nl = idxN(i,   j+1, nxN);
            const int nr = idxN(i+1, j+1, nxN);
            const double ex = xN[nr] - xN[nl];
            const double ey = yN[nr] - yN[nl];
            const double L  = hypot(ex, ey);
            const double invL = (L > 1e-14) ? 1.0 / L : 0.0;
            const double nx = -ey * invL;
            const double ny = ex * invL;
            faceY[idxFY(i,j,nxC)] = (FaceGeom){nx, ny, (L > 1e-14 ? L : 1e-14)};
        }
    }
}

static void cell_center(const double *xN, const double *yN, int nxC, int i, int j, double *xc, double *yc)
{
    const int nxN = nxC + 1;
    const int n00 = idxN(i,   j,   nxN);
    const int n10 = idxN(i+1, j,   nxN);
    const int n11 = idxN(i+1, j+1, nxN);
    const int n01 = idxN(i,   j+1, nxN);
    *xc = 0.25 * (xN[n00] + xN[n10] + xN[n11] + xN[n01]);
    *yc = 0.25 * (yN[n00] + yN[n10] + yN[n11] + yN[n01]);
}


static void calculate_rhs(Conservative *U, Conservative *rhs, int nxC, int nyC, int ng, double *cellA, FaceGeom *faceX, const FaceGeom *faceY, Conservative *FxInt, Conservative *FyInt)
{
    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC; i++) {
            rhs[idxC(i,j,nxC)] = (Conservative){0,0,0,0};
        }
    }

    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC-1; i++) {
            Primitive WL = cons_to_prim(U[idxC(i,j,nxC)]);
            Primitive WR = cons_to_prim(U[idxC(i+1,j,nxC)]);
            FaceGeom fg = faceX[idxFX(i,j,nxC)];

            Conservative Fn;
            ROE_Flux_Normal(WL, WR, fg.nx, fg.ny, &Fn);
            FxInt[idxFX(i,j,nxC)] = c_scale(Fn, fg.L);
        }
    }

    for (int j = 0; j < nyC - 1; j++) {
        for (int i = 0; i < nxC; i++) {
            Primitive WL = cons_to_prim(U[idxC(i,j,nxC)]);
            Primitive WR = cons_to_prim(U[idxC(i,j+1,nxC)]);
            FaceGeom fg = faceY[idxFY(i,j,nxC)];

            Conservative Fn;
            ROE_Flux_Normal(WL, WR, fg.nx, fg.ny, &Fn);
            FyInt[idxFY(i,j,nxC)] = c_scale(Fn, fg.L);
        }
    }

    for (int j = ng; j < nyC-ng; j++) {
        for (int i = ng; i < nxC-ng; i++) {
            const double A = cellA[idxC(i,j,nxC)];

            const Conservative FxR = FxInt[idxFX(i,   j, nxC)];
            const Conservative FxL = FxInt[idxFX(i-1, j, nxC)];
            const Conservative FyT = FyInt[idxFY(i, j,   nxC)];
            const Conservative FyB = FyInt[idxFY(i, j-1, nxC)];

            Conservative div = c_add(c_sub(FxR, FxL), c_sub(FyT, FyB));
            rhs[idxC(i,j,nxC)] = c_scale(div, -1.0/A);
        }
    }
}

static double calculate_dt(Conservative *U, int nxC, int nyC, int ng, double *cellA, FaceGeom *faceX, FaceGeom *faceY)
{
    double dt_min = 1e300;

    for (int j = ng; j < nyC-ng; j++) {
        for (int i = ng; i < nxC-ng; i++) {
            const Primitive W = cons_to_prim(U[idxC(i,j,nxC)]);
            if (W.rho <= 0.0 || W.p <= 0.0) continue;
            const double a = sqrt(GAMMA * W.p / W.rho);

            double sum = 0.0;

            {
                const FaceGeom fg = faceX[idxFX(i, j, nxC)];
                const double un = W.u*fg.nx + W.v*fg.ny;
                sum += (fabs(un) + a) * fg.L;
            }
            {
                const FaceGeom fg = faceX[idxFX(i-1, j, nxC)];
                const double un = W.u*fg.nx + W.v*fg.ny;
                sum += (fabs(un) + a) * fg.L;
            }
            {
                const FaceGeom fg = faceY[idxFY(i, j, nxC)];
                const double un = W.u*fg.nx + W.v*fg.ny;
                sum += (fabs(un) + a) * fg.L;
            }
            {
                const FaceGeom fg = faceY[idxFY(i, j-1, nxC)];
                const double un = W.u*fg.nx + W.v*fg.ny;
                sum += (fabs(un) + a) * fg.L;
            }

            const double A = cellA[idxC(i,j,nxC)];
            const double dt_cell = CFL * A / sum;
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

int main(void)
{
    const int ng  = 2;
    const int nxC = NX + 2*ng;
    const int nyC = NY + 2*ng;

    const int nxN = nxC + 1;
    const int nyN = nyC + 1;

    Conservative *U   = (Conservative*)malloc(sizeof(Conservative) * nxC * nyC);
    Conservative *U1  = (Conservative*)malloc(sizeof(Conservative) * nxC * nyC);
    Conservative *rhs = (Conservative*)malloc(sizeof(Conservative) * nxC * nyC);

    double *xN = (double*)malloc(sizeof(double) * nxN * nyN);
    double *yN = (double*)malloc(sizeof(double) * nxN * nyN);

    double   *cellA = (double*)malloc(sizeof(double) * nxC * nyC);
    FaceGeom *faceX = (FaceGeom*)malloc(sizeof(FaceGeom) * (nxC-1) * nyC);
    FaceGeom *faceY = (FaceGeom*)malloc(sizeof(FaceGeom) * nxC * (nyC-1));

    Conservative *FxInt = (Conservative*)malloc(sizeof(Conservative) * (nxC-1) * nyC);
    Conservative *FyInt = (Conservative*)malloc(sizeof(Conservative) * nxC * (nyC-1));

    if (!U || !U1 || !rhs || !xN || !yN || !cellA || !faceX || !faceY || !FxInt || !FyInt) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    build_cartesian_grid(xN, yN, nxC, nyC, ng);
    compute_geometry(xN, yN, nxC, nyC, cellA, faceX, faceY);

    const Primitive WL = (Primitive){RHO_L, U_L, 0.0, P_L};
    const Primitive WR = (Primitive){RHO_R, U_R, 0.0, P_R};

    for (int j = 0; j < nyC; j++) {
        for (int i = 0; i < nxC; i++) {
            double x,y;
            cell_center(xN, yN, nxC, i, j, &x, &y);
            Primitive W = (x < XDIFF) ? WL : WR;
            U[idxC(i,j,nxC)] = prim_to_cons(W);
        }
    }

    zero_slope(U, nxC, nyC, ng);

    double t = 0.0;
    int step = 0;

    while (t < T_END) {
        double dt = calculate_dt(U, nxC, nyC, ng, cellA, faceX, faceY);
        if (t + dt > T_END) dt = T_END - t;

        zero_slope(U, nxC, nyC, ng);
        calculate_rhs(U, rhs, nxC, nyC, ng, cellA, faceX, faceY, FxInt, FyInt);
        for (int j = 0; j < nyC; j++) {
            for (int i = 0; i < nxC; i++) {
                const int id = idxC(i,j,nxC);
                U1[id].rho   = U[id].rho   + dt * rhs[id].rho;
                U1[id].rho_u = U[id].rho_u + dt * rhs[id].rho_u;
                U1[id].rho_v = U[id].rho_v + dt * rhs[id].rho_v;
                U1[id].E     = U[id].E     + dt * rhs[id].E;
            }
        }

        zero_slope(U1, nxC, nyC, ng);
        calculate_rhs(U1, rhs, nxC, nyC, ng, cellA, faceX, faceY, FxInt, FyInt);
        for (int j = 0; j < nyC; j++) {
            for (int i = 0; i < nxC; i++) {
                const int id = idxC(i,j,nxC);
                U[id].rho   = 0.5 * (U[id].rho   + U1[id].rho   + dt * rhs[id].rho);
                U[id].rho_u = 0.5 * (U[id].rho_u + U1[id].rho_u + dt * rhs[id].rho_u);
                U[id].rho_v = 0.5 * (U[id].rho_v + U1[id].rho_v + dt * rhs[id].rho_v);
                U[id].E     = 0.5 * (U[id].E     + U1[id].E     + dt * rhs[id].E);
            }
        }

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
