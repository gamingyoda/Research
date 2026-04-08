/**********************************

円柱周りを一般座標系で解く
圧縮性NS方程式

 *********************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* 乱流モデルや離散化手法の切り替えはここで行う。 */

#define SET_PARAM        /* パラメーターを設定するとき宣言する     */
#define SST              /* 乱流モデルの切り替え SST と LOWKW  NON */
#define RANS              /* DDES or DES or RANS の切り替えに用いる */
#define MUSCL            /* MUSCL or WCNS の切り替えに用いる */

#include "global.h"
#include "read.h"
#include "calc.h"
#include "output.h"
#include "read_data.h"
#include "initial.h"
#include "boundary.h" /* boundary for SST */
#if 0
#include "boundary.h" SSTの時こっち
#endif
//#include "boundary-SA.h"

#ifdef SST
#include "SST-DES.h"
#include "fds.h"
#include "fds-komega.h"
/* #include "slau-SST.h" */
#include "viscous.h"
#include "viscous-SST.h"
/* #include "LU-SGS-SST.h" */
#include "MFGS-SST.h"
#endif

#ifdef SA
#include "SA-DES.h"
#include "fds.h"
#include "fds-SA.h"
#include "viscous.h"
#include "viscous-SA.h"
#include "MFGS-SA.h"
#endif


#ifdef NON
#include "fds.h"
/* #include "slau.h" */
#include "viscous.h"
#include "LU-SGS.h"
/* #include "MFGS.h" */
#endif

int main(){
  int time, r0, i, j;
  int cont = 0;

  /* 格子・メトリクスを読み込み、共有作業配列を確保する。 */
  read();

  /* 初期の基本変数を与え、保存変数へ変換する。 */
  Initial();

  /* 再開・出力用の初期設定。cont=0 なら初期場から開始する。 */
  PostFlow_input(cont);

#ifdef SST
  /* 選択した乱流モデルの変数を初期化する。 */
  komega_ini();
#endif

#ifdef SA
  /* 選択した乱流モデルの変数を初期化する。 */
  SA_ini();
#endif

  /* 最初の更新前にゴーストセルとブロック境界の値をそろえる。 */
  boundary();

  time=cont;

  /* メインの時間発展ループ。
     1. 現在の状態を退避する。
     2. 陰解法で1ステップ進める。
     3. outputstep ごとに結果を出力する。 */

  //以下無限ループ
  while(1){
    /* tmpQ/TurbtmpQ は多段の陰的更新で使う退避配列。 */
    Cons_tmp();

    /* 上で選んだソルバで物理時間を1ステップ進める。 */
    gauss_seidel(time);

    time++;

    /* 後処理用に一定ステップごとに場を出力する。 */

    //結果を出力
    if(time%outputstep==0){
      PostFlow_output(time);
    }

  }//無限ループ終わり

  return 0;

}
