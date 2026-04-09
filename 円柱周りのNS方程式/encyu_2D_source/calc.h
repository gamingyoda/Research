/*------------------------------

  計算関数 2d

------------------------------*/


inline double Cons_calcE(int n, int r1){
  return p[n][r1] / (gamma0 - 1.0) + 0.5 * rho[n][r1] * (ux[n][r1] * ux[n][r1] + uy[n][r1] * uy[n][r1]);
}

inline double Cons_calcP(int n, int r1){
  return (gamma0 - 1.0) * (e[n][r1] - 0.5 * rho[n][r1] * (ux[n][r1] * ux[n][r1] + uy[n][r1] * uy[n][r1]));
}

inline double Cons_calcH(int n, int r1){
  return (e[n][r1] + p[n][r1]) / rho[n][r1]; 
}

inline double Cons_calcCpT(int n, int r1){
  return (Cons_calcE(n, r1) + Cons_calcP(n, r1)) / rho[n][r1] - 0.5 * (ux[n][r1] * ux[n][r1] + uy[n][r1] * uy[n][r1]);
}

void Cons_tmp(){
  int n, i, j, r0;

  for(n=0;n<NT;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	tmpQ[n][0][r0]  = Q[n][0][r0];
	tmpQ[n][1][r0]  = Q[n][1][r0];
	tmpQ[n][2][r0]  = Q[n][2][r0];
	tmpQ[n][3][r0]  = Q[n][3][r0];
	TurbtmpQ[n][0][r0] = TurbQ[n][0][r0];
	TurbtmpQ[n][1][r0] = TurbQ[n][1][r0];
      }
    }
  }


}
