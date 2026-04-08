/*********************************************************/
/*   Lower Upper Symmetric Gauss Seidel Implicit Scheme  */
/*                     written by Fujisawa               */
/*********************************************************/
/* qq には sweep 中の保存変数補正量 dQ を入れる。 */
static  void calcPM(int rr,int n,int pmflag,int ddg,int dde,double **qq,double (*flux)[4])
{
  int ii;
  double ZZ,ZZ0,invQ,invdQ,kx,ky,kz,Sk,c;
  double Jaco;
  int rt, rk;
  int mflag;
  int ddd[2];
  int XI = 0;
  int ETA = 1;
  int X = 0;
  int Y = 1;
  double *SS[2][2];
  double tmpux ,tmpuy,tmprho,tmpp,tmpe;
  double spe;
  double tmp,Mu;
  double ALPHA = 1.01;

  ddd[XI]   = ddg;
  ddd[ETA]  = dde;  

  SS[XI][X]   = y_eta[n];
  SS[ETA][X]  = y_xi[n]; 
  
  SS[XI][Y]   = x_eta[n];
  SS[ETA][Y]  = x_xi[n];

  for(mflag=0;mflag<2;mflag++)
    {

      rt = rr + pmflag * ddd[mflag];

      if(qq[0][rt]!=0.0)
      	{
	  Jaco = 1.0 / S[n][rt];

	  kx  = 0.5 * (SS[mflag][X][rt] + SS[mflag][X][rt + ddd[mflag]]) * Jaco;
	  ky  = 0.5 * (SS[mflag][Y][rt] + SS[mflag][Y][rt + ddd[mflag]]) * Jaco;
	  
	  Sk = ( sqrt( kx*kx + ky*ky ) );
	  
	  /* invQ = 1.0 / (qq[0][rt] + Q[n][0][rt]); */
	  /* tmprho = (qq[0][rt] + Q[n][0][rt])*Jaco; */
	  /* tmpux  = (qq[1][rt] + Q[n][1][rt])*invQ; */
	  /* tmpuy  = (qq[2][rt] + Q[n][2][rt])*invQ; */
	  /* tmpe   = (qq[3][rt] + Q[n][3][rt])*Jaco; */
	  /* tmpp   = (gamma0 - 1.0) * (tmpe - 0.5 * tmprho * (tmpux*tmpux+tmpuy*tmpuy) ); */

	  invQ = 1.0 / (qq[0][rt] + rho[n][rt] * S[n][rt]);
	  tmprho = (qq[0][rt] * Jaco + rho[n][rt]);
	  tmpux  = (qq[1][rt] + ux[n][rt] * rho[n][rt] * S[n][rt])*invQ;
	  tmpuy  = (qq[2][rt] + uy[n][rt] * rho[n][rt] * S[n][rt])*invQ;
	  tmpe   = (qq[3][rt] * Jaco + e[n][rt]);
	  tmpp   = (gamma0 - 1.0) * (tmpe - 0.5 * tmprho * (tmpux*tmpux+tmpuy*tmpuy) );
	  
	  ZZ     = kx * tmpux + ky * tmpuy;
	  ZZ0    = kx* ux[n][rt] + ky* uy[n][rt];
	  c      = sqrt( gamma0 * Cons_calcP(n, rt) / rho[n][rt]);
	  tmp    = Cons_calcP(n , rt) / rho[n][rt] / Rair ; /** 温度 **/
	  Mu     = mu_0 * ( pow((tmp)/(273.15+20.0),1.5) * (273.15+20.0 + C)/(tmp + C));@p

	  spe= ALPHA * (fabs(ZZ0) + c*Sk)+ 2.0*(Mu+Mut[n][rt])*Sk*Sk/rho[n][rt];
	  /* spe= ALPHA * (fabs(ZZ0) + c*Sk); */
	  
	  flux[mflag][0] = 0.5*((tmprho*ZZ - rho[n][rt]*ZZ0)*S[n][rt] - pmflag * spe * qq[0][rt]);
	  flux[mflag][1] = 0.5*(((tmprho*tmpux*ZZ + kx*tmpp) - ( rho[n][rt]*ux[n][rt]*ZZ0 + kx*p[n][rt]) )*S[n][rt] - pmflag * spe * qq[1][rt]);
	  flux[mflag][2] = 0.5*(((tmprho*tmpuy*ZZ + ky*tmpp) - ( rho[n][rt]*uy[n][rt]*ZZ0 + ky*p[n][rt]) )*S[n][rt] - pmflag * spe * qq[2][rt]);
	  flux[mflag][3] = 0.5*(((tmpe+tmpp)*ZZ - (e[n][rt]+p[n][rt])*ZZ0)*S[n][rt] - pmflag * spe * qq[3][rt]);
      	}
      else{
      	flux[mflag][0] =0.0;
      	flux[mflag][1] =0.0;
      	flux[mflag][2] =0.0;
      	flux[mflag][3] =0.0;
      }
    }
  
}

