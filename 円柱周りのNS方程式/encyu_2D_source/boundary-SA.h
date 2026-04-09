/***************************/
/*                         */
/*      境界条件 2d        */
/*                         */
/***************************/

/*******************************************************/
/*                                                     */
/*                   壁面境界条件                      */
/* r0は壁近傍のセル r1,r2は壁内の第一格子点,第二格子点 */
/*                                                     */
/*******************************************************/
void wall_boundary(int n, int r0, int r1, int r2){
  double Mu, tmpT, w_wall;

  tmpT = (Cons_calcP(n, r0) / (rho[n][r0] * Rair)) / T_0;
  Mu = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0);
  w_wall = 60.0 * Mu / (rho[n][r0] * 0.09 * pow(d_wall[n][r0], 2.0));

  p[n][r1]      = p[n][r0];
  rho[n][r1]    = rho[n][r0];
  ux[n][r1]     = -ux[n][r0];
  uy[n][r1]     = -uy[n][r0];
  e[n][r1]      = Cons_calcE(n, r1);
  NuSA[n][r1]   = - NuSA[n][r0];
  Mut[n][r1]    = - Mut[n][r0];

  p[n][r2]      = p[n][r1];
  rho[n][r2]    = rho[n][r1];
  ux[n][r2]     = ux[n][r1];
  uy[n][r2]     = uy[n][r1];
  e[n][r2]      = Cons_calcE(n, r2);
  NuSA[n][r2]   = NuSA[n][r1];
  Mut[n][r2]    = Mut[n][r1];

}

/*******************************************************/
/*                                                     */
/*                   周期境界条件                      */
/*        r0は入れ替える前の値 r1は入れ替えたい値      */
/*                                                     */
/*******************************************************/
void periodic_boundary(int n, int r0, int r1){
  p[n][r0]      = p[n][r1];
  rho[n][r0]    = rho[n][r1];
  ux[n][r0]     = ux[n][r1];
  uy[n][r0]     = uy[n][r1];
  e[n][r0]      = Cons_calcE(n, r0);
  NuSA[n][r0]   = NuSA[n][r1];
  Mut[n][r0]    = Mut[n][r1];
  RA_LE[n][r0]  = RA_LE[n][r1];
/* #ifdef LU_SGS */
/*   dQ[n][0][r0]  = dQ[n][0][r1]; */
/*   dQ[n][1][r0]  = dQ[n][1][r1]; */
/*   dQ[n][2][r0]  = dQ[n][2][r1]; */
/*   dQ[n][3][r0]  = dQ[n][3][r1]; */
/* #endif */
}

/*******************************************************/
/*                                                     */
/*                   出口境界条件                      */
/*        r0は入れ替える前の値 r1は入れ替えたい値      */
/*                                                     */
/*******************************************************/
void exit_boundary(int n, int r0, int r1){
  ux[n][r0]     = ux[n][r1];
  uy[n][r0]     = uy[n][r1];
  rho[n][r0]    = rho0;
  p[n][r0]      = p0;
  e[n][r0]      = Cons_calcE(n, r0);
  NuSA[n][r0]   = NuSA[n][r1];
  Mut[n][r0]    = Mut[n][r1];
}

/*******************************************************/
/*                                                     */
/*                   入口境界条件                      */
/*        r0は入れ替える前の値 r1は入れ替えたい値      */
/*                                                     */
/*******************************************************/
void inter_boundary(int n, int r0, int r1){
  rho[n][r0]    = rho0;
  p[n][r0]      = p0;
  ux[n][r0]     = u0;
  uy[n][r0]     = 0.0;
  e[n][r0]      = Cons_calcE(n, r0);
  k_turb[n][r0] = 1.0e-7 * u0 * u0;
  omega[n][r0]  = u0 * 150 * 0.1;
  NuSA[n][r0]   = mu_0 / rho0;
  Mut[n][r0]    = k_turb[n][r0] * rho[n][r0] / omega[n][r0];
}

