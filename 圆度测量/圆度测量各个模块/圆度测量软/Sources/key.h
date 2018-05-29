#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define START PTIH_PTIH0
#define STOP PTIH_PTIH1
#define SELECT1 PTIH_PTIH2
#define SELECT2 PTIH_PTIH4
#define SELECT3 PTIH_PTIH5
#define SELECT4 PTIH_PTIH6  //设置PH口作用
#define START_dir DDRH_DDRH0
#define STOP_dir DDRH_DDRH1
#define SELECT1_dir DDRH_DDRH2
#define SELECT2_dir DDRH_DDRH4
#define SELECT3_dir DDRH_DDRH5
#define SELECT4_dir DDRH_DDRH6//设置PH口方向

void init_key(void);

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PTH_inter(void) ;
#pragma CODE_SEG DEFAULT
