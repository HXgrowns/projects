/*---------------------------------------------------------*/
/************************************************************
飞翔科技MC9S12XEP100汽车电子综合开发平台
E-mail: 2008f.d@163.com
淘宝店：http://fxfreefly.taobao.com
************************************************************/
/*---------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define LEDCPU PORTB_PB0
#define LEDCPU_dir DDRB_DDRB0
#define  BUS_CLOCK		   32000000	   //总线频率
#define  OSC_CLOCK		   16000000	   //晶振频率

/*************************************************************/
/*                      初始化锁相环                         */
/*************************************************************/
void INIT_PLL(void) 
{
    CLKSEL &= 0x7f;       //set OSCCLK as sysclk
    PLLCTL &= 0x8F;       //Disable PLL circuit
    CRGINT &= 0xDF;
    
    #if(BUS_CLOCK == 40000000) 
      SYNR = 0x44;
    #elif(BUS_CLOCK == 32000000)
      SYNR = 0x43;     
    #elif(BUS_CLOCK == 24000000)
      SYNR = 0x42;
    #endif 

    REFDV = 0x81;         //PLLCLK=2×OSCCLK×(SYNR+1)/(REFDV+1)＝64MHz ,fbus=32M
    PLLCTL =PLLCTL|0x70;  //Enable PLL circuit
    asm NOP;
    asm NOP;
    while(!(CRGFLG&0x08)); //PLLCLK is Locked already
    CLKSEL |= 0x80;        //set PLLCLK as sysclk
}
 
/*************************************************************/
/*                     PIT模块初始化函数                     */
/*************************************************************/
 void init_PIT(){
 
 PITMTLD0=249;     //为0通道8位计数器赋值
 PITLD0= 3839;     //为0通道16位计数器赋值   //(249+1)*(3839+1)=16000000个总线周期=0.03秒
 PITMUX_PMUX0=0;   //第0通道使用微计数器0
 PITCE_PCE0=1;     //第0通道计数器工作 
 PITCFLMT=0X80;    //使能周期中断定时器
 PITINTE_PINTE0=1; //0通道定时器定时中断被使能
 }

/*************************************************************/
/*                     PIT模块中断函数                     */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT_INTER(void) 
{   int m;
    if(PITTF_PTF0==1) {
      
      PITTF_PTF0=1;            
      LEDCPU=~LEDCPU;
    }
}
#pragma CODE_SEG DEFAULT


/*************************************************************/
/*                         主函数                            */
/*************************************************************/
void main(void) 
{
  
  DisableInterrupts;
  INIT_PLL();
  LEDCPU_dir=1;
  init_PIT();
	EnableInterrupts;

  for(;;)
   {  
   }
  
}