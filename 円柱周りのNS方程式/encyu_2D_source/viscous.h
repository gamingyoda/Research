/*--------------------------------

  viscous calc
  2d un-turb

---------------------------------*/


void Viscous_calc_xi(int n, int r0){
  double mu, Mueff, Mut_xi;
  double tmpT;
  double T_1;
  double T_2;
  double T_3;
  double T_4;
  double T_5;
  double T_6;
  double Txx;
  double Txy;
  double Tyy;
  double Tx;
  double Ty;
  double u_x;
  double u_y;
  double v_x;
  double v_y;
  double u_ave1;
  double u_ave2;
  double v_ave1;
  double v_ave2;
  double kx, ky, Jaco0, Jaco1, Jaco2, Jaco3, Jaco4;
  double xi_x, xi_y;
  double eta_x1, eta_y1, eta_x2, eta_y2, eta_x3, eta_y3, eta_x4, eta_y4;
  double betax, betay;
  int r1, r2, r3, r4, r5;

  r1 = r0 - dG[n];
  r2 = r0 - dG[n] + dE[n];
  r3 = r0 - dG[n] - dE[n];
  r4 = r0 + dE[n];
  r5 = r0 - dE[n];

  Jaco0 = 2.0 / (S[n][r1] + S[n][r0]);
  Jaco1 = 2.0 / (S[n][r1] + S[n][r2]);
  Jaco2 = 2.0 / (S[n][r1] + S[n][r3]);
  Jaco3 = 2.0 / (S[n][r0] + S[n][r4]);
  Jaco4 = 2.0 / (S[n][r0] + S[n][r5]);

  kx     = y_eta[n][r0];
  ky     = x_eta[n][r0];
  xi_x   = y_eta[n][r0] * Jaco0;
  xi_y   = x_eta[n][r0] * Jaco0;
  eta_x1 = y_xi[n][r2] * Jaco1;
  eta_y1 = x_xi[n][r2] * Jaco1;
  eta_x2 = y_xi[n][r1] * Jaco2;
  eta_y2 = x_xi[n][r1] * Jaco2;
  eta_x3 = y_xi[n][r4] * Jaco3;
  eta_y3 = x_xi[n][r4] * Jaco3;
  eta_x4 = y_xi[n][r0] * Jaco4;
  eta_y4 = x_xi[n][r0] * Jaco4;

  //粘性項Evを計算する
  //サザーランドの公式で粘性係数を計算
  T_1 = Cons_calcCpT(n, r1);
  T_2 = Cons_calcCpT(n, r0);
  T_3 = Cons_calcCpT(n, r2);
  T_4 = Cons_calcCpT(n, r3);
  T_5 = Cons_calcCpT(n, r4);
  T_6 = Cons_calcCpT(n, r5);

  tmpT = 0.5 * (Cons_calcP(n, r0) / (rho[n][r0] * Rair) + Cons_calcP(n, r1) / (rho[n][r1] * Rair)) / T_0;
  mu = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0);

  Mueff = mu + 0.5 * (Mut[n][r0] + Mut[n][r1]);
  Mut_xi = 0.5 * (Mut[n][r0] + Mut[n][r1]);

  u_x = xi_x * (ux[n][r0] - ux[n][r1]) + 0.25 * (eta_x1 * (ux[n][r2] - ux[n][r1])
					       + eta_x2 * (ux[n][r1] - ux[n][r3])
					       + eta_x3 * (ux[n][r4] - ux[n][r0])
					       + eta_x4 * (ux[n][r0] - ux[n][r5]));

  v_x = xi_x * (uy[n][r0] - uy[n][r1]) + 0.25 * (eta_x1 * (uy[n][r2] - uy[n][r1])
					       + eta_x2 * (uy[n][r1] - uy[n][r3])
					       + eta_x3 * (uy[n][r4] - uy[n][r0])
					       + eta_x4 * (uy[n][r0] - uy[n][r5]));


  u_y = xi_y * (ux[n][r0] - ux[n][r1]) + 0.25 * (eta_y1 * (ux[n][r2] - ux[n][r1])
					       + eta_y2 * (ux[n][r1] - ux[n][r3])
					       + eta_y3 * (ux[n][r4] - ux[n][r0])
					       + eta_y4 * (ux[n][r0] - ux[n][r5]));

  v_y = xi_y * (uy[n][r0] - uy[n][r1]) + 0.25 * (eta_y1 * (uy[n][r2] - uy[n][r1])
					       + eta_y2 * (uy[n][r1] - uy[n][r3])
					       + eta_y3 * (uy[n][r4] - uy[n][r0])
					       + eta_y4 * (uy[n][r0] - uy[n][r5]));


  Tx = xi_x * (T_2 - T_1) + 0.25 * (eta_x1 * (T_3 - T_1) + eta_x2 * (T_1 - T_4)	+ eta_x3 * (T_5 - T_2) + eta_x4 * (T_2 - T_6));
  Ty = xi_y * (T_2 - T_1) + 0.25 * (eta_y1 * (T_3 - T_1) + eta_y2 * (T_1 - T_4)	+ eta_y3 * (T_5 - T_2) + eta_y4 * (T_2 - T_6));

  Txx = 2.0 * Mueff * (2.0 * u_x - v_y) / 3.0;
  Txy = Mueff * (u_y + v_x);
  Tyy = 2.0 * Mueff * (2.0 * v_y - u_x) / 3.0;
  betax = Txx * (ux[n][r1] + ux[n][r0]) * 0.5 + Txy * (uy[n][r1] + uy[n][r0]) * 0.5 + (mu / Pr + Mut_xi / Prt) * Tx;
  betay = Txy * (ux[n][r1] + ux[n][r0]) * 0.5 + Tyy * (uy[n][r1] + uy[n][r0]) * 0.5 + (mu / Pr + Mut_xi / Prt) * Ty;

  Ev[n][0][r0] = 0.0;
  Ev[n][1][r0] = kx * Txx + ky * Txy;
  Ev[n][2][r0] = kx * Txy + ky * Tyy;
  Ev[n][3][r0] = kx * betax + ky * betay;

}

