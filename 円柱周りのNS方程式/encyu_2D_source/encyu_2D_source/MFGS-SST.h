/*********************************************************/
/*   Lower Upper Symmetric Gauss Seidel Implicit Scheme  */
/*                     written by Fujisawa               */
/*********************************************************/

#define inneritr 4 //内部反復数の定義　適宜変更すること 論文によると10回以内で充分

#define sita11   1.5     //時間二次精度 sita11 = 1.5 / sita22 = 2 
#define sita22   2       //時間一次精度 sita11 = 1.0 / sita22 = 1
/* 行列を明示的に作らず、隣接セルとの陰的結合項を評価する。
   pmflag = -1 なら後方側、pmflag = +1 なら前方側の隣接セルを使う。 */
static  void calcPM(int rr,int n,int pmflag,int ddg,int dde,double **qq,double **turbqq,double (*flux)[6],double (*spe))
{
  int ii;
  double ZZ,ZZ0,invQ,kx,ky,kz,Sk,c;
  double Jacort, Jacork, Jaco;
  int rt, rk, rmet;
  int mflag;
  int ddd[2];
  int XI = 0;
  int ETA = 1;
  int X = 0;
  int Y = 1;
  double *SS[2][2];
  double tmpux ,tmpuy,tmprho,tmpp,tmpe,tmpk,tmpomega;
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

      rt = rr;
      rk = rt + pmflag * ddd[mflag];
      rmet = rr;

      if(pmflag==1){
	rmet = rk;
      }
      
      if(qq[0][rt]!=0.0)
      	{
	  Jaco   = 2.0 / (S[n][rt] + S[n][rk]);
	  Jacort = 1.0 / S[n][rt];
	  Jacork = 1.0 / S[n][rk];

	  kx  = SS[mflag][X][rmet] * Jaco;
	  ky  = SS[mflag][Y][rmet] * Jaco;
	  
	  Sk = ( sqrt( kx*kx + ky*ky ) );
	  
	  invQ = 1.0 / (qq[0][rk] + rho[n][rt] * S[n][rt]);
	  tmprho = (qq[0][rk] * Jacork + rho[n][rt]);
	  tmpux  = (qq[1][rk] + ux[n][rt] * rho[n][rt] * S[n][rt])*invQ;
	  tmpuy  = (qq[2][rk] + uy[n][rt] * rho[n][rt] * S[n][rt])*invQ;
	  tmpe   = (qq[3][rk] * Jacork + e[n][rt]);
	  tmpk       = (turbqq[0][rk] + k_turb[n][rt] * rho[n][rt] * S[n][rt])*invQ;
	  tmpomega   = (turbqq[1][rk] + omega[n][rt]  * rho[n][rt] * S[n][rt])*invQ;
	  tmpp   = (gamma0 - 1.0) * (tmpe - 0.5 * tmprho * (tmpux*tmpux+tmpuy*tmpuy) );
	  
	  ZZ     = (kx * tmpux + ky * tmpuy);
	  ZZ0    = 0.5 * (kx* (ux[n][rt] + ux[n][rk]) + ky* (uy[n][rt] + uy[n][rk]));
	  c      = sqrt( gamma0 * Cons_calcP(n, rt) / rho[n][rt]);
	  tmp    = Cons_calcP(n , rt) / rho[n][rt] / Rair; /** 温度 **/
	  Mu     = mu_0 * ( pow((tmp)/(273.15+20.0),1.5) * (273.15+20.0 + C)/(tmp + C));
		      		      

	  spe[mflag]= fabs(ZZ0) + c*Sk + 2.0*(Mu+Mut[n][rt])*Sk*Sk/rho[n][rt];

	  /* spe= (fabs(ZZ0) + c + 2.0*(Mu+Mut[n][rt])*Sk/rho[n][rt]); */

	  /* spe= ALPHA * (fabs(ZZ0) + c*Sk)+ 2.0*(Mu+Mut[n][rt]+gamma0)*Sk*Sk/rho[n][rt]; */
	  /* spe= ALPHA * (fabs(ZZ0) + c*Sk); */
	  
	  flux[mflag][0] = 0.5*((tmprho*ZZ)/Jaco - pmflag * spe[mflag] * qq[0][rk]);
	  flux[mflag][1] = 0.5*((tmprho*tmpux*ZZ + kx*tmpp)/Jaco - pmflag * spe[mflag] * qq[1][rk]);
	  flux[mflag][2] = 0.5*((tmprho*tmpuy*ZZ + ky*tmpp)/Jaco - pmflag * spe[mflag] * qq[2][rk]);
	  flux[mflag][3] = 0.5*(((tmpe+tmpp)*ZZ)/Jaco - pmflag * spe[mflag] * qq[3][rk]);
	  flux[mflag][4] = 0.5*((tmprho*tmpk*ZZ)/Jaco - pmflag * spe[mflag] * turbqq[0][rk]);
	  flux[mflag][5] = 0.5*((tmprho*tmpomega*ZZ)/Jaco - pmflag * spe[mflag] * turbqq[1][rk]);
	}
      else{
      	flux[mflag][0] =0.0;
      	flux[mflag][1] =0.0;
      	flux[mflag][2] =0.0;
      	flux[mflag][3] =0.0;
      	flux[mflag][4] =0.0;
      	flux[mflag][5] =0.0;
      }
    }
  
}