/*******************************************************/
/*                                                     */
/*                  受け渡し境界条件                   */
/*    n0,r0は入れ替える前の値 n1,r1は入れ替えたい値    */
/*                                                     */
/*******************************************************/
void ukewatasi(int n0, int r0, int n1, int r1){
  p[n0][r0]      = p[n1][r1];
  rho[n0][r0]    = rho[n1][r1];
  ux[n0][r0]     = ux[n1][r1];
  uy[n0][r0]     = uy[n1][r1];
  e[n0][r0]      = Cons_calcE(n0, r0);
  k_turb[n0][r0] = k_turb[n1][r1];
  omega[n0][r0]  = omega[n1][r1];
  NuSA[n0][r0]   = NuSA[n1][r1];
  Mut[n0][r0]    = Mut[n1][r1];
  RA_LE[n0][r0]  = RA_LE[n1][r1];
/* #ifdef LU_SGS */
/*   dQ[n0][0][r0]  = dQ[n1][0][r1]; */
/*   dQ[n0][1][r0]  = dQ[n1][1][r1]; */
/*   dQ[n0][2][r0]  = dQ[n1][2][r1]; */
/*   dQ[n0][3][r0]  = dQ[n1][3][r1]; */
/* #endif */
}

/*******************************************************/
/*              Linear Interpolation                   */
/*******************************************************/
inline static double Interpolation(double y0, double y1, double x0, double x1, double X){
  return y0 + (y1 - y0) * (X - x0) / (x1 - x0);
}

