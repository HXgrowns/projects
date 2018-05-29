#include "key.h"

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

 int i;
 int max = 0;
 int min = 0;
 int wucha = 0;
/*************************************************************/
/*                       初始化按键                          */
/*************************************************************/
void init_key(void) 
{
     START_dir =0;       //设置为输入
     STOP_dir=0;
     SELECT1_dir=0;
     SELECT2_dir=0;
     SELECT3_dir=0;
     SELECT4_dir=0;
     PPSH = 0x00;		      //极性选择寄存器,选择下降沿;
     PIFH = 0xff;					//对PIFH的每一位写1来清除标志位;
     PIEH = 0xff;		      //中断使能寄存器;
}
/*************************************************************/
/*                    按键中断函数                           */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt  void PTH_inter(void) 
{ 
   if(PIFH != 0)     //判断中断标志
   {
      PIFH = 0xff;     //清除中断标志
      if(START == 0)         //按键1按下
      {
      for(i=0;i<100;i++)
      { 
      max=max>key_receive_data[i]?max:key_receive_data[i];
      min=min<key_receive_data[i]?min:key_receive_data[i];
      wucha = max-min;
      }
      }
      if(STOP == 0) 
      {
         
      }
   }   
}
#pragma CODE_SEG DEFAULT

