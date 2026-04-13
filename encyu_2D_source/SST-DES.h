/************************************

calculation for k-omega turburance model

 **********************************/

/* /\*----------------------------------------------------------*\/ */
/* /\*                        Y PLUS                            *\/ */
/* /\*----------------------------------------------------------*\/ */
/* void calcyp(){ */
/*   int i, j, count; */
/*   int r0, rc; */
/*   const double kappa = 0.42; */
/*   const double B = 5.5; */
/*   double twx, twy, rhow, ut, up, l; */
/*   double Mu, Muw, tw, dut; */
/*   double ut2; */
/*   double tmpT; */

/*   for(i=2;i<it-3;i++){ */
/*     for(j=2;j<jt-3;j++){ */
/*       r0 = dim(i, j); */
/*       rc = dim(clx[r0], cly[r0]); */

/*       rhow = rho[rc]; */
/*       tmpT = (Cons_calcP(rc) / (rhow * Rair)) / T_0;        /\** 壁面温度 **\/ */
/*       Muw = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0); */

/*       tmpT = (Cons_calcP(r0) / (rho[r0] * Rair)) / T_0; */
/*       Mu = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0); */

/*       l = 1.0 / d_wall[rc]; */

/*       twx = Muw * ux[rc] * l; */
/*       twy = Muw * uy[rc] * l; */
      
/*       tw = sqrt(twx * twx + twy * twy); */
/*       ut = sqrt(tw / rhow); */
/*       yp[r0] = ut * d_wall[r0] * rhow / Muw; */
/*       ut_buff[r0] = ut; */


/*       if(yp[rc] > 10){ */

/* 	up = sqrt(ux[rc] * ux[rc] + uy[rc] * uy[rc]); */

/* 	count = 0; */
/* 	/\* ut = 0.01; *\/ */
/* 	do{ */
/* 	  ut2 = ut; */
/* 	  ut = ut + (up - ut * (log(yp[rc]) / kappa + B)) / (up / ut + 1.0 / kappa); */
/* 	  dut = fabs(ut - ut2); */

/* 	  if(ut < 0.0){ */
/* 	    ut = 0.1 * fabs(ut); */
/* 	  } */

/* 	  yp[rc] = rhow * ut * d_wall[rc] / Muw; */

/* 	  /\* printf("[%d %d] %d  %e  %e\n", i, j, count, ut, yp[r0]); *\/ */


/* 	  count++; */

/* 	}while(dut > 1.0e-4 * ut2); */

/* 	yp[r0] = rhow * ut * d_wall[r0] / Muw; */
/* 	ut_buff[r0] = ut; */
/* 	/\* printf("%d %d %e %e\n",i,j,yp[r0],ut); *\/ */
      

/*       } */

/*     }  */
/*   } */
  
/* } */

/*----------------------------------------------------------*/
/*                 生成項Pを計算する                        */
/*----------------------------------------------------------*/
static double calc_komega_P(int n, int r0){
  double u_x, u_y;
  double v_x, v_y;
  double ux_e, ux_w, ux_n, ux_s;
  double uy_e, uy_w, uy_n, uy_s;
  int pG, mG, pE, mE;
  double PP, Sij;

  pG = r0 + dG[n];
  mG = r0 - dG[n];
  pE = r0 + dE[n];
  mE = r0 - dE[n];

  ux_e = 0.5 * (ux[n][pG] + ux[n][r0]);
  ux_w = 0.5 * (ux[n][mG] + ux[n][r0]);
  ux_n = 0.5 * (ux[n][pE] + ux[n][r0]);
  ux_s = 0.5 * (ux[n][mE] + ux[n][r0]);

  uy_e = 0.5 * (uy[n][pG] + uy[n][r0]);
  uy_w = 0.5 * (uy[n][mG] + uy[n][r0]);
  uy_n = 0.5 * (uy[n][pE] + uy[n][r0]);
  uy_s = 0.5 * (uy[n][mE] + uy[n][r0]);

  u_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (ux_e - ux_w) + (y_xi[n][pE] + y_xi[n][r0]) * (ux_n - ux_s)) / S[n][r0];
  v_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (uy_e - uy_w) + (y_xi[n][pE] + y_xi[n][r0]) * (uy_n - uy_s)) / S[n][r0];
  u_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (ux_e - ux_w) + (x_xi[n][pE] + x_xi[n][r0]) * (ux_n - ux_s)) / S[n][r0];
  v_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (uy_e - uy_w) + (x_xi[n][pE] + x_xi[n][r0]) * (uy_n - uy_s)) / S[n][r0];

  Sij = sqrt(2.0 * u_x * u_x + 2.0 * v_y * v_y + (u_y + v_x) * (u_y + v_x));

  PP = Mut[n][r0] * Sij * Sij;

  return PP;
}