/*******************************************************/
/*        Linear Interpolation  calculation            */
/*                n1は値を比べる方の値                 */
/*******************************************************/
void interpolation_boundary(int n0, int r0, int n1, int j_n1){

  unsigned int i;
  int r1;
  int rn;
  double l;

  l = d_wall[n0][r0];

  for(i=2;i<it[n1]-1;i++){
    r1 = dim[n1](i, j_n1);
    rn = r1 + dG[n1];
    if( d_wall[n1][r1] <= l && l <= d_wall[n1][rn] ) { break; }
  }


  p[n0][r0]      = Interpolation(p[n1][r1],   p[n1][rn],   d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  rho[n0][r0]    = Interpolation(rho[n1][r1], rho[n1][rn], d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  ux[n0][r0]     = Interpolation(ux[n1][r1],  ux[n1][rn],  d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  uy[n0][r0]     = Interpolation(uy[n1][r1],  uy[n1][rn],  d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  e[n0][r0]      = Cons_calcE(n0, r0);
  k_turb[n0][r0] = Interpolation(k_turb[n1][r1],  k_turb[n1][rn],  d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  omega[n0][r0]  = Interpolation(omega[n1][r1],  omega[n1][rn],  d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  Mut[n0][r0]    = Interpolation(Mut[n1][r1],  Mut[n1][rn],  d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
  NuSA[n0][r0]    = Interpolation(NuSA[n1][r1],  NuSA[n1][rn],  d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]);
/* #ifdef LU_SGS */
/*   dQ[n0][0][r0]      = Interpolation(dQ[n1][0][r1],   dQ[n1][0][rn],   d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]); */
/*   dQ[n0][1][r0]      = Interpolation(dQ[n1][1][r1],   dQ[n1][1][rn],   d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]); */
/*   dQ[n0][2][r0]      = Interpolation(dQ[n1][2][r1],   dQ[n1][2][rn],   d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]); */
/*   dQ[n0][3][r0]      = Interpolation(dQ[n1][3][r1],   dQ[n1][3][rn],   d_wall[n1][r1], d_wall[n1][rn], d_wall[n0][r0]); */
/* #endif */
}


void boundary(){
  int i, j, r0, r1, r2, n, O_ini, O_end;
  double vr, vsita, r, p_0, rho_0, T, S_, k1, k2;
  double xi, sita;
  int n0, n1, n2;

  //壁面の境界条件
  n = N_IN;
  for(j=0;j<jt[n]-1;j++){
    r0 = dim[n](2, j);
    r1 = dim[n](1, j);
    r2 = dim[n](0, j);
    wall_boundary(n, r0, r1, r2);
  }


  //出口境界条件:静圧固定、その他は内側から保管
  n = N_WAKE;
  for(j=0;j<jt[n]-1;j++){
    r0 = dim[n](it[n]-3, j);
    r1 = dim[n](it[n]-4, j);
    exit_boundary(n, r0, r1);

    r0 = dim[n](it[n]-2, j);
    r1 = dim[n](it[n]-3, j);
    exit_boundary(n, r0, r1);
  }

  //入口境界条件:速度と全圧が変数、その他は内側から保管
  n = N_OUT;
  for(j=0;j<jt[n]-1;j++){
    r0 = dim[n](it[n]-3, j);
    r1 = dim[n](it[n]-4, j);
    inter_boundary(n, r0, r1);

    r0 = dim[n](it[n]-2, j);
    r1 = dim[n](it[n]-3, j);
    inter_boundary(n, r0, r1);
  }


  //周期境界条件
  n = N_IN;
  for(i=0;i<it[n]-1;i++){
    r1 = dim[n](i, jt[n]-5);
    r0 = dim[n](i, 0);
    periodic_boundary(n, r0, r1);

    r1 = dim[n](i, jt[n]-4);
    r0 = dim[n](i, 1);
    periodic_boundary(n, r0, r1);

    r1 = dim[n](i, 2);
    r0 = dim[n](i, jt[n]-3);
    periodic_boundary(n, r0, r1);

    r1 = dim[n](i, 3);
    r0 = dim[n](i, jt[n]-2);
    periodic_boundary(n, r0, r1);
  }

  //領域2と3の継ぎ目を線形補間
  n1 = N_WAKE;
  n2 = N_OUT;
  for(i=2;i<it[n1]-3;i++){
    r1 = dim[n1](i, 0);
    interpolation_boundary(n1, r1, n2, jt[n2]-5);

    r1 = dim[n1](i, 1);
    interpolation_boundary(n1, r1, n2, jt[n2]-4);

    r1 = dim[n1](i, jt[n1]-3);
    interpolation_boundary(n1, r1, n2, 2);

    r1 = dim[n1](i, jt[n1]-2);
    interpolation_boundary(n1, r1, n2, 3);
  }

  for(i=2;i<it[n2]-3;i++){
    r2 = dim[n2](i, 0);
    interpolation_boundary(n2, r2, n1, jt[n1]-5);

    r2 = dim[n2](i, 1);
    interpolation_boundary(n2, r2, n1, jt[n1]-4);

    r2 = dim[n2](i, jt[n2]-3);
    interpolation_boundary(n2, r2, n1, 2);

    r2 = dim[n2](i, jt[n2]-2);
    interpolation_boundary(n2, r2, n1, 3);
  }


  //領域1と2との値の受け渡し
  n0 = N_IN;
  n1 = N_WAKE;
  for(j=0;j<jt[n0]-3-jmin;j++){
    r0 = dim[n0](it[n0]-5, jmin+j);
    r1 = dim[n1](0,        j);
    ukewatasi(n1, r1, n0, r0);

    r0 = dim[n0](it[n0]-4, jmin+j);
    r1 = dim[n1](1,        j);
    ukewatasi(n1, r1, n0, r0);

    r0 = dim[n0](it[n0]-3, jmin+j);
    r1 = dim[n1](2,        j);
    ukewatasi(n0, r0, n1, r1);

    r0 = dim[n0](it[n0]-2, jmin+j);
    r1 = dim[n1](3,        j);
    ukewatasi(n0, r0, n1, r1);
  }

  for(j=jt[n0]-3-jmin;j<jt[n1]-1;j++){
    r0 = dim[n0](it[n0]-5, j-jmax+2);
    r1 = dim[n1](0,        j);
    ukewatasi(n1, r1, n0, r0);

    r0 = dim[n0](it[n0]-4, j-jmax+2);
    r1 = dim[n1](1,        j);
    ukewatasi(n1, r1, n0, r0);

    r0 = dim[n0](it[n0]-3, j-jmax+2);
    r1 = dim[n1](2,        j);
    ukewatasi(n0, r0, n1, r1);

    r0 = dim[n0](it[n0]-2, j-jmax+2);
    r1 = dim[n1](3,        j);
    ukewatasi(n0, r0, n1, r1);
  }

  //領域1と3との値の受け渡し
  n0 = N_IN;
  n2 = N_OUT;
  for(j=0;j<jt[n2]-1;j++){
    r0 = dim[n0](it[0]-5, jmax-2+j);
    r2 = dim[n2](0,       j);
    ukewatasi(n2, r2, n0, r0);

    r0 = dim[n0](it[0]-4, jmax-2+j);
    r2 = dim[n2](1,       j);
    ukewatasi(n2, r2, n0, r0);

    r0 = dim[n0](it[0]-3, jmax-2+j);
    r2 = dim[n2](2,       j);
    ukewatasi(n0, r0, n2, r2);

    r0 = dim[n0](it[0]-2, jmax-2+j);
    r2 = dim[n2](3,       j);
    ukewatasi(n0, r0, n2, r2);
  }


}
