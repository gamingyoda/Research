/****************************************

viscous calc
for SA turburance model

*****************************************/

void Viscous_SA_xi(int n, int r0){
  double kx, ky;
  double NuSA_x, NuSA_y;
  double Mu, Nueff;
  double siguma_reverse = 1.5;
  double Jaco0, Jaco1, Jaco2, Jaco3, Jaco4;
  double xi_x, xi_y;
  double eta_x1, eta_y1, eta_x2, eta_y2, eta_x3, eta_y3, eta_x4, eta_y4;
  double tmpT;
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

  tmpT = 0.5 * (Cons_calcP(n, r0) / (rho[n][r0] * Rair) + Cons_calcP(n, r1) / (rho[n][r1] * Rair)) / T_0;
  Mu = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0);


  Nueff = Mu / rho[n][r0] + 0.5 * (NuSA[n][r0] + NuSA[n][r1]);

  NuSA_x = xi_x * (NuSA[n][r0] - NuSA[n][r1]) + 0.25 * (eta_x1 * (NuSA[n][r2] - NuSA[n][r1])
						      + eta_x2 * (NuSA[n][r1] - NuSA[n][r3])
					              + eta_x3 * (NuSA[n][r4] - NuSA[n][r0])
					              + eta_x4 * (NuSA[n][r0] - NuSA[n][r5]));


  NuSA_y = xi_y * (NuSA[n][r0] - NuSA[n][r1]) + 0.25 * (eta_y1 * (NuSA[n][r2] - NuSA[n][r1])
					              + eta_y2 * (NuSA[n][r1] - NuSA[n][r3])
					              + eta_y3 * (NuSA[n][r4] - NuSA[n][r0])
					              + eta_y4 * (NuSA[n][r0] - NuSA[n][r5]));


  TurbEv[n][0][r0] = siguma_reverse * (kx * Nueff * NuSA_x     + ky * Nueff * NuSA_y);
}

void Viscous_SA_eta(int n, int r0){
  double kx, ky;
  double NuSA_x, NuSA_y;
  double Mu, Nueff;
  double siguma_reverse = 1.5;
  double Jaco0, Jaco1, Jaco2, Jaco3, Jaco4;
  double xi_x1, xi_y1, xi_x2, xi_y2, xi_x3, xi_y3, xi_x4, xi_y4;
  double eta_x, eta_y;
  double tmpT;
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

  tmpT = 0.5 * (Cons_calcP(n, r0) / (rho[n][r0] * Rair) + Cons_calcP(n, r1) / (rho[n][r1] * Rair)) / T_0;
  Mu = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0);

  Nueff     = Mu / rho[n][r0] + 0.5 * (NuSA[n][r0] + NuSA[n][r1]);


  NuSA_x = eta_x * (NuSA[n][r0] - NuSA[n][r1]) + 0.25 * (xi_x1 * (NuSA[n][r1] - NuSA[n][r2])
				                       + xi_x2 * (NuSA[n][r3] - NuSA[n][r1])
					               + xi_x3 * (NuSA[n][r0] - NuSA[n][r4])
					               + xi_x4 * (NuSA[n][r5] - NuSA[n][r0]));


  NuSA_y = eta_y * (NuSA[n][r0] - NuSA[n][r1]) + 0.25 * (xi_y1 * (NuSA[n][r1] - NuSA[n][r2])
					               + xi_y2 * (NuSA[n][r3] - NuSA[n][r1])
					               + xi_y3 * (NuSA[n][r0] - NuSA[n][r4])
					               + xi_y4 * (NuSA[n][r5] - NuSA[n][r0]));


  TurbFv[n][0][r0] = siguma_reverse * (kx * Nueff   * NuSA_x     + ky * Nueff   * NuSA_y);
}

void viscous_SA(){
  int n;

  for(n=0;n<NT;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
	int r0;
	r0 = dim[n](i, j);
	Viscous_SA_xi(n, r0);
	Viscous_SA_eta(n, r0);
      }
    }
  }

}
