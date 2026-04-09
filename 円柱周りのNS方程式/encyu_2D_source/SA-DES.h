/************************************

calculation for SA turburance model

 **********************************/


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


static double calc_F_v1(int n, int r0){
  double Nu, tmpT, XXX, F_v1;
  const double c_v1 = 7.1;

  tmpT = Cons_calcP(n, r0) / (rho[n][r0] * Rair) / T_0;
  Nu = (mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0)) / rho[n][r0];

  XXX = NuSA[n][r0] / Nu;

  F_v1 = pow(XXX , 3.0) / (pow(XXX , 3.0) + pow(c_v1 , 3.0));

  return F_v1;
}


/*----------------------------------------------------------*/
/*                 生成項Pを計算する                        */
/*----------------------------------------------------------*/
static double calc_SA_P_Destruction(int n, int r0){
  const double kuppa = 0.41;
  const double c_b1 = 0.13455;
  const double c_b2 = 0.622;
  const double c_w2 = 0.3;
  const double c_w3 = 2.0;
  const double c_t3 = 1.1;
  const double c_t4 = 2.0;
  const double c_v1 = 7.1;
  const double C_DES = 0.65;
  const double siguma_reverse = 1.5;
  double u_x, u_y;
  double v_x, v_y;
  double ux_e, ux_w, ux_n, ux_s;
  double uy_e, uy_w, uy_n, uy_s;
  int pG, mG, pE, mE;
  double PP, Sij, f_t2, S_hat, Nu, tmpT, XXX, f_v2, f_v1;
  double Des, c_w1, f_w, GG, rrr, ddd, P_Des;

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


  tmpT = Cons_calcP(n, r0) / (rho[n][r0] * Rair) / T_0;
  Nu = (mu_0 * tmpT * sqrt(tmpT) * (1.0 + C / T_0) / (tmpT + C / T_0)) / rho[n][r0];

  XXX = NuSA[n][r0] / Nu;

#ifdef DES
  deruta = max2f(deruta_x[n][r0], deruta_y[n][r0]);
  ddd  = min2f(d_wall[n][r0], C_DES * deruta);
#endif


#ifdef RANS
  ddd = d_wall[n][r0];
#endif

  if(d_wall[n][r0] > ddd){
    RA_LE[n][r0] = 0.0;        //LES
  }
  else{
    RA_LE[n][r0] = 1.0;        //RANS
  }


  Sij  = sqrt((u_y - v_x) * (u_y - v_x)); //vorticity magnitude
  f_t2 = c_t3 * exp(-1.0 * c_t4 * XXX * XXX);
  f_v1 = pow(XXX , 3.0) / (pow(XXX , 3.0) + pow(c_v1 , 3.0));
  f_v2 = 1.0 - XXX / (1.0 + XXX * f_v1);
  S_hat = Sij + NuSA[n][r0] * f_v2 / (kuppa * kuppa * ddd * ddd);

  PP = c_b1 * (1.0 - f_t2) * NuSA[n][r0] * S_hat;


  c_w1 = c_b1 / (kuppa * kuppa) + siguma_reverse * (1.0 + c_b2);

  rrr = NuSA[n][r0] / (S_hat * kuppa * kuppa * ddd * ddd);
  GG = rrr + c_w2 * (pow(rrr, 6.0) - rrr);
  f_w = GG * pow((1.0 + pow(c_w3, 6.0)) / (pow(GG, 6.0) + pow(c_w3, 6.0)), 1.0 / 6.0);

  Des = -1.0 * (c_w1 * f_w - c_b1 * f_t2 / (kuppa * kuppa)) * pow(NuSA[n][r0] / ddd, 2.0);

  P_Des = PP + Des;

  return P_Des;
}



/*----------------------------------------------------------*/
/*             kとomegaのデターミナントを計算               */
/*----------------------------------------------------------*/
static double calc_Deffusion(int n, int r0){
  const double c_b2 = 0.622;
  const double siguma_reverse = 1.5;
  double NuSA_x, NuSA_y;
  double NuSA_e, NuSA_w, NuSA_n, NuSA_s;
  int pG, mG, pE, mE;
  double KW;

  pG = r0 + dG[n];
  mG = r0 - dG[n];
  pE = r0 + dE[n];
  mE = r0 - dE[n];

  NuSA_e = 0.5 * (NuSA[n][pG] + NuSA[n][r0]);
  NuSA_w = 0.5 * (NuSA[n][mG] + NuSA[n][r0]);
  NuSA_n = 0.5 * (NuSA[n][pE] + NuSA[n][r0]);
  NuSA_s = 0.5 * (NuSA[n][mE] + NuSA[n][r0]);

  NuSA_x     = 0.5 * ((y_eta[n][pG] + y_eta[n][r0]) * (NuSA_e - NuSA_w)         + (y_xi[n][pE] + y_xi[n][r0]) * (NuSA_n - NuSA_s)) / S[n][r0];
  NuSA_y     = 0.5 * ((x_eta[n][pG] + x_eta[n][r0]) * (NuSA_e - NuSA_w)         + (x_xi[n][pE] + x_xi[n][r0]) * (NuSA_n - NuSA_s)) / S[n][r0];

  KW = siguma_reverse * c_b2 * (NuSA_x + NuSA_y) * (NuSA_x + NuSA_y);

  return KW;
}




/*----------------------------------------------------------*/
/*                 生成項全体を計算する                     */
/*----------------------------------------------------------*/
void calc_SA(int n, int r0, double *RHSt){
  double PP, D;

  PP = calc_SA_P_Destruction(n, r0);
  D = calc_Deffusion(n, r0);

  RHSt[0] = (PP + D) * S[n][r0];
}

/*----------------------------------------------------------*/
/*                 k-omega initialize                       */
/*----------------------------------------------------------*/
void SA_ini(){
  int i, j, r0, n;
  double beta_1 = 0.075;
  double Mu, tmpT;
  double w_vis, w_log;
  double epsilon;

  printf("-------------------DES VALID------------------------\n");

  for(n=0;n<NT;n++){
    for(j=2;j<jt[n]-2;j++){
      for(i=2;i<it[n]-2;i++){
	r0 = dim[n](i, j);

	NuSA[n][r0] = mu_0 / rho[n][r0];

      }
    }
  }

  for(n=0;n<NT;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	TurbQ[n][0][r0] = NuSA[n][r0] * S[n][r0];
      }
    }
  }


}
