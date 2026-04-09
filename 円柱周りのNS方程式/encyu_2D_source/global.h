/************************

色々宣言する! 2d

 **********************/

#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef SET_PARAM
# define EXTERN
#else
# define EXTERN extern
#endif

   /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
   /*%%    グリッド                0〜(it-1) の  it    個                %%*/
   /*%%    セル                    0〜(it-2) の (it-1) 個                %%*/
   /*%%      (仮想セルを両側に２個ずつ設ける。)                          %%*/
   /*%%         よって、計算点は   2〜(it-4) の (it-5) 個                %%*/
   /*%%                                                                  %%*/
   /*%%    面積ベクトル            0〜(it-2) の (it-1) 個                %%*/
   /*%%      (境界の名前がそのまま)  (面積も同じ数だけ)                  %%*/
   /*%%    体積                    0〜(it-3) の (it-2) 個                %%*/
   /*%%      (もっとも番号の大きいセルは 体積をもたない。)               %%*/
   /*%%    Fluxベクトル                                                  %%*/
   /*%%      (境界と同じ名前をもつ:面積ベクトルと 同じ)                  %%*/
   /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*-----------------------[Parameter]---------------------------*/
#define dt 2.0e-6                /* 時間刻み */
#define ds 2.0e-5                /* 最小格子幅 */
#define u0 50.0              /* 主流速度 */
#define p0 101.325e+3            /* 大気圧 */
#define rho0 1.184               /* 空気密度 */
#define gamma0 1.4               /* 比熱比 */
#define mu_0 18.24e-6            /* 粘性係数 */
#define T_0 293.15               /* サザランド温度 */
#define C 110.4                  /* サザランド定数 */
#define outputstep 2000          /* 出力ステップ */
#define lambda 1.0               /* 陰解法、陽解法切り替え */
#define RR 0.25                  /* 円柱の半径 */
#define pi 3.141592635897        /* 円周率 */
#define Rair 287.04              /* 空気の気体定数 */
#define t_NUMBER 4               /* ニュートン反復回数 */
#define Pr 0.72                  /* 空気のプラントル数 */
#define Prt 0.9                  /* 乱流プラントル数 */

/* 領域番号 */
#define NT 3 

#define N_IN    0
#define N_WAKE  1
#define N_OUT   2

#define jmax 65                   /* 内部境界との受け渡し定数 */
#define jmin 182                  /*          上同            */

EXTERN unsigned int ( *dim[NT] )(int, int);

/*----------------------[ global variables ]-----------------------*/
EXTERN unsigned int it[NT], jt[NT];                     /* グリッドの総数  番号は 0〜(it-1) */
EXTERN unsigned int dG[NT], dE[NT];

EXTERN double *x_xi[NT],  *y_xi[NT];                    /* メトリック */
EXTERN double *x_eta[NT], *y_eta[NT];                   /* メトリック */
EXTERN double *x_xi_cen[NT],  *y_xi_cen[NT];                    /* メトリック */
EXTERN double *x_eta_cen[NT], *y_eta_cen[NT];                   /* メトリック */
EXTERN double *S[NT];                               /* セルの面積 */
EXTERN double *x[NT], *y[NT];                           /* 格子の座標 */
EXTERN double *cen_x[NT], *cen_y[NT];                   /* セルの座標 */
EXTERN double *cx[NT], *cy[NT];                   /* セルの座標(出力用) */

EXTERN double *rho[NT];                             /*     密度        */      
EXTERN double *ux[NT];                              /*  流速ベクトル   */
EXTERN double *uy[NT];                              /*  流速ベクトル   */
EXTERN double *p[NT];                               /*     静圧        */      
EXTERN double *e[NT];                               /*   全エネルギ    */
EXTERN double *Q[NT][4];                            /*   保存量        */
EXTERN double *tmpQ[NT][4];                         /*   保存量(tmp)   */
EXTERN double *E[NT][4];                            /*  対流流束(xi)   */
EXTERN double *F[NT][4];                            /*  対流流束(eta)  */
EXTERN double *Ecen[NT][6];                            /*  対流流束(xi)   */
EXTERN double *Fcen[NT][6];                            /*  対流流束(eta)  */
EXTERN double *Ev[NT][4];                           /*  粘性流束(xi)   */
EXTERN double *Fv[NT][4];                           /*  粘性流束(eta)  */

/* viscous */
EXTERN double *vis_S[NT][2];
EXTERN double *duxd[NT][2], *duyd[NT][2], *dcptd[NT][2];

/* WCNS */
EXTERN double *Qch[NT][6][2];                            /*   特性量        */
EXTERN double *Qchcv[NT][4][2];                             /*   特性量        */
EXTERN double *TurbQchcv[NT][2][2];                             /*   特性量        */

/* LUADI */
EXTERN double *tmpEE[NT][4];                         /* LU-ADI用の流速保管 */
EXTERN double *dQ[NT][4];                            /* LU-ADI用のデルタQ  */
EXTERN double *rhsF[NT][4];                            /* LU-ADI用のデルタQ  */

/* k-omega */
EXTERN double *d_wall[NT], *yp[NT], *Mut[NT], *k_turb[NT], *omega[NT], *ut_buff[NT];
EXTERN double *TurbE[NT][2],  *TurbF[NT][2];   
EXTERN double *TurbEv[NT][2], *TurbFv[NT][2];   
EXTERN double *TurbQ[NT][2], *TurbtmpQ[NT][2], *TurbdQ[NT][2], *TurbtmpEE[NT][2], *rhsTurbF[NT][2];
EXTERN int *clx[NT], *cly[NT];

/* SA */
EXTERN double *NuSA[NT];

/* DES */
EXTERN double *deruta_x[NT], *deruta_y[NT];
EXTERN double *RA_LE[NT], *lkw[NT];
#define C_DES_kepu 0.61
#define C_DES_kome 0.78


#endif
