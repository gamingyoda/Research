/**********************************

円柱周りを一般座標系で解く
圧縮性NS方程式

 *********************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
#include "boundary.h" SSTの時こっち
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

  read();

  Initial();

  PostFlow_input(cont);

#ifdef SST
  komega_ini();
#endif

#ifdef SA
  SA_ini();
#endif

  boundary();

  time=cont;

  //以下無限ループ
  while(1){
    Cons_tmp();

    gauss_seidel(time);

    time++;

    //結果を出力
    if(time%outputstep==0){
      PostFlow_output(time);
    }

  }//無限ループ終わり

  return 0;

}
