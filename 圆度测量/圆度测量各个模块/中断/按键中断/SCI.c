#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define BUS_CLOCK		   32000000	   //总线频率
#define OSC_CLOCK		   16000000	   //晶振频率
#define BAUD 9600

unsigned char data_receive;
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
/*                        初始化SCI                          */
/*************************************************************/
void INIT_SCI(void) 
{
  SCI0BD = BUS_CLOCK/16/BAUD;   //设置SCI0波特率为9600
  SCI0CR1 = 0x00;        //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI0CR2 = 0x2c;        //允许接收和发送数据，允许接收中断功能 
}

/*************************************************************/
/*                       串口发送函数                        */
/*************************************************************/
void SCI_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI0DRL = data;
}
/*************************************************************/
/*                       串口接收函数                        */
/*************************************************************/
unsigned char SCI_receive(void) 
{
  while(!SCI0SR1_RDRF);          //等待发送数据寄存器满
  return(SCI0DRL);
}