static  void calcLx(int rr,int n,int ddg,int dde,double (*spe))
{
  double c,Jaco;
  double Sk;
  double kx,ky,ZZ,q2,b1;
  int mflag;
  
  double *SS[2][2];
  int ddd[2];
  double Mu,tmp;
  int XI = 0;
  int ETA = 1;
  int X = 0;
  int Y = 1;
  double ALPHA = 1.01;

  Jaco = 1.0 / S[n][rr];

  ddd[XI]   = ddg;
  ddd[ETA]  = dde;  

  SS[XI][X]   = y_eta[n];
  SS[ETA][X]  = y_xi[n];
  
  SS[XI][Y]   = x_eta[n];
  SS[ETA][Y]  = x_xi[n];

  for(mflag=0;mflag<2;mflag++)
    {      
      kx  = 0.5 * (SS[mflag][X][rr] + SS[mflag][X][rr + ddd[mflag]]) * Jaco;
      ky  = 0.5 * (SS[mflag][Y][rr] + SS[mflag][Y][rr + ddd[mflag]]) * Jaco;
	  	 
      ZZ  = kx * ux[n][rr] + ky * uy[n][rr];
      Sk =( sqrt( kx * kx + ky * ky) );
      c  = sqrt( gamma0 * Cons_calcP(n, rr) / rho[n][rr]);
      tmp = Cons_calcP(n , rr) / rho[n][rr] / Rair ; /** 温度 **/
      Mu  = mu_0 * ( pow((tmp) / (273.15+20.0), 1.5) * (273.15 + 20.0 + C)/(tmp + C));
      spe[mflag] = ALPHA * (fabs(ZZ) + c*Sk) + 2.0*(Mu+Mut[n][rr])*Sk*Sk/rho[n][rr];
      /* spe[mflag] = ALPHA * (fabs(ZZ) + c*Sk); */

    }
}

/* 保存変数の補正量と一時 RHS 配列を初期化する。 */
void dQ_Initial(){
  int n, r0, i, j;

  for(n=0;n<NT;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	dQ[n][0][r0] = 0.0;
	dQ[n][1][r0] = 0.0;
	dQ[n][2][r0] = 0.0;
	dQ[n][3][r0] = 0.0;

	rhsF[n][0][r0] = 0.0;
	rhsF[n][1][r0] = 0.0;
	rhsF[n][2][r0] = 0.0;
	rhsF[n][3][r0] = 0.0;
      }
    }
  }

}

/* 物理時間 1 ステップの処理。
   1. 流束を組み直す。
   2. LU-SGS の前進・後退 sweep を行う。
   3. Q から基本変数を更新する。 */
