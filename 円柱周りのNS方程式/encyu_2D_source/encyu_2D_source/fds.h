/*----------------------------------------

Flux Diferrence Split 
Roe MUSCL 2-dimentional

-----------------------------------------*/

void RIAIL(int n, int r0, double rho_s, double ux_s, double uy_s, double HH, double CC, int dz, double (*ral)[4]){
  double Right[4][4];
  double Left[4][4];
  double lambda_abs[4];

  double Jaco, kx, ky, Sk, kx_, ky_;
  double Z, Z_, QQ;
  double b1, b2;
  int ii, jj, kk;
  int dX, dY;
  int XI, ETA;

  XI  = 0;
  ETA = 1;

  if(dz == XI){
    Jaco = 2.0 / (S[n][r0] + S[n][r0-dG[n]]);
    kx = y_eta[n][r0] * Jaco;    ky = x_eta[n][r0] * Jaco;
  }
  else if(dz == ETA){
    Jaco = 2.0 / (S[n][r0] + S[n][r0-dE[n]]);
    kx = y_xi[n][r0] * Jaco;     ky = x_xi[n][r0] * Jaco;
  }

  Sk = 1.0 / (sqrt(kx * kx + ky * ky));
  kx_ = kx * Sk;
  ky_ = ky * Sk;
  Z   = kx * ux_s + ky * uy_s;
  Z_  = Z * Sk;
  QQ  = ux_s * ux_s + uy_s * uy_s;

  lambda_abs[0] = fabs(Z - CC / Sk);
  lambda_abs[1] = fabs(Z          );
  lambda_abs[2] = fabs(Z + CC / Sk);
  lambda_abs[3] = fabs(Z          );

  Right[0][0] = 1.0;
  Right[0][1] = 1.0;
  Right[0][2] = 1.0;
  Right[0][3] = 0.0;
  Right[1][0] = ux_s - kx_ * CC;
  Right[1][1] = ux_s;
  Right[1][2] = ux_s + kx_ * CC;
  Right[1][3] = -ky_;
  Right[2][0] = uy_s - ky_ * CC;
  Right[2][1] = uy_s;
  Right[2][2] = uy_s + ky_ * CC;
  Right[2][3] = kx_;
  Right[3][0] = HH - CC * Z_;
  Right[3][1] = 0.5 * QQ;
  Right[3][2] = HH + CC * Z_;
  Right[3][3] = -(ky_ * ux_s - kx_ * uy_s);

  b1 = 0.5 * QQ * (gamma0 - 1.0) / (CC * CC);
  b2 = (gamma0 - 1.0) / (CC * CC);

  Left[0][0] = 0.5 * (b1 + Z_ / CC);
  Left[0][1] = -0.5 * (kx_ / CC + b2 * ux_s);
  Left[0][2] = -0.5 * (ky_ / CC + b2 * uy_s);
  Left[0][3] = 0.5 * b2;
  Left[1][0] = 1.0 - b1;
  Left[1][1] = b2 * ux_s;
  Left[1][2] = b2 * uy_s;
  Left[1][3] = -b2;
  Left[2][0] = 0.5 * (b1 - Z_ / CC);
  Left[2][1] = 0.5 * (kx_ / CC - b2 * ux_s);
  Left[2][2] = 0.5 * (ky_ / CC - b2 * uy_s);
  Left[2][3] = 0.5 * b2;
  Left[3][0] = ky_ * ux_s - kx_ * uy_s;
  Left[3][1] = -ky_;
  Left[3][2] = kx_;
  Left[3][3] = 0.0;

  for(ii=0;ii<4;ii++){
    for(jj=0;jj<4;jj++){
      ral[ii][jj] = 0.0;
      for(kk=0;kk<4;kk++){
	ral[ii][jj] += Right[ii][kk] * lambda_abs[kk] * Left[kk][jj];
      }
    }
  }

}

