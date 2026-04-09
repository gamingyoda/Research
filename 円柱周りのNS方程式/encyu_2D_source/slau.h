/*******************************************/
/*         SLAU & MUSCL                    */
/*                     written by fujisawa */
/*******************************************/

#define _E_ 0
#define _F_ 1

typedef struct{
  double rhoPK, rhoMK;
  double uxPK, uxMK;
  double uyPK, uyMK;
  double pPK, pMK;
  double ePK, eMK;
  double cPK, cMK;
}MUSCL_struct;


/************************************************
  流束制限関数 slope limiter !!!!!! 
  ***********************************************/
static inline double limiter (double deltP , double deltM , double ep){
  return(  ( 2.0 * deltP * deltM + ep ) / (deltM * deltM + deltP * deltP + ep ) ) ;
}

/*----------------------------------------------------------*/
/*                    小さい値を返す                        */
/*----------------------------------------------------------*/
static double min2f(double xe,double ye){
  return (xe < ye ? xe : ye);
}

/*----------------------------------------------------------*/
/*                    大きい値を返す                        */
/*----------------------------------------------------------*/
static double max2f(double xe,double ye){
  return (xe > ye ? xe : ye);
}


static void MUSCL_calc(int r0, int dK, int n, MUSCL_struct *st){
  int pK, mK, mmK;
  double p_r0, p_pK, p_mK, p_mmK;
  double D1rho, D1ux, D1uy, D1e, D1p;
  double D2rho, D2ux, D2uy, D2e, D2p;
  double D3rho, D3ux, D3uy, D3e, D3p;
  double D1rho_, D1ux_, D1uy_, D1p_, D1e_;
  double D2rho_, D2ux_, D2uy_, D2p_, D2e_;
  double D3rho_, D3ux_, D3uy_, D3p_, D3e_;
  double Jaco;

  /***== < MUSCL > ==***/
  double ipu = 1.0;   /* MUSCL 2nd,3rd-order */
  double kk = 1.0/3.0;/* MUSCL 3rd */
  /* double kk = -1.0;   /\* MUSCL 2nd-order fully upwind */
    
  /***== <  TVD slope limiter > ==***/
  double ep = 1.0e-6;/* ep が大きいほど高次精度に近い  G3_SHUS/shusTVD2.c = 100000000.0*/
  double ss = 1.0;/* noTVD 以下の ssをすべて消さないと有効でない*/

  pK = r0 + dK;
  mK = r0 - dK;
  mmK= mK - dK;

  D1rho = rho[n][mK] - rho[n][mmK];
  D2rho = rho[n][r0] - rho[n][mK];
  D3rho = rho[n][pK] - rho[n][r0];
  D1ux  = ux[n][mK]  - ux[n][mmK];
  D2ux  = ux[n][r0]  - ux[n][mK];
  D3ux  = ux[n][pK]  - ux[n][r0];
  D1uy  = uy[n][mK]  - uy[n][mmK];
  D2uy  = uy[n][r0]  - uy[n][mK];
  D3uy  = uy[n][pK]  - uy[n][r0];
  D1e   = e[n][mK]   - e[n][mmK];
  D2e   = e[n][r0]   - e[n][mK];
  D3e   = e[n][pK]   - e[n][r0];
    
  /* φL(i-1/2) xi方向 */
  D1rho_ = minmod_limiter(D1rho, D2rho, kk);
  D2rho_ = minmod_limiter(D2rho, D1rho, kk);
  st->rhoPK = (rho[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1rho_ + (1.0+kk*ss)*D2rho_ )*ipu);

  D1ux_ = minmod_limiter(D1ux, D2ux, kk);
  D2ux_ = minmod_limiter(D2ux, D1ux, kk);
  st->uxPK  = (ux[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1ux_  + (1.0+kk*ss)*D2ux_  )*ipu);

  D1uy_ = minmod_limiter(D1uy, D2uy, kk);
  D2uy_ = minmod_limiter(D2uy, D1uy, kk);
  st->uyPK  = (uy[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1uy_  + (1.0+kk*ss)*D2uy_  )*ipu);

  D1e_ = minmod_limiter(D1e, D2e, kk);
  D2e_ = minmod_limiter(D2e, D1e, kk);
  st->ePK   = (e[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1e_   + (1.0+kk*ss)*D2e_   )*ipu);

  st->pPK = (gamma0 - 1.0) * ( st->ePK - 0.5 * st->rhoPK * (st->uxPK*st->uxPK + st->uyPK*st->uyPK));
  st->cPK   = sqrt( gamma0*st->pPK/st->rhoPK );/** 音速 **/

  /* φR(i-1/2) xi方向 */
  D3rho_ = minmod_limiter(D3rho, D2rho, kk);
  D2rho_ = minmod_limiter(D2rho, D3rho, kk);
  st->rhoMK = (rho[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3rho_ + (1.0+kk*ss)*D2rho_ )*ipu);
 
  D3ux_ = minmod_limiter(D3ux, D2ux, kk);
  D2ux_ = minmod_limiter(D2ux, D3ux, kk);
  st->uxMK  = (ux[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3ux_  + (1.0+kk*ss)*D2ux_  )*ipu);
  
  D3uy_ = minmod_limiter(D3uy, D2uy, kk);
  D2uy_ = minmod_limiter(D2uy, D3uy, kk);
  st->uyMK  = (uy[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3uy_  + (1.0+kk*ss)*D2uy_  )*ipu);

  D3e_ = minmod_limiter(D3e, D2e, kk);
  D2e_ = minmod_limiter(D2e, D3e, kk);
  st->eMK   = (e[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3e_   + (1.0+kk*ss)*D2e_   )*ipu);

  st->pMK = (gamma0 - 1.0) * ( st->eMK - 0.5 * st->rhoMK * (st->uxMK*st->uxMK + st->uyMK*st->uyMK));
  st->cMK   = sqrt( gamma0*st->pMK/st->rhoMK );/** 音速 **/

  /* /\* φL(i-1/2) xi方向 *\/ */
  /* ss = limiter( D1rho, D2rho, ep );/\**\/ */
  /* st->rhoPK = (rho[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1rho + (1.0+kk*ss)*D2rho )*ipu); */

  /* ss = limiter( D1ux,  D2ux,  ep );/\**\/ */
  /* st->uxPK  = (ux[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1ux  + (1.0+kk*ss)*D2ux  )*ipu); */

  /* ss = limiter( D1uy,  D2uy,  ep );/\**\/ */
  /* st->uyPK  = (uy[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1uy  + (1.0+kk*ss)*D2uy  )*ipu); */

  /* ss = limiter( D1e,  D2e,  ep );/\**\/ */
  /* st->ePK   = (e[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1e   + (1.0+kk*ss)*D2e   )*ipu); */

  /* st->pPK = (gamma0 - 1.0) * ( st->ePK - 0.5 * st->rhoPK * (st->uxPK*st->uxPK + st->uyPK*st->uyPK)); */
  /* st->cPK   = sqrt( gamma0*st->pPK/st->rhoPK );/\** 音速 **\/ */

  /* /\* φR(i-1/2) xi方向 *\/ */
  /* ss = limiter( D3rho, D2rho, ep );/\**\/ */
  /* st->rhoMK = (rho[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3rho + (1.0+kk*ss)*D2rho )*ipu); */
 
  /* ss = limiter( D3ux,  D2ux,  ep );/\**\/ */
  /* st->uxMK  = (ux[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3ux  + (1.0+kk*ss)*D2ux  )*ipu); */
  
  /* ss = limiter( D3uy,  D2uy,  ep );/\**\/ */
  /* st->uyMK  = (uy[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3uy  + (1.0+kk*ss)*D2uy  )*ipu); */

  /* ss = limiter( D3e,   D2e,   ep );/\**\/ */
  /* st->eMK   = (e[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3e   + (1.0+kk*ss)*D2e   )*ipu); */

  /* st->pMK = (gamma0 - 1.0) * ( st->eMK - 0.5 * st->rhoMK * (st->uxMK*st->uxMK + st->uyMK*st->uyMK)); */
  /* st->cMK   = sqrt( gamma0*st->pMK/st->rhoMK );/\** 音速 **\/ */

  /* /\* φL(i-1/2) xi方向 *\/ */
  /* st->rhoPK = (rho[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1rho + (1.0+kk*ss)*D2rho )*ipu); */
  /* st->uxPK  = (ux[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1ux  + (1.0+kk*ss)*D2ux  )*ipu); */
  /* st->uyPK  = (uy[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1uy  + (1.0+kk*ss)*D2uy  )*ipu); */
  /* st->ePK   = (e[n][mK]  + 0.25*ss*( (1.0-kk*ss)*D1e   + (1.0+kk*ss)*D2e   )*ipu); */
  /* st->pPK = (gamma0 - 1.0) * ( st->ePK - 0.5 * st->rhoPK * (st->uxPK*st->uxPK + st->uyPK*st->uyPK)); */
  /* st->cPK   = sqrt( gamma0*st->pPK/st->rhoPK );/\** 音速 **\/ */

  /* /\* φR(i-1/2) xi方向 *\/ */
  /* st->rhoMK = (rho[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3rho + (1.0+kk*ss)*D2rho )*ipu); */
  /* st->uxMK  = (ux[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3ux  + (1.0+kk*ss)*D2ux  )*ipu); */
  /* st->uyMK  = (uy[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3uy  + (1.0+kk*ss)*D2uy  )*ipu); */
  /* st->eMK   = (e[n][r0]  - 0.25*ss*( (1.0-kk*ss)*D3e   + (1.0+kk*ss)*D2e   )*ipu); */
  /* st->pMK = (gamma0 - 1.0) * ( st->eMK - 0.5 * st->rhoMK * (st->uxMK*st->uxMK + st->uyMK*st->uyMK)); */
  /* st->cMK   = sqrt( gamma0*st->pMK/st->rhoMK );/\** 音速 **\/ */


  /* st->rhoPK = rho[n][mK]; */
  /* st->uxPK  = ux[n][mK]; */
  /* st->uyPK  = uy[n][mK]; */
  /* st->ePK   = e[n][mK]; */
  /* st->pPK   = (gamma0 - 1.0) * ( st->ePK - 0.5 * st->rhoPK * (st->uxPK*st->uxPK + st->uyPK*st->uyPK)); */
  /* st->cPK   = sqrt( gamma0*st->pPK/st->rhoPK );音速 */

  /* st->rhoMK = rho[n][r0]; */
  /* st->uxMK  = ux[n][r0]; */
  /* st->uyMK  = uy[n][r0]; */
  /* st->eMK   = e[n][r0]; */
  /* st->pMK   = (gamma0 - 1.0) * ( st->eMK - 0.5 * st->rhoMK * (st->uxMK*st->uxMK + st->uyMK*st->uyMK)); */
  /* st->cMK   = sqrt( gamma0*st->pMK/st->rhoMK );音速 */

}