/* 新しい時間ステップの前に補正量と RHS 配列を初期化する。 */
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
	TurbdQ[n][0][r0] = 0.0;
	TurbdQ[n][1][r0] = 0.0;

	rhsF[n][0][r0] = 0.0;
	rhsF[n][1][r0] = 0.0;
	rhsF[n][2][r0] = 0.0;
	rhsF[n][3][r0] = 0.0;
	rhsTurbF[n][0][r0] = 0.0;
	rhsTurbF[n][1][r0] = 0.0;
      }
    }
  }

}
/* 流れ場と SST を連成して 1 ステップ進める。
   1. 残差を組み立てる。
   2. 陰的補正量を反復で求める。
   3. Q を更新し、基本変数を取り直す。 */
void gauss_seidel(int time){
  int itr, n, ii, jj, kk, nn, numk, t;
  double errormax;
  double error4;

  itr = 0;

  dQ_Initial();
    
  for(itr=0;itr<2;itr++){

    /* 最新の基本変数から対流・粘性流束を再計算する。 */
    fds();
    /* fds_komega(); */
    /* slau(); */
    /* shus(); */
    viscous();
    viscous_komega();


    ii = jj = kk = 0;
    errormax = 0.0;


    /* Step 1: 陰的反復の元になる陽的残差を組み立てる。 */
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
	    double RHS0, RHS1, RHS2, RHS3, RHS4, RHS5, RHSt[2];
	    double spe_r0[2];
	    double spe_rt[2];
	    double deltaFlux[2][6];
	    double rhs1[6];
	    double LDinv;  
	    int XI = 0;
	    int ETA = 1;

	    r0 = dim[n](i, j);

	    RHS0 = - dt * ((E[n][0][r0+dG[n]] - E[n][0][r0]) - (Ev[n][0][r0+dG[n]] - Ev[n][0][r0]) + (F[n][0][r0+dE[n]] - F[n][0][r0]) - (Fv[n][0][r0+dE[n]] - Fv[n][0][r0]));
	    RHS1 = - dt * ((E[n][1][r0+dG[n]] - E[n][1][r0]) - (Ev[n][1][r0+dG[n]] - Ev[n][1][r0]) + (F[n][1][r0+dE[n]] - F[n][1][r0]) - (Fv[n][1][r0+dE[n]] - Fv[n][1][r0]));
	    RHS2 = - dt * ((E[n][2][r0+dG[n]] - E[n][2][r0]) - (Ev[n][2][r0+dG[n]] - Ev[n][2][r0]) + (F[n][2][r0+dE[n]] - F[n][2][r0]) - (Fv[n][2][r0+dE[n]] - Fv[n][2][r0]));
	    RHS3 = - dt * ((E[n][3][r0+dG[n]] - E[n][3][r0]) - (Ev[n][3][r0+dG[n]] - Ev[n][3][r0]) + (F[n][3][r0+dE[n]] - F[n][3][r0]) - (Fv[n][3][r0+dE[n]] - Fv[n][3][r0]));

	    calc_komega(n, r0, RHSt);

	    RHS4 = - dt * ((TurbE[n][0][r0+dG[n]] - TurbE[n][0][r0]) - (TurbEv[n][0][r0+dG[n]] - TurbEv[n][0][r0]) + (TurbF[n][0][r0+dE[n]] - TurbF[n][0][r0]) - (TurbFv[n][0][r0+dE[n]] - TurbFv[n][0][r0]) - RHSt[0]);
	    RHS5 = - dt * ((TurbE[n][1][r0+dG[n]] - TurbE[n][1][r0]) - (TurbEv[n][1][r0+dG[n]] - TurbEv[n][1][r0]) + (TurbF[n][1][r0+dE[n]] - TurbF[n][1][r0]) - (TurbFv[n][1][r0+dE[n]] - TurbFv[n][1][r0]) - RHSt[1]);



	    /* 段の最初の残差を保存し、台形則型の更新に使う。 */
	    if(itr==0){
	      tmpEE[n][0][r0] = RHS0;
	      tmpEE[n][1][r0] = RHS1;
	      tmpEE[n][2][r0] = RHS2;
	      tmpEE[n][3][r0] = RHS3;
	      TurbtmpEE[n][0][r0] = RHS4;
	      TurbtmpEE[n][1][r0] = RHS5;
	    }

	    rhsF[n][0][r0] = (tmpQ[n][0][r0] - Q[n][0][r0]) + 0.5 * (RHS0 + tmpEE[n][0][r0]);
	    rhsF[n][1][r0] = (tmpQ[n][1][r0] - Q[n][1][r0]) + 0.5 * (RHS1 + tmpEE[n][1][r0]);
	    rhsF[n][2][r0] = (tmpQ[n][2][r0] - Q[n][2][r0]) + 0.5 * (RHS2 + tmpEE[n][2][r0]);
	    rhsF[n][3][r0] = (tmpQ[n][3][r0] - Q[n][3][r0]) + 0.5 * (RHS3 + tmpEE[n][3][r0]);
	    rhsTurbF[n][0][r0] = (TurbtmpQ[n][0][r0] - TurbQ[n][0][r0]) + 0.5 * (RHS4 + TurbtmpEE[n][0][r0]);
	    rhsTurbF[n][1][r0] = (TurbtmpQ[n][1][r0] - TurbQ[n][1][r0]) + 0.5 * (RHS5 + TurbtmpEE[n][1][r0]);

	  }
	}