double minmod_limiter(double delt1,double delt2,double kk)
{
  double bb,result;

  bb = (3.0 - kk)/(1.0 - kk);
  if(delt1*delt2*bb<=0.0)
    {
      result = 0.0;
    }
  else if(fabs(delt1)/fabs(delt2*bb)<=1.0)
    {
      result = delt1;
    }
  else
    {
      result = delt2*bb;
    }
  return result;
}

void fds(){
  int n;

  for(n=0;n<NT;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
	int r0;
	int pG, mG, mmG, ppG, mmmG;
	int dgd, jj;
	double invS;
	double p_r0, p_pG, p_ppG, p_mG, p_mmG, p_mmmG;
	double skx, sky, Jaco;

	double DD1rho, DD1ux, DD1uy, DD1p, DD1e, DD1k, DD1omega;
	double DD2rho, DD2ux, DD2uy, DD2p, DD2e, DD2k, DD2omega;
	double DD3rho, DD3ux, DD3uy, DD3p, DD3e, DD3k, DD3omega;
	double DD4rho, DD4ux, DD4uy, DD4p, DD4e, DD4k, DD4omega;
	double DD5rho, DD5ux, DD5uy, DD5p, DD5e, DD5k, DD5omega;

	double D1rho, D1ux, D1uy, D1p, D1e;
	double D2rho, D2ux, D2uy, D2p, D2e;
	double D3rho, D3ux, D3uy, D3p, D3e;

	double D1rho_, D1ux_, D1uy_, D1p_, D1e_;
	double D2rho_, D2ux_, D2uy_, D2p_, D2e_;
	double D3rho_, D3ux_, D3uy_, D3p_, D3e_;

	double rhoPG, uxPG, uyPG, pPG, cPG, ePG, VnPG;
	double rhoMG, uxMG, uyMG, pMG, cMG, eMG, VnMG;
	double rhoAVE,uxAVE,uyAVE,CCAVE,HHAVE;
  
	double RAL[4][4];
	double EE[4];
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
	    ppG  = r0 + 2 * dG[n];
	    mG = r0 - dG[n];
	    mmG = r0 - 2 * dG[n];
	    mmmG = r0 - 3 * dG[n];
	    skx = y_eta[n][r0];
	    sky = x_eta[n][r0];
	  }
	  else if(dgd == ETA){
	    Jaco = 2.0 / (S[n][r0] + S[n][r0-dE[n]]);
	    pG = r0 + dE[n];
	    ppG = r0 + 2 * dE[n];
	    mG = r0 - dE[n];
	    mmG = r0 - 2 * dE[n];
	    mmmG = r0 - 3 * dE[n];
	    skx = y_xi[n][r0];
	    sky = x_xi[n][r0];
	  }

	  if((i==2 && dgd==XI) || (j==2 && dgd==ETA) || (i==it[n]-3 && dgd==XI) || (j==jt[n]-3 && dgd==ETA)){
	    p_r0  = Cons_calcP(n, r0);
	    p_pG  = Cons_calcP(n, pG);
	    p_mG  = Cons_calcP(n, mG);
	    p_mmG = Cons_calcP(n, mmG);

	    D1rho = rho[n][mG] - rho[n][mmG];
	    D2rho = rho[n][r0] - rho[n][mG];
	    D3rho = rho[n][pG] - rho[n][r0];
	    D1ux  = ux[n][mG]  - ux[n][mmG];
	    D2ux  = ux[n][r0]  - ux[n][mG];
	    D3ux  = ux[n][pG]  - ux[n][r0];
	    D1uy  = uy[n][mG]  - uy[n][mmG];
	    D2uy  = uy[n][r0]  - uy[n][mG];
	    D3uy  = uy[n][pG]  - uy[n][r0];
	    D1e   = e[n][mG]   - e[n][mmG];
	    D2e   = e[n][r0]   - e[n][mG];
	    D3e   = e[n][pG]   - e[n][r0];
	    D1p   = p_mG      - p_mmG;
	    D2p   = p_r0      - p_mG;
	    D3p   = p_pG      - p_r0;
	  }
	  else{
	    p_r0  = Cons_calcP(n, r0);
	    p_pG  = Cons_calcP(n, pG);
	    p_ppG  = Cons_calcP(n, ppG);
	    p_mG  = Cons_calcP(n, mG);
	    p_mmG = Cons_calcP(n, mmG);
	    p_mmmG = Cons_calcP(n, mmmG);

	    DD1rho = rho[n][mmG] - rho[n][mmmG];
	    DD2rho = rho[n][mG]  - rho[n][mmG];
	    DD3rho = rho[n][r0]  - rho[n][mG];
	    DD4rho = rho[n][pG]  - rho[n][r0];
	    DD5rho = rho[n][ppG] - rho[n][pG];
	    DD1ux  = ux[n][mmG]  - ux[n][mmmG];
	    DD2ux  = ux[n][mG]   - ux[n][mmG];
	    DD3ux  = ux[n][r0]   - ux[n][mG];
	    DD4ux  = ux[n][pG]   - ux[n][r0];
	    DD5ux  = ux[n][ppG]  - ux[n][pG];
	    DD1uy  = uy[n][mmG]  - uy[n][mmmG];
	    DD2uy  = uy[n][mG]   - uy[n][mmG];
	    DD3uy  = uy[n][r0]   - uy[n][mG];
	    DD4uy  = uy[n][pG]   - uy[n][r0];
	    DD5uy  = uy[n][ppG]  - uy[n][pG];
	    DD1e   = e[n][mmG]   - e[n][mmmG];
	    DD2e   = e[n][mG]    - e[n][mmG];
	    DD3e   = e[n][r0]    - e[n][mG];
	    DD4e   = e[n][pG]    - e[n][r0];
	    DD5e   = e[n][ppG]   - e[n][pG];
	    DD1p   = p_mmG    - p_mmmG;
	    DD2p   = p_mG     - p_mmG;
	    DD3p   = p_r0     - p_mG;
	    DD4p   = p_pG     - p_r0;
	    DD5p   = p_ppG    - p_pG;

	    D1rho = DD2rho - (minmod_limiter(DD3rho - DD2rho, DD2rho - DD1rho, kk) - minmod_limiter(DD2rho - DD1rho, DD3rho - DD2rho, kk)) / 6.0;
	    D2rho = DD3rho - (minmod_limiter(DD4rho - DD3rho, DD3rho - DD2rho, kk) - minmod_limiter(DD3rho - DD2rho, DD4rho - DD3rho, kk)) / 6.0;
	    D3rho = DD4rho - (minmod_limiter(DD5rho - DD4rho, DD4rho - DD3rho, kk) - minmod_limiter(DD4rho - DD3rho, DD5rho - DD4rho, kk)) / 6.0;
	    D1ux  = DD2ux  - (minmod_limiter(DD3ux  - DD2ux,  DD2ux  - DD1ux,  kk) - minmod_limiter(DD2ux  - DD1ux,  DD3ux  - DD2ux,  kk)) / 6.0;
	    D2ux  = DD3ux  - (minmod_limiter(DD4ux  - DD3ux,  DD3ux  - DD2ux,  kk) - minmod_limiter(DD3ux  - DD2ux,  DD4ux  - DD3ux,  kk)) / 6.0;
	    D3ux  = DD4ux  - (minmod_limiter(DD5ux  - DD4ux,  DD4ux  - DD3ux,  kk) - minmod_limiter(DD4ux  - DD3ux,  DD5ux  - DD4ux,  kk)) / 6.0;
	    D1uy  = DD2uy  - (minmod_limiter(DD3uy  - DD2uy,  DD2uy  - DD1uy,  kk) - minmod_limiter(DD2uy  - DD1uy,  DD3uy  - DD2uy,  kk)) / 6.0;
	    D2uy  = DD3uy  - (minmod_limiter(DD4uy  - DD3uy,  DD3uy  - DD2uy,  kk) - minmod_limiter(DD3uy  - DD2uy,  DD4uy  - DD3uy,  kk)) / 6.0;
	    D3uy  = DD4uy  - (minmod_limiter(DD5uy  - DD4uy,  DD4uy  - DD3uy,  kk) - minmod_limiter(DD4uy  - DD3uy,  DD5uy  - DD4uy,  kk)) / 6.0;
	    D1p   = DD2p   - (minmod_limiter(DD3p   - DD2p,   DD2p   - DD1p,   kk) - minmod_limiter(DD2p   - DD1p,   DD3p   - DD2p,   kk)) / 6.0;
	    D2p   = DD3p   - (minmod_limiter(DD4p   - DD3p,   DD3p   - DD2p,   kk) - minmod_limiter(DD3p   - DD2p,   DD4p   - DD3p,   kk)) / 6.0;
	    D3p   = DD4p   - (minmod_limiter(DD5p   - DD4p,   DD4p   - DD3p,   kk) - minmod_limiter(DD4p   - DD3p,   DD5p   - DD4p,   kk)) / 6.0;
	    D1e   = DD2e   - (minmod_limiter(DD3e   - DD2e,   DD2e   - DD1e,   kk) - minmod_limiter(DD2e   - DD1e,   DD3e   - DD2e,   kk)) / 6.0;
	    D2e   = DD3e   - (minmod_limiter(DD4e   - DD3e,   DD3e   - DD2e,   kk) - minmod_limiter(DD3e   - DD2e,   DD4e   - DD3e,   kk)) / 6.0;
	    D3e   = DD4e   - (minmod_limiter(DD5e   - DD4e,   DD4e   - DD3e,   kk) - minmod_limiter(DD4e   - DD3e,   DD5e   - DD4e,   kk)) / 6.0;
	  }

	  /* p_r0  = Cons_calcP(n, r0); */
	  /* p_pG  = Cons_calcP(n, pG); */
	  /* p_mG  = Cons_calcP(n, mG); */
	  /* p_mmG = Cons_calcP(n, mmG); */


	  /* D1rho = rho[n][mG] - rho[n][mmG]; */
	  /* D2rho = rho[n][r0] - rho[n][mG]; */
	  /* D3rho = rho[n][pG] - rho[n][r0]; */
	  /* D1ux  = ux[n][mG]  - ux[n][mmG]; */
	  /* D2ux  = ux[n][r0]  - ux[n][mG]; */
	  /* D3ux  = ux[n][pG]  - ux[n][r0]; */
	  /* D1uy  = uy[n][mG]  - uy[n][mmG]; */
	  /* D2uy  = uy[n][r0]  - uy[n][mG]; */
	  /* D3uy  = uy[n][pG]  - uy[n][r0]; */
	  /* D1e   = e[n][mG]   - e[n][mmG]; */
	  /* D2e   = e[n][r0]   - e[n][mG]; */
	  /* D3e   = e[n][pG]   - e[n][r0]; */
	  /* D1p   = p_mG      - p_mmG; */
	  /* D2p   = p_r0      - p_mG; */
	  /* D3p   = p_pG      - p_r0; */

	  D1rho_ = minmod_limiter(D1rho, D2rho, kk);
	  D2rho_ = minmod_limiter(D2rho, D1rho, kk);
	  rhoMG  = rho[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1rho_ + (1.0 + kk * ss) * D2rho_) * ipu;

	  D1ux_ = minmod_limiter(D1ux, D2ux, kk);
	  D2ux_ = minmod_limiter(D2ux, D1ux, kk);
	  uxMG  = ux[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1ux_ + (1.0 + kk * ss) * D2ux_) * ipu;

	  D1uy_ = minmod_limiter(D1uy, D2uy, kk);
	  D2uy_ = minmod_limiter(D2uy, D1uy, kk);
	  uyMG  = uy[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1uy_ + (1.0 + kk * ss) * D2uy_) * ipu;

	  D1e_ = minmod_limiter(D1e, D2e, kk);
	  D2e_ = minmod_limiter(D2e, D1e, kk);
	  eMG  = e[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1e_ + (1.0 + kk * ss) * D2e_) * ipu;

	  D1p_ = minmod_limiter(D1p, D2p, kk);
	  D2p_ = minmod_limiter(D2p, D1p, kk);
	  pMG  = p[n][mG] + 0.25 * ss * ((1.0 - kk * ss) * D1p_ + (1.0 + kk * ss) * D2p_) * ipu;

	  D3rho_ = minmod_limiter(D3rho, D2rho, kk);
	  D2rho_ = minmod_limiter(D2rho, D3rho, kk);
	  rhoPG  = rho[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3rho_ + (1.0 + kk * ss) * D2rho_ ) * ipu;

	  D3ux_ = minmod_limiter(D3ux, D2ux, kk);
	  D2ux_ = minmod_limiter(D2ux, D3ux, kk);
	  uxPG  = ux[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3ux_ + (1.0 + kk * ss) * D2ux_ ) * ipu;

	  D3uy_ = minmod_limiter(D3uy, D2uy, kk);
	  D2uy_ = minmod_limiter(D2uy, D3uy, kk);
	  uyPG  = uy[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3uy_ + (1.0 + kk * ss) * D2uy_ ) * ipu;

	  D3e_ = minmod_limiter(D3e, D2e, kk);
	  D2e_ = minmod_limiter(D2e, D3e, kk);
	  ePG  = e[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3e_ + (1.0 + kk * ss) * D2e_ ) * ipu;

	  D3p_ = minmod_limiter(D3p, D2p, kk);
	  D2p_ = minmod_limiter(D2p, D3p, kk);
	  pPG  = p[n][r0] - 0.25 * ss * ((1.0 - kk * ss) * D3p_ + (1.0 + kk * ss) * D2p_ ) * ipu;

	  invrhoave = 1.0 / (sqrt(rhoPG) + sqrt(rhoMG));
	  rhoAVE    = sqrt(rhoPG * rhoMG);
	  uxAVE     = (sqrt(rhoPG) * uxPG + sqrt(rhoMG) * uxMG) * invrhoave;
	  uyAVE     = (sqrt(rhoPG) * uyPG + sqrt(rhoMG) * uyMG) * invrhoave;
	  HHAVE     = (sqrt(rhoPG) * (ePG + pPG) / rhoPG + sqrt(rhoMG) * (eMG + pMG) / rhoMG) * invrhoave;
	  CCAVE     = sqrt((gamma0 - 1.0) * (HHAVE - 0.5 * (uxAVE * uxAVE + uyAVE * uyAVE)));
	      
	  RIAIL(n, r0, rhoAVE, uxAVE, uyAVE, HHAVE, CCAVE, dgd, RAL);

	  VnMG = (uxMG * skx + uyMG * sky);
	  VnPG = (uxPG * skx + uyPG * sky);

	  EE[0] = rhoPG * VnPG + rhoMG * VnMG; 
	  EE[1] = rhoPG * uxPG * VnPG + skx * pPG + rhoMG * uxMG * VnMG + skx * pMG;  
	  EE[2] = rhoPG * uyPG * VnPG + sky * pPG + rhoMG * uyMG * VnMG + sky * pMG;
	  EE[3] = VnPG * (ePG + pPG) + VnMG * (eMG + pMG); 

	  if(dgd == XI){
	    for(jj=0;jj<=3;jj++){
	      E[n][jj][r0] = 0.5 * (EE[jj] -     (RAL[jj][0] * (rhoPG - rhoMG)
					       + RAL[jj][1] * (uxPG * rhoPG - uxMG * rhoMG)
					       + RAL[jj][2] * (uyPG * rhoPG - uyMG * rhoMG)
					       + RAL[jj][3] * (ePG - eMG)) / Jaco);
	    }
	  }
	  else if(dgd == ETA){
	    for(jj=0;jj<=3;jj++){
	      F[n][jj][r0] = 0.5 * (EE[jj] -       (RAL[jj][0] * (rhoPG - rhoMG)
						 + RAL[jj][1] * (uxPG * rhoPG - uxMG * rhoMG)
						 + RAL[jj][2] * (uyPG * rhoPG - uyMG * rhoMG)
						 + RAL[jj][3] * (ePG - eMG)) / Jaco);
	    }
	  }
	}//dgdループ終わり
      }
    }
  }
}
