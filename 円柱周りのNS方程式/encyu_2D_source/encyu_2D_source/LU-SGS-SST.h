/******************************************************/
/*                                                    */
/* Lower Upper Symmetric Gauss Seidel Implicit Scheme */
/*                       +komega                      */
/*                                                    */
/******************************************************/
/* qq/turbqq には流れ場と乱流変数の補正量を入れる。 */

static void calcPM(int rr,int n,int pmflag,int ddg,int dde,double **qq,double **turbqq,double (*flux)[6]){
  int ii;
  double ZZ,ZZ0,invQ,invdQ,kx,ky,Sk,c;
  double Jaco;
  int rk,rt;
  int mflag;
  int ddd[2];
  int XI=0;
  int ETA=1;
  int X=0;
  int Y=1;
  double *SS[2][2];
  double tmpux,tmpuy,tmprho,tmpp,tmpe,tmpk,tmpomega;
  double spe;
  double tmp,Mu;
  double ALPHA=1.01;

  ddd[XI]=ddg;
  ddd[ETA]=dde;

  SS[XI][X]=y_eta[n];
  SS[ETA][X]=y_xi[n];

  SS[XI][Y]=x_eta[n];
  SS[ETA][Y]=x_xi[n];

  for(mflag=0;mflag<2;mflag++){
    rt=rr+pmflag*ddd[mflag];

    if(qq[0][rt]!=0.0){
      Jaco=1.0/S[n][rt];

      kx=0.5*(SS[mflag][X][rt]+SS[mflag][X][rt+ddd[mflag]])*Jaco;
      ky=0.5*(SS[mflag][Y][rt]+SS[mflag][Y][rt+ddd[mflag]])*Jaco;

      Sk=(sqrt(kx*kx+ky*ky));

      invQ=1.0/(qq[0][rt]+rho[n][rt]*S[n][rt]);
      tmprho  =(qq[0][rt]*Jaco+rho[n][rt]);
      tmpux   =(qq[1][rt]+ux[n][rt]*rho[n][rt]*S[n][rt])*invQ;
      tmpuy   =(qq[2][rt]+uy[n][rt]*rho[n][rt]*S[n][rt])*invQ;
      tmpe    =(qq[3][rt]*Jaco+e[n][rt]);
      tmpk    =(turbqq[0][rt]+k_turb[n][rt]*rho[n][rt]*S[n][rt])*invQ;
      tmpomega=(turbqq[1][rt]+omega[n][rt]*rho[n][rt]*S[n][rt])*invQ;
      tmpp    =(gamma0-1.0)*(tmpe-0.5*tmprho*(tmpux*tmpux+tmpuy*tmpuy));

      ZZ=kx*tmpux+ky*tmpuy;
      ZZ0=kx*ux[n][rt]+ky*uy[n][rt];
      c=sqrt(gamma0*Cons_calcP(n, rt)/rho[n][rt]);
      tmp=Cons_calcP(n, rt)/rho[n][rt]/Rair;
      Mu=mu_0*(pow((tmp)/(273.15+20.0),1.5)*(273.15+20.0+C)/(tmp+C));

      spe=ALPHA*(fabs(ZZ0)+c*Sk)+2.0*(Mu+Mut[n][rt])*Sk*Sk/rho[n][rt];

      flux[mflag][0]=0.5*((tmprho*ZZ-rho[n][rt]*ZZ0)*S[n][rt]-pmflag*spe*qq[0][rt]);
      flux[mflag][1]=0.5*(((tmprho*tmpux*ZZ+kx*tmpp)-(rho[n][rt]*ux[n][rt]*ZZ0+kx*p[n][rt]))*S[n][rt]-pmflag*spe*qq[1][rt]);
      flux[mflag][2]=0.5*(((tmprho*tmpuy*ZZ+ky*tmpp)-(rho[n][rt]*uy[n][rt]*ZZ0+ky*p[n][rt]))*S[n][rt]-pmflag*spe*qq[2][rt]);
      flux[mflag][3]=0.5*(((tmpe+tmpp)*ZZ-(e[n][rt]+p[n][rt])*ZZ0)*S[n][rt]-pmflag*spe*qq[3][rt]);
      flux[mflag][4]=0.5*((tmprho*tmpk*ZZ-rho[n][rt]*k_turb[n][rt]*ZZ0)*S[n][rt]-pmflag*spe*turbqq[0][rt]);
      flux[mflag][5]=0.5*((tmprho*tmpomega*ZZ-rho[n][rt]*omega[n][rt]*ZZ0)*S[n][rt]-pmflag*spe*turbqq[1][rt]);
    }else{
      flux[mflag][0]=0.0;
      flux[mflag][1]=0.0;
      flux[mflag][2]=0.0;
      flux[mflag][3]=0.0;
      flux[mflag][4]=0.0;
      flux[mflag][5]=0.0;
    }
  }

}