#ifdef _OPENMP
      }
#endif
    }

    /* Step 2: 行列を作らない sweep 反復で線形化補正量を求める。 */
    for(t=0;t<inneritr;t++){
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
	      double spe_rt[2];
	      double deltaFlux[2][6];
	      double rhs1[6];
	      double LDinv;  
	      int XI = 0;
	      int ETA = 1;

	      r0 = dim[n](i, j);
				
	      /* 下側隣接セルの寄与を加える。 */
	      calcPM(r0,n,-1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux,spe_r0);

	      rhs1[0] = rhsF[n][0][r0] + dt * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
	      rhs1[1] = rhsF[n][1][r0] + dt * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
	      rhs1[2] = rhsF[n][2][r0] + dt * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
	      rhs1[3] = rhsF[n][3][r0] + dt * (deltaFlux[XI][3]+deltaFlux[ETA][3]);
	      rhs1[4] = rhsTurbF[n][0][r0] + dt * (deltaFlux[XI][4]+deltaFlux[ETA][4]);
	      rhs1[5] = rhsTurbF[n][1][r0] + dt * (deltaFlux[XI][5]+deltaFlux[ETA][5]);

	      /* 上側隣接セルの寄与を加える。 */
	      calcPM(r0,n,1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux,spe_rt);

	      rhs1[0] -= dt * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
	      rhs1[1] -= dt * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
	      rhs1[2] -= dt * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
	      rhs1[3] -= dt * (deltaFlux[XI][3]+deltaFlux[ETA][3]);
	      rhs1[4] -= dt * (deltaFlux[XI][4]+deltaFlux[ETA][4]);
	      rhs1[5] -= dt * (deltaFlux[XI][5]+deltaFlux[ETA][5]);

	      LDinv =  1.0 / (1.0+0.5*dt*(spe_r0[0]+spe_r0[1]+spe_rt[0]+spe_rt[1]));

	      dQ[n][0][r0] = rhs1[0] * LDinv;
	      dQ[n][1][r0] = rhs1[1] * LDinv;
	      dQ[n][2][r0] = rhs1[2] * LDinv;
	      dQ[n][3][r0] = rhs1[3] * LDinv;
	      TurbdQ[n][0][r0] = rhs1[4] * LDinv;
	      TurbdQ[n][1][r0] = rhs1[5] * LDinv;
	    }
	  }