/*----------------------------------------------------------*/
/*                 渦度の絶対値を計算する                   */
/*----------------------------------------------------------*/
static double calc_W(int n, int r0){
  double u_x, u_y;
  double v_x, v_y;
  double ux_e, ux_w, ux_n, ux_s;
  double uy_e, uy_w, uy_n, uy_s;
  int pG, mG, pE, mE;
  double W, Sij;

  pG = r0 + dG[n];
  mG = r0 - dG[n];
  pE = r0 + dE[n];
  mE = r0 - dE[n];

  ux_e = 0.5 * (ux[n][pG] + ux[n][r0]);
  ux_w = 0.5 * (ux[n][mG] + ux[n][r0]);
  ux_n = 0.5 * (ux[n][pE] + ux[n][r0]);
  ux_s = 0.5 * (ux[n][mE] + ux[n][r0]);

  uy_e = 0.5 * (uy[n][pG] + uy[n][r0]);
  uy_w = 0.5 * (uy[n][mG] + uy[n][r0]);
  uy_n = 0.5 * (uy[n][pE] + uy[n][r0]);
  uy_s = 0.5 * (uy[n][mE] + uy[n][r0]);

  v_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (uy_e - uy_w) + (y_xi[n][pE] + y_xi[n][r0]) * (uy_n - uy_s)) / S[n][r0];
  u_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (ux_e - ux_w) + (x_xi[n][pE] + x_xi[n][r0]) * (ux_n - ux_s)) / S[n][r0];

  W = sqrt((u_y - v_x) * (u_y - v_x));

  return W;
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


/*----------------------------------------------------------*/
/*             kとomegaのデターミナントを計算               */
/*----------------------------------------------------------*/
static double calc_derukw(int n, int r0){
  double k_x, k_y;
  double omega_x, omega_y;
  double k_e, k_w, k_n, k_s;
  double omega_e, omega_w, omega_n, omega_s;
  int pG, mG, pE, mE;
  double KW;

  pG = r0 + dG[n];
  mG = r0 - dG[n];
  pE = r0 + dE[n];
  mE = r0 - dE[n];

  k_e = 0.5 * (k_turb[n][pG] + k_turb[n][r0]);
  k_w = 0.5 * (k_turb[n][mG] + k_turb[n][r0]);
  k_n = 0.5 * (k_turb[n][pE] + k_turb[n][r0]);
  k_s = 0.5 * (k_turb[n][mE] + k_turb[n][r0]);

  omega_e = 0.5 * (omega[n][pG] + omega[n][r0]);
  omega_w = 0.5 * (omega[n][mG] + omega[n][r0]);
  omega_n = 0.5 * (omega[n][pE] + omega[n][r0]);
  omega_s = 0.5 * (omega[n][mE] + omega[n][r0]);

  k_x     = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (k_e - k_w)         + (y_xi[n][pE] + y_xi[n][r0]) * (k_n - k_s)) / S[n][r0];
  omega_x = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (omega_e - omega_w) + (y_xi[n][pE] + y_xi[n][r0]) * (omega_n - omega_s)) / S[n][r0];
  k_y     = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (k_e - k_w)         + (x_xi[n][pE] + x_xi[n][r0]) * (k_n - k_s)) / S[n][r0];
  omega_y = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (omega_e - omega_w) + (x_xi[n][pE] + x_xi[n][r0]) * (omega_n - omega_s)) / S[n][r0];

  KW = (k_x + k_y) * (omega_x + omega_y);

  return KW;
}


/*----------------------------------------------------------*/
/*                     関数F1を計算                         */
/*----------------------------------------------------------*/
static double calc_F1(int n, int r0){
  double beta = 0.09;
  double tmpT, Mu, F1;
  double siguma_w2 = 0.856;
  double ans1, ans2, ans3, ans4, CDkw;

  tmpT = (Cons_calcP(n, r0) / (rho[n][r0] * Rair)) / T_0;
  Mu = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0);

  CDkw = max2f(2.0 * rho[n][r0] * siguma_w2 * calc_derukw(n, r0) / omega[n][r0], 1.0e-20);

  ans1 = sqrt(k_turb[n][r0]) / (beta * omega[n][r0] * d_wall[n][r0]);
  ans2 = 500 * Mu / (rho[n][r0] * omega[n][r0] * pow(d_wall[n][r0], 2.0));
  ans3 = max2f(ans1, ans2);
  ans4 = 4.0 * siguma_w2 * k_turb[n][r0] / (CDkw * pow(d_wall[n][r0], 2.0));

  F1 = tanh(min2f(ans3, ans4));

  return F1;
}