void Viscous_calc_eta(int n, int r0){
  double mu, Mueff, Mut_eta;
  double tmpT;
  double T_1;
  double T_2;
  double T_3;
  double T_4;
  double T_5;
  double T_6;
  double Txx;
  double Txy;
  double Tyy;
  double Tx;
  double Ty;
  double u_x;
  double u_y;
  double v_x;
  double v_y;
  double u_ave1;
  double u_ave2;
  double v_ave1;
  double v_ave2;
  double kx, ky, Jaco0, Jaco1, Jaco2, Jaco3, Jaco4;
  double xi_x1, xi_y1, xi_x2, xi_y2, xi_x3, xi_y3, xi_x4, xi_y4;
  double eta_x, eta_y;
  double betax, betay;
  int r1, r2, r3, r4, r5;

  r1 = r0 - dE[n];
  r2 = r0 - dE[n] - dG[n];
  r3 = r0 - dE[n] + dG[n];
  r4 = r0 - dG[n];
  r5 = r0 + dG[n];

  Jaco0 = 2.0 / (S[n][r1] + S[n][r0]);
  Jaco1 = 2.0 / (S[n][r1] + S[n][r2]);
  Jaco2 = 2.0 / (S[n][r1] + S[n][r3]);
  Jaco3 = 2.0 / (S[n][r0] + S[n][r4]);
  Jaco4 = 2.0 / (S[n][r0] + S[n][r5]);

  kx    = y_xi[n][r0];
  ky    = x_xi[n][r0];
  eta_x = y_xi[n][r0] * Jaco0;
  eta_y = x_xi[n][r0] * Jaco0;
  xi_x1 = y_eta[n][r1] * Jaco1;
  xi_y1 = x_eta[n][r1] * Jaco1;
  xi_x2 = y_eta[n][r3] * Jaco2;
  xi_y2 = x_eta[n][r3] * Jaco2;
  xi_x3 = y_eta[n][r0] * Jaco3;
  xi_y3 = x_eta[n][r0] * Jaco3;
  xi_x4 = y_eta[n][r5] * Jaco4;
  xi_y4 = x_eta[n][r5] * Jaco4; 

  //粘性項Fvを計算する
  //サザーランドの公式で粘性係数を計算
  T_1 = Cons_calcCpT(n, r1);
  T_2 = Cons_calcCpT(n, r0);
  T_3 = Cons_calcCpT(n, r2);
  T_4 = Cons_calcCpT(n, r4);
  T_5 = Cons_calcCpT(n, r3);
  T_6 = Cons_calcCpT(n, r5);

  tmpT = 0.5 * (Cons_calcP(n, r0) / (rho[n][r0] * Rair) + Cons_calcP(n, r1) / (rho[n][r1] * Rair)) / T_0;
  mu = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0);

  Mueff = mu + 0.5 * (Mut[n][r0] + Mut[n][r1]);
  Mut_eta = 0.5 * (Mut[n][r0] + Mut[n][r1]);

  u_x = eta_x * (ux[n][r0] - ux[n][r1]) + 0.25 * (xi_x1 * (ux[n][r1] - ux[n][r2])
						+ xi_x2 * (ux[n][r3] - ux[n][r1])
					        + xi_x3 * (ux[n][r0] - ux[n][r4])
						+ xi_x4 * (ux[n][r5] - ux[n][r0]));

  v_x = eta_x * (uy[n][r0] - uy[n][r1]) + 0.25 * (xi_x1 * (uy[n][r1] - uy[n][r2])
				       	        + xi_x2 * (uy[n][r3] - uy[n][r1])
					        + xi_x3 * (uy[n][r0] - uy[n][r4])
					        + xi_x4 * (uy[n][r5] - uy[n][r0]));


  u_y = eta_y * (ux[n][r0] - ux[n][r1]) + 0.25 * (xi_y1 * (ux[n][r1] - ux[n][r2])
					        + xi_y2 * (ux[n][r3] - ux[n][r1])
					        + xi_y3 * (ux[n][r0] - ux[n][r4])
					        + xi_y4 * (ux[n][r5] - ux[n][r0]));


  v_y = eta_y * (uy[n][r0] - uy[n][r1]) + 0.25 * (xi_y1 * (uy[n][r1] - uy[n][r2])
					        + xi_y2 * (uy[n][r3] - uy[n][r1])
					        + xi_y3 * (uy[n][r0] - uy[n][r4])
					        + xi_y4 * (uy[n][r5] - uy[n][r0]));


  Tx = eta_x * (T_2 - T_1) + 0.25 * (xi_x1 * (T_1 - T_3) + xi_x2 * (T_5 - T_1) + xi_x3 * (T_2 - T_4) + xi_x4 * (T_6 - T_2));
  Ty = eta_y * (T_2 - T_1) + 0.25 * (xi_y1 * (T_1 - T_3) + xi_y2 * (T_5 - T_1) + xi_y3 * (T_2 - T_4) + xi_y4 * (T_6 - T_2));


  Txx = 2.0 * Mueff * (2.0 * u_x - v_y) / 3.0;
  Txy = Mueff * (u_y + v_x);
  Tyy = 2.0 * Mueff * (2.0 * v_y - u_x) / 3.0;
  betax = Txx * (ux[n][r1] + ux[n][r0]) * 0.5 + Txy * (uy[n][r1] + uy[n][r0]) * 0.5 + (mu / Pr + Mut_eta / Prt) * Tx;
  betay = Txy * (ux[n][r1] + ux[n][r0]) * 0.5 + Tyy * (uy[n][r1] + uy[n][r0]) * 0.5 + (mu / Pr + Mut_eta / Prt) * Ty;

  Fv[n][0][r0] = 0.0;
  Fv[n][1][r0] = kx * Txx + ky * Txy;
  Fv[n][2][r0] = kx * Txy + ky * Tyy;
  Fv[n][3][r0] = kx * betax + ky * betay;
}

void viscous(){
  int n;

  for(n=0;n<NT;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
	int r0;
	r0 = dim[n](i, j);
	Viscous_calc_xi(n,  r0);
	Viscous_calc_eta(n, r0);
      }
    }
  }

}