static void slau_core(int r0,int n,double EFG[2][4]){
  int m;
  double Cbar, Mbar, ML, MR, betaL, betaR, pbar;
  double ukPK, ukMK, ukbarR, ukbarL, ukbar;
  double s0, s1;
  double mom;
  double uPK,uMK;
  double Xuai, Gmix, Jaco, Sk;
  MUSCL_struct st;

  for(m=0; m<2; m++){

    if(m == 0){ /* E */
      MUSCL_calc(r0, dG[n], n, &st);
      Jaco = 2.0 / (S[n][r0] + S[n][r0-dG[n]]);
      /* s0 = y_eta[n][r0]; */
      /* s1 = x_eta[n][r0]; */
      /* ukPK = (st.uxPK * y_eta[n][r0] + st.uyPK * x_eta[n][r0]) / sqrt(s0 * s0 + s1 * s1) / Jaco; */
      /* ukMK = (st.uxMK * y_eta[n][r0] + st.uyMK * x_eta[n][r0]) / sqrt(s0 * s0 + s1 * s1) / Jaco; */
      s0 = y_eta[n][r0] * Jaco;
      s1 = x_eta[n][r0] * Jaco;
      Sk = sqrt(s0 * s0 + s1 * s1);
      /* ukPK = (st.uxPK * y_eta[n][r0] + st.uyPK * x_eta[n][r0]) / sqrt(s0 * s0 + s1 * s1); */
      /* ukMK = (st.uxMK * y_eta[n][r0] + st.uyMK * x_eta[n][r0]) / sqrt(s0 * s0 + s1 * s1); */
      /* ukPK = (st.uxPK * y_eta[n][r0] + st.uyPK * x_eta[n][r0]); */
      /* ukMK = (st.uxMK * y_eta[n][r0] + st.uyMK * x_eta[n][r0]); */
      ukPK = (st.uxPK * s0 + st.uyPK * s1) / Sk;
      ukMK = (st.uxMK * s0 + st.uyMK * s1) / Sk;
    }
    else if(m == 1){ /* F */
      MUSCL_calc(r0, dE[n], n, &st);
      Jaco = 2.0 / (S[n][r0] + S[n][r0-dE[n]]);
      /* s0 = y_xi[n][r0]; */
      /* s1 = x_xi[n][r0]; */
      /* ukPK = (st.uxPK * y_xi[n][r0] + st.uyPK * x_xi[n][r0]) / sqrt(s0 * s0 + s1 * s1) / Jaco; */
      /* ukMK = (st.uxMK * y_xi[n][r0] + st.uyMK * x_xi[n][r0]) / sqrt(s0 * s0 + s1 * s1) / Jaco; */
      s0 = y_xi[n][r0] * Jaco;
      s1 = x_xi[n][r0] * Jaco;
      Sk = sqrt(s0 * s0 + s1 * s1);
      /* ukPK = (st.uxPK * y_xi[n][r0] + st.uyPK * x_xi[n][r0]) / sqrt(s0 * s0 + s1 * s1); */
      /* ukMK = (st.uxMK * y_xi[n][r0] + st.uyMK * x_xi[n][r0]) / sqrt(s0 * s0 + s1 * s1); */
      ukPK = (st.uxPK * s0 + st.uyPK * s1) / Sk;
      ukMK = (st.uxMK * s0 + st.uyMK * s1) / Sk;
    }

    /** 音速の平均値を求める **/ 
    Cbar = 0.5 * (st.cPK + st.cMK);
      
    /** マッハ数の平均値 **/	  
    /* ML = ukPK/(Cbar * sqrt(s0 * s0 + s1 * s1)); */
    /* MR = ukMK/(Cbar * sqrt(s0 * s0 + s1 * s1)); */
    ML = ukPK/(Cbar);
    MR = ukMK/(Cbar);


    Mbar = min2f(1.0, sqrt(0.5 * (st.uxPK * st.uxPK + st.uxMK * st.uxMK + st.uyPK * st.uyPK + st.uyMK * st.uyMK)) / Cbar);
    Xuai = (1.0 - Mbar) * (1.0 - Mbar);

    /** M_L **/
    if( fabs(ML) < 1.0   ){ betaL = 0.25 * ( 2.0 - ML ) *(ML + 1.0)*(ML + 1.0); }
    else if(  ML >=  1.0 ){ betaL = 1.0; }
    else                  { betaL = 0.0; }
    /** M_R **/  		      
    if( fabs(MR) < 1.0   ){ betaR = 0.25 * ( 2.0 + MR ) *(MR - 1.0)*(MR - 1.0); }
    else if(  MR >=  1.0 ){ betaR = 0.0; } 
    else                  { betaR = 1.0; } 
      
    /** 圧力 **/
    pbar = 0.5 * (st.pPK + st.pMK) + 0.5 * (betaL - betaR) * (st.pPK - st.pMK) + 0.5 * (1.0 - Xuai) * (betaL + betaR - 1.0) * (st.pPK + st.pMK);

    Gmix = -1.0 * max2f(min2f(ML, 0.0), -1.0) * min2f(max2f(MR, 0.0), 1.0);              //低M数では、0でも良い

    ukbar =  (st.rhoPK * fabs(ukPK)+ st.rhoMK * fabs(ukMK)) / (st.rhoPK + st.rhoMK);
    ukbarL = (1.0 - Gmix) * ukbar + Gmix * fabs(ukPK);
    ukbarR = (1.0 - Gmix) * ukbar + Gmix * fabs(ukMK);

    /****  momentum (i-1/2) xi方向 ****/
    mom = 0.5 * (st.rhoPK * (ukPK + ukbarL) + st.rhoMK * (ukMK - ukbarR) - Xuai * (st.pMK - st.pPK) / Cbar);
    /* mom = 0.5 * (st.rhoPK * (ukPK + ukbarL) + st.rhoMK * (ukMK - ukbarR) - Xuai * (st.pPK - st.pMK) / Cbar); */
    
    /** Fluxの計算                        ΦL                                    ΦR          p_(i-1/2)  **/
    /* EFG[m][0] = 0.5*(mom+fabs(mom))                            + 0.5*(mom-fabs(mom)); */
    /* EFG[m][1] = 0.5*(mom+fabs(mom))*    st.uxPK                + 0.5*(mom-fabs(mom))*    st.uxMK        + s0*pbar / Sk; */
    /* EFG[m][2] = 0.5*(mom+fabs(mom))*    st.uyPK                + 0.5*(mom-fabs(mom))*    st.uyMK        + s1*pbar / Sk; */
    /* EFG[m][3] = 0.5*(mom+fabs(mom))*(st.ePK+st.pPK)/st.rhoPK   + 0.5*(mom-fabs(mom))*(st.eMK+st.pMK)/st.rhoMK; */
    /* EFG[m][0] = Sk * (0.5*(mom+fabs(mom))                            + 0.5*(mom-fabs(mom))) / Jaco; */
    /* EFG[m][1] = Sk * (0.5*(mom+fabs(mom))*    st.uxPK                + 0.5*(mom-fabs(mom))*    st.uxMK        + s0*pbar / Sk) / Jaco; */
    /* EFG[m][2] = Sk * (0.5*(mom+fabs(mom))*    st.uyPK                + 0.5*(mom-fabs(mom))*    st.uyMK        + s1*pbar / Sk) / Jaco; */
    /* EFG[m][3] = Sk * (0.5*(mom+fabs(mom))*(st.ePK+st.pPK)/st.rhoPK   + 0.5*(mom-fabs(mom))*(st.eMK+st.pMK)/st.rhoMK) / Jaco; */
    EFG[m][0] = Sk * (0.5*(mom+fabs(mom))                            + 0.5*(mom-fabs(mom))) / Jaco;
    EFG[m][1] = Sk * (0.5*(mom+fabs(mom))*    st.uxPK                + 0.5*(mom-fabs(mom))*    st.uxMK        + s0*pbar / Sk) / Jaco;
    EFG[m][2] = Sk * (0.5*(mom+fabs(mom))*    st.uyPK                + 0.5*(mom-fabs(mom))*    st.uyMK        + s1*pbar / Sk) / Jaco;
    EFG[m][3] = Sk * (0.5*(mom+fabs(mom))*(st.ePK+st.pPK)/st.rhoPK   + 0.5*(mom-fabs(mom))*(st.eMK+st.pMK)/st.rhoMK) / Jaco;



/*     EFG[m][4] = 0.5*(mom+fabs(mom))*( gamma0*invgam1*st->pPK + 0.5*mom*mom/st->rhoPK )/st->rhoPK */
/*       + 0.5*(mom-fabs(mom))*( gamma0*invgam1*st->pMK + 0.5*mom*mom/st->rhoMK )/st->rhoMK; */
  }
}