static void calcLx(int rr,int n,int ddg,int dde,double (*spe)){
  double c,Jaco;
  double Sk;
  double kx,ky,ZZ,q2,b1;
  int mflag;

  double *SS[2][2];
  int ddd[2];
  double Mu,tmp;
  int XI=0;
  int ETA=1;
  int X=0;
  int Y=1;
  double ALPHA=1.01;

  Jaco=1.0/S[n][rr];

  ddd[XI]=ddg;
  ddd[ETA]=dde;

  SS[XI][X]=y_eta[n];
  SS[ETA][X]=y_xi[n];

  SS[XI][Y]=x_eta[n];
  SS[ETA][Y]=x_xi[n];

  for(mflag=0;mflag<2;mflag++){
    kx=0.5*(SS[mflag][X][rr]+SS[mflag][X][rr+ddd[mflag]])*Jaco;
    ky=0.5*(SS[mflag][Y][rr]+SS[mflag][Y][rr+ddd[mflag]])*Jaco;

    ZZ=kx*ux[n][rr]+ky*uy[n][rr];
    Sk=(sqrt(kx*kx+ky*ky));
    c=sqrt(gamma0*Cons_calcP(n, rr)/rho[n][rr]);
    tmp=Cons_calcP(n, rr)/rho[n][rr]/Rair; /*温度*/
    Mu=mu_0*(pow((tmp)/(273.15+20.0),1.5)*(273.15+20.0+C)/(tmp+C));
    spe[mflag]=ALPHA*(fabs(ZZ)+c*Sk)+2.0*(Mu+Mut[n][rr])*Sk*Sk/rho[n][rr];
  }
}

/* 新しい物理時間ステップの前に補正量と RHS 配列を初期化する。 */
void dQ_Initial(){
  int n,r0,i,j;

  for(n=0;n<NT;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0=dim[n](i,j);
	dQ[n][0][r0]=0.0;
	dQ[n][1][r0]=0.0;
	dQ[n][2][r0]=0.0;
	dQ[n][3][r0]=0.0;
	TurbdQ[n][0][r0]=0.0;
	TurbdQ[n][1][r0]=0.0;

	rhsF[n][0][r0]=0.0;
	rhsF[n][1][r0]=0.0;
	rhsF[n][2][r0]=0.0;
	rhsF[n][3][r0]=0.0;
	rhsTurbF[n][0][r0]=0.0;
	rhsTurbF[n][1][r0]=0.0;
      }
    }
  }

}