#pragma omp for private(i, j, r0)
	  for(j=jt[n]-4;j>1;j--){
	    for(i=it[n]-4;i>1;i--){
	      double Jaco, invQ;
	      double RHS0, RHS1, RHS2, RHS3;
	      double spe_r0[2];
	      double spe_rt[2];
	      double deltaFlux[2][6];
	      double rhs1[6];
	      double LDinv;  
	      int XI = 0;
	      int ETA = 1;

	      r0 = dim[n](i, j);
				
	      calcPM(r0,n,-1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux,spe_r0);

	      rhs1[0] = rhsF[n][0][r0] + dt * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
	      rhs1[1] = rhsF[n][1][r0] + dt * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
	      rhs1[2] = rhsF[n][2][r0] + dt * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
	      rhs1[3] = rhsF[n][3][r0] + dt * (deltaFlux[XI][3]+deltaFlux[ETA][3]);
	      rhs1[4] = rhsTurbF[n][0][r0] + dt * (deltaFlux[XI][4]+deltaFlux[ETA][4]);
	      rhs1[5] = rhsTurbF[n][1][r0] + dt * (deltaFlux[XI][5]+deltaFlux[ETA][5]);

	      calcPM(r0,n,1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux,spe_rt);

	      rhs1[0] -= dt * (deltaFlux[XI][0]+deltaFlux[ETA][0]);
	      rhs1[1] -= dt * (deltaFlux[XI][1]+deltaFlux[ETA][1]);
	      rhs1[2] -= dt * (deltaFlux[XI][2]+deltaFlux[ETA][2]);
	      rhs1[3] -= dt * (deltaFlux[XI][3]+deltaFlux[ETA][3]);
	      rhs1[4] -= dt * (deltaFlux[XI][4]+deltaFlux[ETA][4]);
	      rhs1[5] -= dt * (deltaFlux[XI][5]+deltaFlux[ETA][5]);

	      LDinv =  1.0 / (1.0+0.5*dt*(spe_r0[0]+spe_r0[1]+spe_rt[0]+spe_rt[1]));

	      dQ[n][0][r0] = rhs1[0] * LDinv;
	      dQ[n][1][r0] = rhs1[1] * LDinv;
	      dQ[n][2][r0] = rhs1[2] * LDinv;
	      dQ[n][3][r0] = rhs1[3] * LDinv;
	      TurbdQ[n][0][r0] = rhs1[4] * LDinv;
	      TurbdQ[n][1][r0] = rhs1[5] * LDinv;
	    }
	  }
#ifdef _OPENMP
	}
#endif
      }
    }
  

    /* Step 3: 補正量を反映し、基本変数と乱流変数を更新する。 */
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
	    double LDinv;  
	    double a1 = 0.31, omega_mut;

	    r0 = dim[n](i, j);
	    Jaco = 1.0 / S[n][r0];

	    Q[n][0][r0] = Q[n][0][r0] + dQ[n][0][r0];
	    Q[n][1][r0] = Q[n][1][r0] + dQ[n][1][r0];
	    Q[n][2][r0] = Q[n][2][r0] + dQ[n][2][r0];
	    Q[n][3][r0] = Q[n][3][r0] + dQ[n][3][r0];

	    TurbQ[n][0][r0] = TurbQ[n][0][r0] + TurbdQ[n][0][r0];
	    TurbQ[n][1][r0] = TurbQ[n][1][r0] + TurbdQ[n][1][r0];

	    /* 保存変数から基本変数を取り出し直す。 */
	    invQ = 1.0 / Q[n][0][r0];  /* = 1.0/(rho*v) */

	    rho[n][r0] = Q[n][0][r0] * Jaco;      /*        ^         */
	    ux[n][r0]  = Q[n][1][r0] * invQ;      /* Q とは Q のこと。*/
	    uy[n][r0]  = Q[n][2][r0] * invQ;
	    e[n][r0]   = Q[n][3][r0] * Jaco;
	
	    p[n][r0] = Cons_calcP(n, r0);

	    k_turb[n][r0] = TurbQ[n][0][r0] * invQ;

	    if(k_turb[n][r0] < 1.0e-10){
	      k_turb[n][r0] = 1.0e-10;
	    }

	    omega[n][r0]  = TurbQ[n][1][r0] * invQ;
	    omega_mut = max2f(a1 * omega[n][r0], calc_W(n, r0) * calc_F2(n, r0));
	    Mut[n][r0] = a1 * rho[n][r0] * k_turb[n][r0] / omega_mut;

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
	      if(isnan(k_turb[n][r0])){ printf("k is nan! n=%d %d %d %e %e %e %e %d\n",time,i,j,k_turb[n][r0],omega[n][r0],Mut[n][r0],rho[n][r0],itr); exit(1);}
	      if(isnan(omega[n][r0])){ printf("omega is nan! n=%d %d %d %e %e %e %e %d\n",time,i,j,k_turb[n][r0],omega[n][r0],Mut[n][r0],rho[n][r0],itr); exit(1);}
	    

	  }
	}
#ifdef _OPENMP
      }
#endif
    }

    /* 次の外側反復に入る前にゴーストセルとブロック境界を更新する。 */
    boundary();

    if(itr==0){
      printf("time:%d n:%d i:%d j:%d errormax:%e itr:%d\n",time,nn,ii,jj,errormax,itr);
    }
    
  }
}