void slau(){
  int n;

  for(n=0;n<NT;n++){
    int i, j;

#pragma omp parallel for private(i, j)
    for(j=2;   j<=jt[n]-3;   j++){       /*   面積ベクトルは (it-2)まで(個数は (it-1)コ) しかない。    */
      for(i=2;   i<=it[n]-3;   i++){     /*  (i<it-1)だと,pGの面積ベクトルはない。                     */
	int ii, r0;
	double EFG[2][4];
  
	r0 = dim[n](i, j);
	  
	slau_core(r0, n, EFG);

	E[n][0][r0] = EFG[_E_][0];
	E[n][1][r0] = EFG[_E_][1];
	E[n][2][r0] = EFG[_E_][2];
	E[n][3][r0] = EFG[_E_][3];


	F[n][0][r0] = EFG[_F_][0];
	F[n][1][r0] = EFG[_F_][1];
	F[n][2][r0] = EFG[_F_][2];
	F[n][3][r0] = EFG[_F_][3];


	for(ii=0;ii<4;ii++){
	  if(isnan(E[n][ii][r0])){
	    printf("E[%d][%d][r0] is nan! at (%d %d)\n",n,ii,i,j);
	    exit(1);
	  }
	  if(isnan(F[n][ii][r0])){
	    printf("F[%d][%d][r0] is nan! at (%d %d)\n",n,ii,i,j);
	    exit(1);
	  }
	  
	}

      }
    }
  }
}