void gauss_seidel(int time){
  int itr, n, ii, jj, kk, nn, numk;
  double errormax;
  double error4;

  itr = 0;

  dQ_Initial();
    
  for(itr=0;itr<t_NUMBER;itr++){

    /* 現在の場から対流流束と粘性流束を再計算する。 */
    fds();
    /* shus(); */
    /* slau(); */
    viscous();

    ii = jj = kk = 0;
    errormax = 0.0;

    for(n=0;n<NT;n++){
      int i, j, r0;

#ifdef _OPENMP
      omp_set_nested(1);
#pragma omp parallel num_threads(8)
      {
#endif

#pragma omp for private(i, j, r0)
	  for(j=2;j<jt[n]-3;j++){
	    for(i=2;i<it[n]-3;i++){
	      double Jaco, invQ;
	      double RHS0, RHS1, RHS2, RHS3;
	      double spe_r0[2];
	      double deltaFlux[2][4];
	      double rhs1[4];
	      double LDinv;  
	      int XI = 0;
	      int ETA = 1;

	      r0 = dim[n](i, j);

	      /* 有限体積法の収支式から陽的残差を作る。 */
	      RHS0 = - dt * ((E[n][0][r0+dG[n]] - E[n][0][r0]) - (Ev[n][0][r0+dG[n]] - Ev[n][0][r0]) + (F[n][0][r0+dE[n]] - F[n][0][r0]) - (Fv[n][0][r0+dE[n]] - Fv[n][0][r0]));
	      RHS1 = - dt * ((E[n][1][r0+dG[n]] - E[n][1][r0]) - (Ev[n][1][r0+dG[n]] - Ev[n][1][r0]) + (F[n][1][r0+dE[n]] - F[n][1][r0]) - (Fv[n][1][r0+dE[n]] - Fv[n][1][r0]));
	      RHS2 = - dt * ((E[n][2][r0+dG[n]] - E[n][2][r0]) - (Ev[n][2][r0+dG[n]] - Ev[n][2][r0]) + (F[n][2][r0+dE[n]] - F[n][2][r0]) - (Fv[n][2][r0+dE[n]] - Fv[n][2][r0]));
	      RHS3 = - dt * ((E[n][3][r0+dG[n]] - E[n][3][r0]) - (Ev[n][3][r0+dG[n]] - Ev[n][3][r0]) + (F[n][3][r0+dE[n]] - F[n][3][r0]) - (Fv[n][3][r0+dE[n]] - Fv[n][3][r0]));


	      if(itr==0){
	      	tmpEE[n][0][r0] = RHS0;
	      	tmpEE[n][1][r0] = RHS1;
	      	tmpEE[n][2][r0] = RHS2;
	      	tmpEE[n][3][r0] = RHS3;
	      }

	      rhs1[0] = (tmpQ[n][0][r0] - Q[n][0][r0]) + 0.5 * (RHS0 + tmpEE[n][0][r0]);
	      rhs1[1] = (tmpQ[n][1][r0] - Q[n][1][r0]) + 0.5 * (RHS1 + tmpEE[n][1][r0]);
	      rhs1[2] = (tmpQ[n][2][r0] - Q[n][2][r0]) + 0.5 * (RHS2 + tmpEE[n][2][r0]);
	      rhs1[3] = (tmpQ[n][3][r0] - Q[n][3][r0]) + 0.5 * (RHS3 + tmpEE[n][3][r0]);

	      calcPM(r0,n,-1,dG[n],dE[n],dQ[n],deltaFlux);

	      rhs1[0] += lambda * dt * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
	      rhs1[1] += lambda * dt * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
	      rhs1[2] += lambda * dt * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
	      rhs1[3] += lambda * dt * (deltaFlux[XI][3]+deltaFlux[ETA][3]);

	      calcLx(r0,n,dG[n],dE[n],spe_r0);	    
	      LDinv =  1.0 / (1.0+lambda * dt*(spe_r0[0]+spe_r0[1]));

	      dQ[n][0][r0] = rhs1[0] * LDinv;
	      dQ[n][1][r0] = rhs1[1] * LDinv;
	      dQ[n][2][r0] = rhs1[2] * LDinv;
	      dQ[n][3][r0] = rhs1[3] * LDinv;
	    }
	  }

#pragma omp for private(i, j, r0)
	  for(j=jt[n]-4;j>1;j--){
	    for(i=it[n]-4;i>1;i--){
	      double Jaco, invQ;
	      double RHS0, RHS1, RHS2, RHS3;
	      double spe_r0[2];
	      double deltaFlux[2][4];
	      double rhs1[4];
	      double LDinv;
	      int XI = 0;
	      int ETA = 1;

	      r0 = dim[n](i, j);

	      /* calcPM(r0,n,1,dG[n],dE[n],dQ[n],deltaFlux); */

	      /* rhs1[0] = lambda * dt * (deltaFlux[XI][0]+deltaFlux[ETA][0]); */
	      /* rhs1[1] = lambda * dt * (deltaFlux[XI][1]+deltaFlux[ETA][1]); */
	      /* rhs1[2] = lambda * dt * (deltaFlux[XI][2]+deltaFlux[ETA][2]); */
	      /* rhs1[3] = lambda * dt * (deltaFlux[XI][3]+deltaFlux[ETA][3]); */

	      /* calcLx(r0,n,dG[n],dE[n],spe_r0); */
	      /* LDinv =  1.0 / (1.0+lambda * dt*(spe_r0[0]+spe_r0[1])); */

	      /* dQ[n][0][r0] = dQ[n][0][r0] - rhs1[0] * LDinv; */
	      /* dQ[n][1][r0] = dQ[n][1][r0] - rhs1[1] * LDinv; */
	      /* dQ[n][2][r0] = dQ[n][2][r0] - rhs1[2] * LDinv; */
	      /* dQ[n][3][r0] = dQ[n][3][r0] - rhs1[3] * LDinv; */

	      rhsF[n][0][r0] = dQ[n][0][r0];
	      rhsF[n][1][r0] = dQ[n][1][r0];
	      rhsF[n][2][r0] = dQ[n][2][r0];
	      rhsF[n][3][r0] = dQ[n][3][r0];

	      /* 後退 sweep では前方セル側の寄与を差し引く。 */
	      calcPM(r0,n,1,dG[n],dE[n],rhsF[n],deltaFlux);

	      rhs1[0] = lambda * dt * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
	      rhs1[1] = lambda * dt * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
	      rhs1[2] = lambda * dt * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
	      rhs1[3] = lambda * dt * (deltaFlux[XI][3]+deltaFlux[ETA][3]);

	      calcLx(r0,n,dG[n],dE[n],spe_r0);
	      LDinv =  1.0 / (1.0+lambda * dt*(spe_r0[0]+spe_r0[1]));

	      rhsF[n][0][r0] = dQ[n][0][r0] - rhs1[0] * LDinv;
	      rhsF[n][1][r0] = dQ[n][1][r0] - rhs1[1] * LDinv;
	      rhsF[n][2][r0] = dQ[n][2][r0] - rhs1[2] * LDinv;
	      rhsF[n][3][r0] = dQ[n][3][r0] - rhs1[3] * LDinv;
	    }
	  }
#pragma omp for private(i, j, r0)
      for(j=2;j<jt[n]-3;j++){
	  for(i=2;i<it[n]-3;i++){
	    double Jaco, invQ;
	    double RHS0, RHS1, RHS2, RHS3;
	    double LDinv;  
	    r0 = dim[n](i, j);
	    Jaco = 1.0 / S[n][r0];

	    /* Q[n][0][r0] = Q[n][0][r0] + dQ[n][0][r0]; */
	    /* Q[n][1][r0] = Q[n][1][r0] + dQ[n][1][r0]; */
	    /* Q[n][2][r0] = Q[n][2][r0] + dQ[n][2][r0]; */
	    /* Q[n][3][r0] = Q[n][3][r0] + dQ[n][3][r0]; */

	    Q[n][0][r0] = Q[n][0][r0] + rhsF[n][0][r0];
	    Q[n][1][r0] = Q[n][1][r0] + rhsF[n][1][r0];
	    Q[n][2][r0] = Q[n][2][r0] + rhsF[n][2][r0];
	    Q[n][3][r0] = Q[n][3][r0] + rhsF[n][3][r0];

	    dQ[n][0][r0] = rhsF[n][0][r0];
	    dQ[n][1][r0] = rhsF[n][1][r0];
	    dQ[n][2][r0] = rhsF[n][2][r0];
	    dQ[n][3][r0] = rhsF[n][3][r0];

	    /* 補正量を反映し、Q から rho, u, e を取り出す。 */
	    invQ = 1.0 / Q[n][0][r0];  /* = 1.0/(rho*v) */

	    rho[n][r0] = Q[n][0][r0] * Jaco;      /*        ^         */
	    ux[n][r0]  = Q[n][1][r0] * invQ;      /* Q とは Q のこと。*/
	    uy[n][r0]  = Q[n][2][r0] * invQ;
	    e[n][r0]   = Q[n][3][r0] * Jaco;
	
	    p[n][r0] = Cons_calcP(n, r0);

	    error4 = dQ[n][3][r0] / Q[n][3][r0];

	    if(errormax < fabs(error4)){
	      errormax = fabs(error4);
	      ii = i;
	      jj = j;
	      nn = n;
	    }


	    if(isnan(rho[n][r0])){
	      printf("rho is nan! at (%d %d)\n",i,j);
	      exit(1);
	    }
	    if(isnan(ux[n][r0])){
	      printf("ux is nan! at (%d %d)\n",i,j);
	      exit(1);
	    }
	    if(isnan(uy[n][r0])){
	      printf("uy is nan! at (%d %d)\n",i,j);
	      exit(1);
	    }
	    if(isnan(e[n][r0])){
	      printf("e is nan! at (%d %d)\n",i,j);
	      exit(1);
	    }

	  }
	}
#ifdef _OPENMP
      }
#endif
    }

    /* 更新後の内部点に合わせてゴーストセルとブロック境界を更新する。 */
    boundary();

    if(itr==(t_NUMBER-1)){
      printf("time:%d n:%d i:%d j:%d errormax:%e itr:%d\n",time,nn,ii,jj,errormax,itr);
    }
    
  }

}