/* 流れ場と SST を連成して 1 ステップ進める。 */
void gauss_seidel(int time){
  int n,itr,ii,jj;
  double errormax;
  double error4;

  itr=0;

  dQ_Initial();

  for(itr=0;itr<t_NUMBER;itr++){

    /* 現在の場から流れ場と乱流量の流束を組み直す。 */
    fds();
    fds_komega();
    viscous();
    viscous_komega();

    ii=jj=0;
    errormax=0.0;

    for(n=0;n<NT;n++){
      int i,j,r0;

#ifdef _OPENMP
      omp_set_nested(1);
#pragma omp parallel num_threads(8)
      {
#endif

#pragma omp for private(i,j,r0)
	for(j=2;j<jt[n]-3;j++){
	  for(i=2;i<it[n]-3;i++){
	    double Jaco,invQ;
	    double RHSt[2];
	    double RHS0,RHS1,RHS2,RHS3,RHS4,RHS5;
	    double spe_r0[2];
	    double deltaFlux[2][6];
	    double rhs1[6];
	    double LDinv;
	    int XI=0;
	    int ETA=1;

	    r0=dim[n](i,j);

	    /* k-omega 方程式の生成・消散項は別に評価する。 */
	    calc_komega(n,r0,RHSt);

	    RHS0=-dt*((E[n][0][r0+dG[n]]    -E[n][0][r0]    )-(Ev[n][0][r0+dG[n]]    -Ev[n][0][r0]    )+(F[n][0][r0+dE[n]]    -F[n][0][r0]    )-(Fv[n][0][r0+dE[n]]    -Fv[n][0][r0]    ));
	    RHS1=-dt*((E[n][1][r0+dG[n]]    -E[n][1][r0]    )-(Ev[n][1][r0+dG[n]]    -Ev[n][1][r0]    )+(F[n][1][r0+dE[n]]    -F[n][1][r0]    )-(Fv[n][1][r0+dE[n]]    -Fv[n][1][r0]    ));
	    RHS2=-dt*((E[n][2][r0+dG[n]]    -E[n][2][r0]    )-(Ev[n][2][r0+dG[n]]    -Ev[n][2][r0]    )+(F[n][2][r0+dE[n]]    -F[n][2][r0]    )-(Fv[n][2][r0+dE[n]]    -Fv[n][2][r0]    ));
	    RHS3=-dt*((E[n][3][r0+dG[n]]    -E[n][3][r0]    )-(Ev[n][3][r0+dG[n]]    -Ev[n][3][r0]    )+(F[n][3][r0+dE[n]]    -F[n][3][r0]    )-(Fv[n][3][r0+dE[n]]    -Fv[n][3][r0]    ));
	    RHS4=-dt*((TurbE[n][0][r0+dG[n]]-TurbE[n][0][r0])-(TurbEv[n][0][r0+dG[n]]-TurbEv[n][0][r0])+(TurbF[n][0][r0+dE[n]]-TurbF[n][0][r0])-(TurbFv[n][0][r0+dE[n]]-TurbFv[n][0][r0])-RHSt[0]);
	    RHS5=-dt*((TurbE[n][1][r0+dG[n]]-TurbE[n][1][r0])-(TurbEv[n][1][r0+dG[n]]-TurbEv[n][1][r0])+(TurbF[n][1][r0+dE[n]]-TurbF[n][1][r0])-(TurbFv[n][1][r0+dE[n]]-TurbFv[n][1][r0])-RHSt[1]);

	    if(itr==0){
	      tmpEE[n][0][r0]=RHS0;
	      tmpEE[n][1][r0]=RHS1;
	      tmpEE[n][2][r0]=RHS2;
	      tmpEE[n][3][r0]=RHS3;
	      TurbtmpEE[n][0][r0]=RHS4;
	      TurbtmpEE[n][1][r0]=RHS5;
	    }

	    rhs1[0]=(tmpQ[n][0][r0]    -Q[n][0][r0]    )+0.5*(RHS0+tmpEE[n][0][r0]    );
	    rhs1[1]=(tmpQ[n][1][r0]    -Q[n][1][r0]    )+0.5*(RHS1+tmpEE[n][1][r0]    );
	    rhs1[2]=(tmpQ[n][2][r0]    -Q[n][2][r0]    )+0.5*(RHS2+tmpEE[n][2][r0]    );
	    rhs1[3]=(tmpQ[n][3][r0]    -Q[n][3][r0]    )+0.5*(RHS3+tmpEE[n][3][r0]    );
	    rhs1[4]=(TurbtmpQ[n][0][r0]-TurbQ[n][0][r0])+0.5*(RHS4+TurbtmpEE[n][0][r0]);
	    rhs1[5]=(TurbtmpQ[n][1][r0]-TurbQ[n][1][r0])+0.5*(RHS5+TurbtmpEE[n][1][r0]);

	    /* 前進 sweep では下三角側の隣接セル寄与を取り込む。 */
	    calcPM(r0,n,-1,dG[n],dE[n],dQ[n],TurbdQ[n],deltaFlux);

	    rhs1[0]+=lambda*dt*(deltaFlux[XI][0]+deltaFlux[ETA][0]);
	    rhs1[1]+=lambda*dt*(deltaFlux[XI][1]+deltaFlux[ETA][1]);
	    rhs1[2]+=lambda*dt*(deltaFlux[XI][2]+deltaFlux[ETA][2]);
	    rhs1[3]+=lambda*dt*(deltaFlux[XI][3]+deltaFlux[ETA][3]);
	    rhs1[4]+=lambda*dt*(deltaFlux[XI][4]+deltaFlux[ETA][4]);
	    rhs1[5]+=lambda*dt*(deltaFlux[XI][5]+deltaFlux[ETA][5]);

	    calcLx(r0,n,dG[n],dE[n],spe_r0);
	    LDinv=1.0/(1.0+lambda*dt*(spe_r0[0]+spe_r0[1]));

	    dQ[n][0][r0]    =rhs1[0]*LDinv;
	    dQ[n][1][r0]    =rhs1[1]*LDinv;
	    dQ[n][2][r0]    =rhs1[2]*LDinv;
	    dQ[n][3][r0]    =rhs1[3]*LDinv;
	    TurbdQ[n][0][r0]=rhs1[4]*LDinv;
	    TurbdQ[n][1][r0]=rhs1[5]*LDinv;
	  }
	}
#pragma omp for private(i,j,r0)
	for(j=jt[n]-4;j>1;j--){
	  for(i=it[n]-4;i>1;i--){
	    double Jaco,invQ;
	    double RHS0,RHS1,RHS2,RHS3;
	    double spe_r0[2];
	    double deltaFlux[2][6];
	    double rhs1[6];
	    double LDinv;
	    int XI=0;
	    int ETA=1;

	    r0=dim[n](i,j);

	    rhsF[n][0][r0]=dQ[n][0][r0];
	    rhsF[n][1][r0]=dQ[n][1][r0];
	    rhsF[n][2][r0]=dQ[n][2][r0];
	    rhsF[n][3][r0]=dQ[n][3][r0];
	    rhsTurbF[n][0][r0]=TurbdQ[n][0][r0];
	    rhsTurbF[n][1][r0]=TurbdQ[n][1][r0];

	    /* 後退 sweep では上三角側の隣接セル寄与を取り除く。 */
	    calcPM(r0,n,1,dG[n],dE[n],rhsF[n],rhsTurbF[n],deltaFlux);

	    rhs1[0]=lambda*dt*(deltaFlux[XI][0]+deltaFlux[ETA][0]);
	    rhs1[1]=lambda*dt*(deltaFlux[XI][1]+deltaFlux[ETA][1]);
	    rhs1[2]=lambda*dt*(deltaFlux[XI][2]+deltaFlux[ETA][2]);
	    rhs1[3]=lambda*dt*(deltaFlux[XI][3]+deltaFlux[ETA][3]);
	    rhs1[4]=lambda*dt*(deltaFlux[XI][4]+deltaFlux[ETA][4]);
	    rhs1[5]=lambda*dt*(deltaFlux[XI][5]+deltaFlux[ETA][5]);

	    calcLx(r0,n,dG[n],dE[n],spe_r0);
	    LDinv=1.0/(1.0+lambda*dt*(spe_r0[0]+spe_r0[1]));

	    rhsF[n][0][r0]    =dQ[n][0][r0]    -rhs1[0]*LDinv;
	    rhsF[n][1][r0]    =dQ[n][1][r0]    -rhs1[1]*LDinv;
	    rhsF[n][2][r0]    =dQ[n][2][r0]    -rhs1[2]*LDinv;
	    rhsF[n][3][r0]    =dQ[n][3][r0]    -rhs1[3]*LDinv;
	    rhsTurbF[n][0][r0]=TurbdQ[n][0][r0]-rhs1[4]*LDinv;
	    rhsTurbF[n][1][r0]=TurbdQ[n][1][r0]-rhs1[5]*LDinv;
	  }
	}
#pragma omp for private(i,j,r0)
	for(j=2;j<jt[n]-3;j++){
	  for(i=2;i<it[n]-3;i++){
	    double Jaco,invQ;
	    double RHS0,RHS1,RHS2,RHS3;
	    double LDinv;
	    double a1=0.31,omega_mut;
	    r0=dim[n](i,j);
	    Jaco=1.0/S[n][r0];

	    Q[n][0][r0]=Q[n][0][r0]+rhsF[n][0][r0];
	    Q[n][1][r0]=Q[n][1][r0]+rhsF[n][1][r0];
	    Q[n][2][r0]=Q[n][2][r0]+rhsF[n][2][r0];
	    Q[n][3][r0]=Q[n][3][r0]+rhsF[n][3][r0];
	    TurbQ[n][0][r0]=TurbQ[n][0][r0]+rhsTurbF[n][0][r0];
	    TurbQ[n][1][r0]=TurbQ[n][1][r0]+rhsTurbF[n][1][r0];

	    /* 更新後に基本変数と渦粘性係数を再計算する。 */
	    dQ[n][0][r0]    =rhsF[n][0][r0];
	    dQ[n][1][r0]    =rhsF[n][1][r0];
	    dQ[n][2][r0]    =rhsF[n][2][r0];
	    dQ[n][3][r0]    =rhsF[n][3][r0];
	    TurbdQ[n][0][r0]=rhsTurbF[n][0][r0];
	    TurbdQ[n][1][r0]=rhsTurbF[n][1][r0];

	    invQ=1.0/Q[n][0][r0]; /* =1.0/(rho*v) */

	    rho[n][r0]=Q[n][0][r0]*Jaco;
	    ux[n][r0] =Q[n][1][r0]*invQ;
	    uy[n][r0] =Q[n][2][r0]*invQ;
	    e[n][r0]  =Q[n][3][r0]*Jaco;

	    p[n][r0]=Cons_calcP(n,r0);

	    k_turb[n][r0]=TurbQ[n][0][r0]*invQ;

	    if(k_turb[n][r0]<1.0e-10){
	      k_turb[n][r0]=1.0e-10;
	    }

	    omega[n][r0]=TurbQ[n][1][r0]*invQ;
	    omega_mut=max2f(a1*omega[n][r0],calc_W(n,r0)*calc_F2(n,r0));
	    Mut[n][r0]=a1*rho[n][r0]*k_turb[n][r0]/omega_mut;

	    error4=dQ[n][3][r0]/Q[n][3][r0];

	    if(errormax<fabs(error4)){
	      errormax=fabs(error4);
	      ii=i;
	      jj=j;
	    }


	  }
	}
#ifdef _OPENMP
      }
#endif
    }

    /* 次の段へ進む前に境界値とブロック境界値を更新する。 */
    boundary();
      
    if(itr==(t_NUMBER-1)){
      printf("time:%d i:%d j*%d erormax:%e itr:%d\n",time,ii,jj,errormax,itr);
    }

  }
}     
