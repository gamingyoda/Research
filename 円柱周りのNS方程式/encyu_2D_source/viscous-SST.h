/****************************************

viscous calc
for k-omega turburance model

*****************************************/

void Viscous_komega_xi(int n, int r0){
  const double siguma_k_1 = 0.85;
  const double siguma_k_2 = 1.0;
  const double siguma_omega_1 = 0.5;
  const double siguma_omega_2 = 0.856;
  double siguma_k;
  double siguma_omega;
  double kx, ky;
  double kturb_x, kturb_y;
  double omega_x, omega_y;
  double Mu, Mueff_k, Mueff_omega;
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

  siguma_k     = calc_mix(n, r0, siguma_k_1, siguma_k_2);
  siguma_omega = calc_mix(n, r0, siguma_omega_1, siguma_omega_2);

  Mueff_k     = Mu + 0.5 * (Mut[n][r0] + Mut[n][r1]) * siguma_k;
  Mueff_omega = Mu + 0.5 * (Mut[n][r0] + Mut[n][r1]) * siguma_omega;

  kturb_x = xi_x * (k_turb[n][r0] - k_turb[n][r1]) + 0.25 * (eta_x1 * (k_turb[n][r2] - k_turb[n][r1])
					                + eta_x2 * (k_turb[n][r1] - k_turb[n][r3])
					                + eta_x3 * (k_turb[n][r4] - k_turb[n][r0])
					                + eta_x4 * (k_turb[n][r0] - k_turb[n][r5]));

  omega_x = xi_x * (omega[n][r0] - omega[n][r1]) + 0.25 * (eta_x1 * (omega[n][r2] - omega[n][r1])
					              + eta_x2 * (omega[n][r1] - omega[n][r3])
					              + eta_x3 * (omega[n][r4] - omega[n][r0])
					              + eta_x4 * (omega[n][r0] - omega[n][r5]));


  kturb_y = xi_y * (k_turb[n][r0] - k_turb[n][r1]) + 0.25 * (eta_y1 * (k_turb[n][r2] - k_turb[n][r1])
					                + eta_y2 * (k_turb[n][r1] - k_turb[n][r3])
					                + eta_y3 * (k_turb[n][r4] - k_turb[n][r0])
					                + eta_y4 * (k_turb[n][r0] - k_turb[n][r5]));

  omega_y = xi_y * (omega[n][r0] - omega[n][r1]) + 0.25 * (eta_y1 * (omega[n][r2] - omega[n][r1])
					              + eta_y2 * (omega[n][r1] - omega[n][r3])
					              + eta_y3 * (omega[n][r4] - omega[n][r0])
					              + eta_y4 * (omega[n][r0] - omega[n][r5]));

  TurbEv[n][0][r0] = kx * Mueff_k   * kturb_x     + ky * Mueff_k * kturb_y;
  TurbEv[n][1][r0] = kx * Mueff_omega * omega_x   + ky * Mueff_omega * omega_y;
}

void Viscous_komega_eta(int n, int r0){
  const double siguma_k_1 = 0.85;
  const double siguma_k_2 = 1.0;
  const double siguma_omega_1 = 0.5;
  const double siguma_omega_2 = 0.856;
  double siguma_k;
  double siguma_omega;
  double kx, ky;
  double kturb_x, kturb_y;
  double omega_x, omega_y;
  double Mu, Mueff_k, Mueff_omega;
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

  siguma_k = calc_mix(n, r0, siguma_k_1, siguma_k_2);
  siguma_omega = calc_mix(n, r0, siguma_omega_1, siguma_omega_2);

  Mueff_k     = Mu + 0.5 * (Mut[n][r0] + Mut[n][r1]) * siguma_k;
  Mueff_omega = Mu + 0.5 * (Mut[n][r0] + Mut[n][r1]) * siguma_omega;

  kturb_x = eta_x * (k_turb[n][r0] - k_turb[n][r1]) + 0.25 * (xi_x1 * (k_turb[n][r1] - k_turb[n][r2])
					                 + xi_x2 * (k_turb[n][r3] - k_turb[n][r1])
					                 + xi_x3 * (k_turb[n][r0] - k_turb[n][r4])
					                 + xi_x4 * (k_turb[n][r5] - k_turb[n][r0]));

  omega_x = eta_x * (omega[n][r0] - omega[n][r1]) + 0.25 * (xi_x1 * (omega[n][r1] - omega[n][r2])
					               + xi_x2 * (omega[n][r3] - omega[n][r1])
					               + xi_x3 * (omega[n][r0] - omega[n][r4])
					               + xi_x4 * (omega[n][r5] - omega[n][r0]));


  kturb_y = eta_y * (k_turb[n][r0] - k_turb[n][r1]) + 0.25 * (xi_y1 * (k_turb[n][r1] - k_turb[n][r2])
					                 + xi_y2 * (k_turb[n][r3] - k_turb[n][r1])
					                 + xi_y3 * (k_turb[n][r0] - k_turb[n][r4])
					                 + xi_y4 * (k_turb[n][r5] - k_turb[n][r0]));


  omega_y = eta_y * (omega[n][r0] - omega[n][r1]) + 0.25 * (xi_y1 * (omega[n][r1] - omega[n][r2])
					               + xi_y2 * (omega[n][r3] - omega[n][r1])
					               + xi_y3 * (omega[n][r0] - omega[n][r4])
					               + xi_y4 * (omega[n][r5] - omega[n][r0]));

  TurbFv[n][0][r0] = kx * Mueff_k   * kturb_x     + ky * Mueff_k   * kturb_y;
  TurbFv[n][1][r0] = kx * Mueff_omega * omega_x   + ky * Mueff_omega * omega_y;
}

void viscous_komega(){
  int n;

  for(n=0;n<NT;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
	int r0;
	r0 = dim[n](i, j);
	Viscous_komega_xi(n, r0);
	Viscous_komega_eta(n, r0);
      }
    }
  }

}
