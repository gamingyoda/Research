/*--------------------------

  ルンゲ=クッタ陽解法
  4-order 2d

------------------------------*/
void RungeKutta(){
  int t, i, j, r0, a;
  double Jaco, invQ, RHSt[2], f_mu;

  for(t=1;t<5;t++){

    fds();
    viscous();

    fds_komega();
    viscous_komega();

    calcyp();

    if(t%4 == 1){
      for(j=2;j<jt-3;j++){
	for(i=2;i<it-3;i++){
	  a = 1.0 / 3.0;
	  r0 = dim(i, j);
	  Jaco = 1.0 / S[r0];

	  calc_komega(r0, RHSt);

	  /* printf("%d %d %e %e\n",i,j,yp[r0],d_wall[r0]); */
	  /* printf("%d %d %e %e %e %e\n",i,j,k_turb[r0],omega[r0],Mut[r0],yp[r0]); */


	  Q[0][r0] = tmpQ[0][r0] - a * dt * ((E[0][r0+dG] - E[0][r0]) - (Ev[0][r0+dG] - Ev[0][r0]) + (F[0][r0+dE] - F[0][r0]) - (Fv[0][r0+dE] - Fv[0][r0]));
	  Q[1][r0] = tmpQ[1][r0] - a * dt * ((E[1][r0+dG] - E[1][r0]) - (Ev[1][r0+dG] - Ev[1][r0]) + (F[1][r0+dE] - F[1][r0]) - (Fv[1][r0+dE] - Fv[1][r0]));
	  Q[2][r0] = tmpQ[2][r0] - a * dt * ((E[2][r0+dG] - E[2][r0]) - (Ev[2][r0+dG] - Ev[2][r0]) + (F[2][r0+dE] - F[2][r0]) - (Fv[2][r0+dE] - Fv[2][r0]));
	  Q[3][r0] = tmpQ[3][r0] - a * dt * ((E[3][r0+dG] - E[3][r0]) - (Ev[3][r0+dG] - Ev[3][r0]) + (F[3][r0+dE] - F[3][r0]) - (Fv[3][r0+dE] - Fv[3][r0]));

	  TurbQ[0][r0] = TurbtmpQ[0][r0] - a * dt * ((TurbE[0][r0+dG] - TurbE[0][r0]) - (TurbEv[0][r0+dG] - TurbEv[0][r0]) + (TurbF[0][r0+dE] - TurbF[0][r0]) - (TurbFv[0][r0+dE] - TurbFv[0][r0]) - RHSt[0]);
	  TurbQ[1][r0] = TurbtmpQ[1][r0] - a * dt * ((TurbE[1][r0+dG] - TurbE[1][r0]) - (TurbEv[1][r0+dG] - TurbEv[1][r0]) + (TurbF[1][r0+dE] - TurbF[1][r0]) - (TurbFv[1][r0+dE] - TurbFv[1][r0]) - RHSt[1]);

	  invQ = 1.0 / Q[0][r0];  /* = 1.0/(rho*S) */
	  
	  rho[r0] = Q[0][r0] * Jaco;      /*        ^         */
	  ux[r0]  = Q[1][r0] * invQ;      /* Q とは Q のこと。*/
	  uy[r0]  = Q[2][r0] * invQ;
	  e[r0]   = Q[3][r0] * Jaco;
	  
	  p[r0] = Cons_calcP(r0);

	  k_turb[r0] = TurbQ[0][r0] * invQ;
	  omega[r0]  = TurbQ[1][r0] * invQ;
	  Mut[r0] = rho[r0] * k_turb[r0] / omega[r0];


	}
      }
    }
    else if(t%4 == 2){
      for(j=2;j<jt-3;j++){
	for(i=2;i<it-3;i++){
	  a = 4.0 / 15.0;
	  r0 = dim(i, j);
	  Jaco = 1.0 / S[r0];

	  calc_komega(r0, RHSt);

	  Q[0][r0] = tmpQ[0][r0] - a * dt * ((E[0][r0+dG] - E[0][r0]) - (Ev[0][r0+dG] - Ev[0][r0]) + (F[0][r0+dE] - F[0][r0]) - (Fv[0][r0+dE] - Fv[0][r0]));
	  Q[1][r0] = tmpQ[1][r0] - a * dt * ((E[1][r0+dG] - E[1][r0]) - (Ev[1][r0+dG] - Ev[1][r0]) + (F[1][r0+dE] - F[1][r0]) - (Fv[1][r0+dE] - Fv[1][r0]));
	  Q[2][r0] = tmpQ[2][r0] - a * dt * ((E[2][r0+dG] - E[2][r0]) - (Ev[2][r0+dG] - Ev[2][r0]) + (F[2][r0+dE] - F[2][r0]) - (Fv[2][r0+dE] - Fv[2][r0]));
	  Q[3][r0] = tmpQ[3][r0] - a * dt * ((E[3][r0+dG] - E[3][r0]) - (Ev[3][r0+dG] - Ev[3][r0]) + (F[3][r0+dE] - F[3][r0]) - (Fv[3][r0+dE] - Fv[3][r0]));

	  TurbQ[0][r0] = TurbtmpQ[0][r0] - a * dt * ((TurbE[0][r0+dG] - TurbE[0][r0]) - (TurbEv[0][r0+dG] - TurbEv[0][r0]) + (TurbF[0][r0+dE] - TurbF[0][r0]) - (TurbFv[0][r0+dE] - TurbFv[0][r0]) - RHSt[0]);
	  TurbQ[1][r0] = TurbtmpQ[1][r0] - a * dt * ((TurbE[1][r0+dG] - TurbE[1][r0]) - (TurbEv[1][r0+dG] - TurbEv[1][r0]) + (TurbF[1][r0+dE] - TurbF[1][r0]) - (TurbFv[1][r0+dE] - TurbFv[1][r0]) - RHSt[1]);



	  invQ = 1.0 / Q[0][r0];  /* = 1.0/(rho*S) */
	  
	  rho[r0] = Q[0][r0] * Jaco;      /*        ^         */
	  ux[r0]  = Q[1][r0] * invQ;      /* Q とは Q のこと。*/
	  uy[r0]  = Q[2][r0] * invQ;
	  e[r0]   = Q[3][r0] * Jaco;
	  
	  p[r0] = Cons_calcP(r0);

	  k_turb[r0] = TurbQ[0][r0] * invQ;
	  omega[r0] = TurbQ[1][r0] * invQ;
	  Mut[r0] = rho[r0] * k_turb[r0] / omega[r0];



	}
      }
    }
    else if(t%4 == 3){
      for(j=2;j<jt-3;j++){
	for(i=2;i<it-3;i++){
	  a = 5.0 / 9.0;
	  r0 = dim(i, j);
	  Jaco = 1.0 / S[r0];

	  calc_komega(r0, RHSt);

	  Q[0][r0] = tmpQ[0][r0] - a * dt * ((E[0][r0+dG] - E[0][r0]) - (Ev[0][r0+dG] - Ev[0][r0]) + (F[0][r0+dE] - F[0][r0]) - (Fv[0][r0+dE] - Fv[0][r0]));
	  Q[1][r0] = tmpQ[1][r0] - a * dt * ((E[1][r0+dG] - E[1][r0]) - (Ev[1][r0+dG] - Ev[1][r0]) + (F[1][r0+dE] - F[1][r0]) - (Fv[1][r0+dE] - Fv[1][r0]));
	  Q[2][r0] = tmpQ[2][r0] - a * dt * ((E[2][r0+dG] - E[2][r0]) - (Ev[2][r0+dG] - Ev[2][r0]) + (F[2][r0+dE] - F[2][r0]) - (Fv[2][r0+dE] - Fv[2][r0]));
	  Q[3][r0] = tmpQ[3][r0] - a * dt * ((E[3][r0+dG] - E[3][r0]) - (Ev[3][r0+dG] - Ev[3][r0]) + (F[3][r0+dE] - F[3][r0]) - (Fv[3][r0+dE] - Fv[3][r0]));

	  TurbQ[0][r0] = TurbtmpQ[0][r0] - a * dt * ((TurbE[0][r0+dG] - TurbE[0][r0]) - (TurbEv[0][r0+dG] - TurbEv[0][r0]) + (TurbF[0][r0+dE] - TurbF[0][r0]) - (TurbFv[0][r0+dE] - TurbFv[0][r0]) - RHSt[0]);
	  TurbQ[1][r0] = TurbtmpQ[1][r0] - a * dt * ((TurbE[1][r0+dG] - TurbE[1][r0]) - (TurbEv[1][r0+dG] - TurbEv[1][r0]) + (TurbF[1][r0+dE] - TurbF[1][r0]) - (TurbFv[1][r0+dE] - TurbFv[1][r0]) - RHSt[1]);


	  invQ = 1.0 / Q[0][r0];  /* = 1.0/(rho*S) */
	  
	  rho[r0] = Q[0][r0] * Jaco;      /*        ^         */
	  ux[r0]  = Q[1][r0] * invQ;      /* Q とは Q のこと。*/
	  uy[r0]  = Q[2][r0] * invQ;
	  e[r0]   = Q[3][r0] * Jaco;
	  
	  p[r0] = Cons_calcP(r0);

	  k_turb[r0] = TurbQ[0][r0] * invQ;
	  omega[r0] = TurbQ[1][r0] * invQ;
	  Mut[r0] = rho[r0] * k_turb[r0] / omega[r0];


	}
      }
    }
    else if(t%4 == 0){
      for(j=2;j<jt-3;j++){
	for(i=2;i<it-3;i++){
	  a = 1.0;
	  r0 = dim(i, j);
	  Jaco = 1.0 / S[r0];

	  calc_komega(r0, RHSt);

	  Q[0][r0] = tmpQ[0][r0] - a * dt * ((E[0][r0+dG] - E[0][r0]) - (Ev[0][r0+dG] - Ev[0][r0]) + (F[0][r0+dE] - F[0][r0]) - (Fv[0][r0+dE] - Fv[0][r0]));
	  Q[1][r0] = tmpQ[1][r0] - a * dt * ((E[1][r0+dG] - E[1][r0]) - (Ev[1][r0+dG] - Ev[1][r0]) + (F[1][r0+dE] - F[1][r0]) - (Fv[1][r0+dE] - Fv[1][r0]));
	  Q[2][r0] = tmpQ[2][r0] - a * dt * ((E[2][r0+dG] - E[2][r0]) - (Ev[2][r0+dG] - Ev[2][r0]) + (F[2][r0+dE] - F[2][r0]) - (Fv[2][r0+dE] - Fv[2][r0]));
	  Q[3][r0] = tmpQ[3][r0] - a * dt * ((E[3][r0+dG] - E[3][r0]) - (Ev[3][r0+dG] - Ev[3][r0]) + (F[3][r0+dE] - F[3][r0]) - (Fv[3][r0+dE] - Fv[3][r0]));

	  TurbQ[0][r0] = TurbtmpQ[0][r0] - a * dt * ((TurbE[0][r0+dG] - TurbE[0][r0]) - (TurbEv[0][r0+dG] - TurbEv[0][r0]) + (TurbF[0][r0+dE] - TurbF[0][r0]) - (TurbFv[0][r0+dE] - TurbFv[0][r0]) - RHSt[0]);
	  TurbQ[1][r0] = TurbtmpQ[1][r0] - a * dt * ((TurbE[1][r0+dG] - TurbE[1][r0]) - (TurbEv[1][r0+dG] - TurbEv[1][r0]) + (TurbF[1][r0+dE] - TurbF[1][r0]) - (TurbFv[1][r0+dE] - TurbFv[1][r0]) - RHSt[1]);


	  invQ = 1.0 / Q[0][r0];  /* = 1.0/(rho*S) */
	  
	  rho[r0] = Q[0][r0] * Jaco;      /*        ^         */
	  ux[r0]  = Q[1][r0] * invQ;      /* Q とは Q のこと。*/
	  uy[r0]  = Q[2][r0] * invQ;
	  e[r0]   = Q[3][r0] * Jaco;
	  
	  p[r0] = Cons_calcP(r0);

	  k_turb[r0] = TurbQ[0][r0] * invQ;
	  omega[r0] = TurbQ[1][r0] * invQ;
	  Mut[r0] = rho[r0] * k_turb[r0] / omega[r0];

	}
      }
    }

    boundary();
    komega_boundary();

  }

}
