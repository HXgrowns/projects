/*---------------------------------------------------------*/
/************************************************************
飞翔科技MC9S12XEP100汽车电子综合开发平台 
E-mail: 2008f.d@163.com
淘宝店：http://fxfreefly.taobao.com
************************************************************/
/*---------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "SCI.h"
#define LEDCPU PORTB_PB0
#define LEDCPU_dir DDRB_DDRB0
#define LED_ON 0
#define LED_OFF 1

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

 //unsigned char data_receive;
/*************************************************************/
/*                        延时函数                           */
/*************************************************************/
void delay(unsigned int n) 
{
  unsigned int i,j;
  for(j=0;j<n;j++)
  for(i=0;i<40000;i++)
  ;
}
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
         
      }
      if(STOP == 0) 
      {
         
      }
   }   
}
#pragma CODE_SEG DEFAULT


/*************************************************************/
/*                         主函数                            */
/*************************************************************/
void main(void) 
{
  unsigned char receive[21] = {0};
	DisableInterrupts;
  init_key();
  LEDCPU_dir = 1;
	EnableInterrupts;
  LEDCPU = LED_ON;
for(;;)
  {
  
     unsigned char data[] ={0x80,0x03,0x00,0x00,0x00,0x08,0x5A,0x1D}; 
     send_string(data,8);
     receive_string(receive,21);
     
  }
}