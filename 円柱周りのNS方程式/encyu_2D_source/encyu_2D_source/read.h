/*******************************/
/*       メモリ読み込み        */
/*       格子読み込み          */
/*******************************/

/* 各ブロックは 2 次元格子を 1 次元配列に展開して保持する。 */
unsigned int dimIN(int i,int j){
  return i + j*it[0]; 
}
unsigned int dimWAKE(int i,int j){
  return i + j*it[1]; 
}
unsigned int dimOUT(int i,int j){
  return i + j*it[2]; 
}



/*----------メモリ確保関数-------------*/
/* メモリ確保に失敗したら、その場で終了するためのラッパ。 */
void *ealloc(size_t size){
  void *p;

  p = malloc(size);
  if(NULL == p){
    perror("");
    exit(1);
  }

  return p;
}

/* ブロック 1 個分の double 配列を確保する。 */
void *memory(int n){
  void *p;
  p = ealloc(sizeof(double)*(it[n])*(jt[n]));
  return p;
}

/* ブロック 1 個分の int 配列を確保する。 */
void *memory_int(int n){
  void *p;
  p = ealloc(sizeof(int)*(it[n])*(jt[n]));
  return p;
}


/* 格子ファイルを読み込み、計算で使う全配列を確保する。 */
void read(){
  int i, j, ij, n, r0, kk;
  char fn[50];
  FILE *fpw;

  sprintf(fn,"./grid/grid_data");

  fpw = fopen(fn, "r");
  if(NULL == fpw){
    perror(fn);
    exit(1);
  }

  dim[0]=dimIN;
  dim[1]=dimWAKE;
  dim[2]=dimOUT;

  for(n=0;n<NT;n++){
    fscanf(fpw,"%d %d\n",&it[n], &jt[n]);

    /* 1 次元配列化したときの隣接セルへのオフセット。 */
    dG[n] = 1;
    dE[n] = it[n];

    printf("n:%d it:%d jt:%d Sij:%d\n",n,it[n],jt[n],it[n] * jt[n]);

    /* セル中心の計算は 0..it-2, 0..jt-2 を使うが、
       境界処理や隣接参照を簡単にするため配列は全体サイズで確保する。 */
    x_xi[n]   = memory(n);
    y_xi[n]   = memory(n);
    x_eta[n]  = memory(n);
    y_eta[n]  = memory(n);
    x_xi_cen[n]   = memory(n);
    y_xi_cen[n]   = memory(n);
    x_eta_cen[n]  = memory(n);
    y_eta_cen[n]  = memory(n);
    S[n]      = memory(n);
    x[n]      = memory(n);
    y[n]      = memory(n);
    cen_x[n]  = memory(n);
    cen_y[n]  = memory(n);
    rho[n]    = memory(n);
    ux[n]     = memory(n);
    uy[n]     = memory(n);
    p[n]      = memory(n);
    e[n]      = memory(n);
    d_wall[n] = memory(n);
    yp[n]     = memory(n);
    Mut[n]    = memory(n);
    NuSA[n]    = memory(n);
    k_turb[n] = memory(n);
    omega[n]  = memory(n);
    clx[n]    = memory_int(n);
    cly[n]    = memory_int(n);
    ut_buff[n] = memory(n);
    deruta_x[n] = memory(n);
    deruta_y[n] = memory(n);
    RA_LE[n] = memory(n);
    lkw[n]   = memory(n);

    for(ij=0;ij<4;ij++){
      Q[n][ij]     = memory(n);
      tmpQ[n][ij]  = memory(n);
      E[n][ij]     = memory(n);
      F[n][ij]     = memory(n);
      Ev[n][ij]    = memory(n);
      Fv[n][ij]    = memory(n);
      tmpEE[n][ij] = memory(n);
      dQ[n][ij]    = memory(n);
      rhsF[n][ij]  = memory(n);
    }

    for(ij=0;ij<6;ij++){
      Ecen[n][ij]     = memory(n);
      Fcen[n][ij]     = memory(n);

      for(kk=0;kk<2;kk++){
	Qch[n][ij][kk]    = memory(n);
	Qchcv[n][ij][kk]  = memory(n);
      }
    }

    for(ij=0;ij<2;ij++){
      for(kk=0;kk<2;kk++){
	TurbQchcv[n][ij][kk]  = memory(n);
      }
    }


    for(ij=0;ij<2;ij++){
      vis_S[n][ij] = memory(n);
      duxd[n][ij]  = memory(n);
      duyd[n][ij]  = memory(n);
      dcptd[n][ij] = memory(n);
      TurbE[n][ij] = memory(n);
      TurbF[n][ij] = memory(n);
      TurbEv[n][ij] = memory(n);
      TurbFv[n][ij] = memory(n);
      TurbQ[n][ij]   = memory(n);
      TurbtmpQ[n][ij] = memory(n);
      TurbtmpEE[n][ij] = memory(n);
      TurbdQ[n][ij]   = memory(n);
      rhsTurbF[n][ij]   = memory(n);
    }
    /* 各ブロックのファイル並び順:
       1. セル中心座標
       2. 面メトリクスとセル面積
       3. セル中心メトリクス
       4. 壁面からの距離
       5. DES 用のフィルタ幅 */
    /*************** [ write cell-center grid data ] *******************/
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);      
	fscanf(fpw,"%lf %lf\n",&cen_x[n][r0], &cen_y[n][r0]);
      }
    }

    /*************** [ write metrics and area data ] *******************/
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);      
	fscanf(fpw,"%lf %lf %lf %lf %lf\n",&x_xi[n][r0], &y_xi[n][r0], &x_eta[n][r0], &y_eta[n][r0], &S[n][r0]);
      }
    }

    /*************** [ write metrics (cell-center) ] *******************/
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);      
	fscanf(fpw,"%lf %lf %lf %lf\n",&x_xi_cen[n][r0], &y_xi_cen[n][r0], &x_eta_cen[n][r0], &y_eta_cen[n][r0]);
      }
    }

    /*************** [ write distance data from wall ] *******************/
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);
	fscanf(fpw,"%lf\n",&d_wall[n][r0]);
      }
    }

    /*************** [ write filter width data ] *******************/
    for(i=0;i<it[n]-1;i++){
      for(j=0;j<jt[n]-1;j++){
	r0 = dim[n](i, j);      
	fscanf(fpw,"%lf %lf\n",&deruta_x[n][r0], &deruta_y[n][r0]);
      }
    }

  }

  fclose(fpw);  


}
