/****************************************************

fds for k-omega turbulance model

 ***************************************************/

void fds_komega(){
  int n;

  for(n=0;n<NT;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
	int r0;
	int pG, mG, mmG;
	double invS;
	int dgd, jj;
	double skx, sky, Jaco;
	double D1rho, D1ux, D1uy, D1k, D1omega;
	double D2rho, D2ux, D2uy, D2k, D2omega;
	double D3rho, D3ux, D3uy, D3k, D3omega;

	double D1rho_, D1ux_, D1uy_, D1k_, D1omega_;
	double D2rho_, D2ux_, D2uy_, D2k_, D2omega_;
	double D3rho_, D3ux_, D3uy_, D3k_, D3omega_;

	double rhoPG, uxPG, uyPG, kPG, omegaPG, VnPG;
	double rhoMG, uxMG, uyMG, kMG, omegaMG, VnMG;
	double rhoAVE,uxAVE,uyAVE,kAVE,omegaAVE;
	double UU;
  
	double EE[2];
	double RAL[2][2];
	double invrhoave;

	int XI, ETA;
	XI = 0;
	ETA = 1;

	/***== < MUSCL > ==***/
	double ipu = 1.0;   /* MUSCL 2nd,3rd-order */  
	double kk = 1.0/3.0;/* MUSCL 3rd */
	// double kk = -1.0;   /* MUSCL 2nd-order fully upwind
	/*  double kk = 0.0;   /* MUSCL 2nd-order upwind biased*/
	double ss = 1.0;

	r0 = dim[n](i, j);

	for(dgd=0;dgd<2;dgd++){
	  if(dgd == XI){
	    Jaco = 2.0 / (S[n][r0] + S[n][r0-dG[n]]);
	    pG = r0 + dG[n];
	    mG = r0 - dG[n];
	    mmG = r0 - 2 * dG[n];
	    skx = y_eta[n][r0];
	    sky = x_eta[n][r0];
	  }
	  else if(dgd == ETA){
	    Jaco = 2.0 / (S[n][r0] + S[n][r0-dE[n]]);
	    pG = r0 + dE[n];
	    mG = r0 - dE[n];
	    mmG = r0 - 2 * dE[n];
	    skx = y_xi[n][r0];
	    sky = x_xi[n][r0];
	  }

	  D1rho = rho[n][mG] - rho[n][mmG];
	  D2rho = rho[n][r0] - rho[n][mG];
	  D3rho = rho[n][pG] - rho[n][r0];
	  D1ux  = ux[n][mG]  - ux[n][mmG];
	  D2ux  = ux[n][r0]  - ux[n][mG];
	  D3ux  = ux[n][pG]  - ux[n][r0];
	  D1uy  = uy[n][mG]  - uy[n][mmG];
	  D2uy  = uy[n][r0]  - uy[n][mG];
	  D3uy  = uy[n][pG]  - uy[n][r0];
	  D1k       = k_turb[n][mG]  - k_turb[n][mmG];
	  D2k       = k_turb[n][r0]  - k_turb[n][mG];
	  D3k       = k_turb[n][pG]  - k_turb[n][r0];
	  D1omega   = omega[n][mG]   - omega[n][mmG];
	  D2omega   = omega[n][r0]   - omega[n][mG];
	  D3omega   = omega[n][pG]   - omega[n][r0];

	  D1rho_ = minmod_limiter(D1rho, D2rho, kk);
	  D2rho_ = minmod_limiter(D2rho, D1rho, kk);
	  rhoMG  = rho[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1rho_ + (1.0 + kk * ss) * D2rho_) * ipu;

	  D1ux_ = minmod_limiter(D1ux, D2ux, kk);
	  D2ux_ = minmod_limiter(D2ux, D1ux, kk);
	  uxMG  = ux[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1ux_ + (1.0 + kk * ss) * D2ux_) * ipu;

	  D1uy_ = minmod_limiter(D1uy, D2uy, kk);
	  D2uy_ = minmod_limiter(D2uy, D1uy, kk);
	  uyMG  = uy[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1uy_ + (1.0 + kk * ss) * D2uy_) * ipu;

	  D1k_ = minmod_limiter(D1k, D2k, kk);
	  D2k_ = minmod_limiter(D2k, D1k, kk);
	  kMG  = k_turb[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1k_ + (1.0 + kk * ss) * D2k_) * ipu;

	  D1omega_ = minmod_limiter(D1omega, D2omega, kk);
	  D2omega_ = minmod_limiter(D2omega, D1omega, kk);
	  omegaMG  = omega[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1omega_ + (1.0 + kk * ss) * D2omega_) * ipu;

	  D3rho_ = minmod_limiter(D3rho, D2rho, kk);
	  D2rho_ = minmod_limiter(D2rho, D3rho, kk);
	  rhoPG  = rho[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3rho_ + (1.0 + kk * ss) * D2rho_ ) * ipu;

	  D3ux_ = minmod_limiter(D3ux, D2ux, kk);
	  D2ux_ = minmod_limiter(D2ux, D3ux, kk);
	  uxPG  = ux[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3ux_ + (1.0 + kk * ss) * D2ux_ ) * ipu;

	  D3uy_ = minmod_limiter(D3uy, D2uy, kk);
	  D2uy_ = minmod_limiter(D2uy, D3uy, kk);
	  uyPG  = uy[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3uy_ + (1.0 + kk * ss) * D2uy_ ) * ipu;

	  D3k_ = minmod_limiter(D3k, D2k, kk);
	  D2k_ = minmod_limiter(D2k, D3k, kk);
	  kPG  = k_turb[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3k_ + (1.0 + kk * ss) * D2k_ ) * ipu;

	  D3omega_ = minmod_limiter(D3omega, D2omega, kk);
	  D2omega_ = minmod_limiter(D2omega, D3omega, kk);
	  omegaPG  = omega[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3omega_ + (1.0 + kk * ss) * D2omega_ ) * ipu;

	  invrhoave  = 1.0 / (sqrt(rhoPG) + sqrt(rhoMG));
	  rhoAVE     = sqrt(rhoPG * rhoMG);
	  uxAVE      = (sqrt(rhoPG) * uxPG  + sqrt(rhoMG) * uxMG)  * invrhoave;
	  uyAVE      = (sqrt(rhoPG) * uyPG  + sqrt(rhoMG) * uyMG)  * invrhoave;
	  kAVE       = (sqrt(rhoPG) * kPG   + sqrt(rhoMG) * kMG)   * invrhoave;
	  omegaAVE   = (sqrt(rhoPG) * omegaPG + sqrt(rhoMG) * omegaMG) * invrhoave;
	      

	  VnMG = (uxMG * skx + uyMG * sky);
	  VnPG = (uxPG * skx + uyPG * sky);

	  EE[0] = rhoPG * kPG * VnPG + rhoMG * kMG * VnMG;
	  EE[1] = rhoPG * omegaPG * VnPG + rhoMG * omegaMG * VnMG;

	  UU = (skx * uxAVE + sky * uyAVE) * Jaco;

	  RAL[0][0] = fabs(UU);
	  RAL[0][1] = 0.0;
	  RAL[1][0] = 0.0;
	  RAL[1][1] = fabs(UU);


	  if(dgd == XI){
	    for(jj=0;jj<=1;jj++){
	      TurbE[n][jj][r0] = 0.5 * (EE[jj] -     (RAL[jj][0] * (rhoPG * kPG - rhoMG * kMG)
						   + RAL[jj][1] * (rhoPG * omegaPG - rhoMG * omegaMG)) / Jaco);
	    }
	  }
	  else if(dgd == ETA){
	    for(jj=0;jj<=1;jj++){
	      TurbF[n][jj][r0] = 0.5 * (EE[jj] -     (RAL[jj][0] * (rhoPG * kPG - rhoMG * kMG)
						   + RAL[jj][1] * (rhoPG * omegaPG - rhoMG * omegaMG)) / Jaco);
	    }
	  }
	}//dgdループ終わり
      }
    }
  }




}
