/*-------------------------

  初期化関数 2d

---------------------------*/

void Initial(){
  int i, j, r0, n;
  double Re, nu, dX, ymin;
  double p_0, sita, rho_0, S_, T;
  double r, vr, vsita;
  double k1, k2;

  Re = (rho0 * u0 * 2.0 * RR) / mu_0;
  dX = sqrt((cen_x[0][3] - cen_x[0][2]) * (cen_x[0][3] - cen_x[0][2]) + (cen_y[0][3] - cen_y[0][2]) * (cen_y[0][3] - cen_y[0][2]));
  nu = sqrt(gamma0 * p0 / rho0) * dt / dX;
  ymin = 0.1 / sqrt(Re);
  /* 設定確認用に代表的な流れ場・格子スケールを表示する。 */
  printf("Re = %e\n",Re);
  printf("nu = %e\n",nu);
  printf("最小格子幅dr = %e\n",dX);
  printf("必要な最小格子幅(層流)ymin = %e\n",ymin);

  /* 初期値には円柱まわりのポテンシャル流れを用いる。 */
  for(n=0;n<NT;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	r     = pow(cen_x[n][r0] ,2.0) + pow(cen_y[n][r0] ,2.0);
	sita  = atan2(cen_y[n][r0],cen_x[n][r0]);
	vr    = u0 * cos(sita) * (1.0 - RR * RR / r);
	vsita = u0 * sin(sita) * (1.0 + RR * RR / r);
	/* S_ = p_0 / (pow(rho_0, gamma0)); */
	/* T  = p_0 / rho_0 - 0.5 * (gamma0 - 1.0) * (vr * vr + vsita * vsita) / gamma0;      //ベルヌーイの定理 */
	/* rho[r0] = pow(T/S_, k1); */
	/* p[r0] = pow(T, k2) / pow(S_, k1); */

	rho[n][r0] = rho0;
	p[n][r0] = p0 + 0.5 * rho0 * u0 * u0 - 0.5 * rho0 * (vr * vr + vsita * vsita);
	/* 極座標の速度をデカルト座標系へ変換する。 */
	ux[n][r0]  = (vr * cos(sita) + vsita * sin(sita));
	uy[n][r0]  = (vr * sin(sita) - vsita * cos(sita));
	e[n][r0]   = Cons_calcE(n, r0);

      }
    }
  }
  /*************保存量の計算************************/
  for(n=0;n<NT;n++){
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	/* 基本変数をセル積分形の保存変数へ変換する。 */
	Q[n][0][r0] = rho[n][r0] * S[n][r0];
	Q[n][1][r0] = rho[n][r0] * ux[n][r0] * S[n][r0];
	Q[n][2][r0] = rho[n][r0] * uy[n][r0] * S[n][r0];
	Q[n][3][r0] = e[n][r0] * S[n][r0];
      }
    }
  }

}
