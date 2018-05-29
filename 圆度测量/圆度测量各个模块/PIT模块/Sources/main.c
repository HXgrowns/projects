/*---------------------------------------------------------*/
/************************************************************
����Ƽ�MC9S12XEP100���������ۺϿ���ƽ̨
E-mail: 2008f.d@163.com
�Ա��꣺http://fxfreefly.taobao.com
************************************************************/
/*---------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define LEDCPU PORTB_PB0
#define LEDCPU_dir DDRB_DDRB0
#define  BUS_CLOCK		   32000000	   //����Ƶ��
#define  OSC_CLOCK		   16000000	   //����Ƶ��

/*************************************************************/
/*                      ��ʼ�����໷                         */
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

    REFDV = 0x81;         //PLLCLK=2��OSCCLK��(SYNR+1)/(REFDV+1)��64MHz ,fbus=32M
    PLLCTL =PLLCTL|0x70;  //Enable PLL circuit
    asm NOP;
    asm NOP;
    while(!(CRGFLG&0x08)); //PLLCLK is Locked already
    CLKSEL |= 0x80;        //set PLLCLK as sysclk
}
 
/*************************************************************/
/*                     PITģ���ʼ������                     */
/*************************************************************/
 void init_PIT(){
 
 PITMTLD0=249;     //Ϊ0ͨ��8λ��������ֵ
 PITLD0= 3839;     //Ϊ0ͨ��16λ��������ֵ   //(249+1)*(3839+1)=16000000����������=0.03��
 PITMUX_PMUX0=0;   //��0ͨ��ʹ��΢������0
 PITCE_PCE0=1;     //��0ͨ������������ 
 PITCFLMT=0X80;    //ʹ�������ж϶�ʱ��
 PITINTE_PINTE0=1; //0ͨ����ʱ����ʱ�жϱ�ʹ��
 }

/*************************************************************/
/*                     PITģ���жϺ���                     */
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
/*                         ������                            */
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