/*----------------------------------------------------------*/
/*                      関数F2を計算                        */
/*----------------------------------------------------------*/
static double calc_F2(int n, int r0){
  double beta = 0.09;
  double tmpT, Mu, F2;
  double ans1, ans2;

  tmpT = (Cons_calcP(n, r0) / (rho[n][r0] * Rair)) / T_0;
  Mu = mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0);

  ans1 = 2.0 * sqrt(k_turb[n][r0]) / (beta * omega[n][r0] * d_wall[n][r0]);
  ans2 = 500 * Mu / (rho[n][r0] * omega[n][r0] * pow(d_wall[n][r0], 2.0));

  F2 = tanh(pow(max2f(ans1, ans2) ,4.0));

  return F2;
}

/*----------------------------------------------------------*/
/*                        mix関数                           */
/*----------------------------------------------------------*/
static double calc_mix(int n, int r0, double var1, double var2){
  double F1;

  F1 = calc_F1(n, r0);

  return var1 * F1 + var2 * (1.0 - F1);
}

/*----------------------------------------------------------*/
/*                 長さスケールl_kwを計算する               */
/*----------------------------------------------------------*/
inline double calc_lkw(int n, int r0, double beta_star){
  return sqrt(k_turb[n][r0]) / (beta_star * omega[n][r0]);
}


/*----------------------------------------------------------*/
/*                 生成項全体を計算する                     */
/*----------------------------------------------------------*/
void calc_komega(int n, int r0, double *RHSt){
  double PP, EE, D;
  const double beta_star = 0.09;
  const double beta_1 = 0.075;
  const double beta_2 = 0.0828;
  const double alpha_1 = 5.0 / 9.0;
  const double alpha_2 = 0.44;
  double siguma_w2 = 0.856;
  double alpha, beta, l_kw, deruta, l_DES, C_DES, fd, deruta_cor;

  alpha = calc_mix(n, r0, alpha_1, alpha_2);
  beta  = calc_mix(n, r0, beta_1, beta_2);
  C_DES = calc_mix(n, r0, C_DES_kome, C_DES_kepu);

  l_kw = calc_lkw(n, r0, beta_star);
  lkw[n][r0] = l_kw;

#ifdef DDES
  deruta = max2f(deruta_x[n][r0], deruta_y[n][r0]);
  fd = 1.0 - tanh(pow(1.5 * l_kw / d_wall[n][r0], 3.0));
  deruta_cor = l_kw - fd * (l_kw - deruta);
  l_DES  = min2f(l_kw, C_DES * deruta_cor);
#endif

#ifdef DES
  deruta = max2f(deruta_x[n][r0], deruta_y[n][r0]);
  l_DES  = min2f(l_kw, C_DES * deruta);
#endif


#ifdef RANS
  l_DES = l_kw;
#endif

  if(l_kw > l_DES){
    RA_LE[n][r0] = 0.0;        //LES
  }
  else{
    RA_LE[n][r0] = 1.0;        //RANS
  }

  PP = calc_komega_P(n, r0);
  D  = rho[n][r0] * pow(k_turb[n][r0], 1.5) / l_DES;
  EE = beta * rho[n][r0] * pow(omega[n][r0], 2.0);

  RHSt[0] = (PP - D) * S[n][r0];
  RHSt[1] = (alpha * rho[n][r0] * PP / Mut[n][r0] - EE + 2.0 * (1.0 - calc_F1(n, r0)) * rho[n][r0] * siguma_w2 * calc_derukw(n, r0) / omega[n][r0]) * S[n][r0];

}

/*----------------------------------------------------------*/
/*                 k-omega initialize                       */
/*----------------------------------------------------------*/
void komega_ini(){
  int i, j, r0, n;
  double beta_1 = 0.075;
  double Mu, tmpT;
  double w_vis, w_log;
  double epsilon;

  for(n=0;n<NT;n++){
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
	r0 = dim[n](i, j);

	k_turb[n][r0] = 1.0e-7 * u0 * u0 * 0.1;
	omega[n][r0] = u0 * 150 * 0.1;
	Mut[n][r0] = k_turb[n][r0] * rho[n][r0] / omega[n][r0];;


	/* epsilon = calc_komega_P(r0) / rho[r0]; */

	/* k_turb[n][r0] = sqrt(Mut[n][r0] * epsilon / (0.09 * rho[r0])); */
	/* omega[n][r0]  = sqrt(epsilon * rho[r0] / (0.09 * Mut[n][r0])); */

	/* printf("%d %d %e %e %e\n",i,j,Mut[n][r0],k_turb[n][r0],omega[n][r0]); */

      }
    }
  }

  for(n=0;n<NT;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	TurbQ[n][0][r0] = rho[n][r0] * k_turb[n][r0] * S[n][r0];
	TurbQ[n][1][r0] = rho[n][r0] * omega[n][r0] * S[n][r0];
      }
    }
  }


}
