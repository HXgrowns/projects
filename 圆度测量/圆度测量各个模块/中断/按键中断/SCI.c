#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define BUS_CLOCK		   32000000	   //����Ƶ��
#define OSC_CLOCK		   16000000	   //����Ƶ��
#define BAUD 9600

unsigned char data_receive;
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
/*                        ��ʼ��SCI                          */
/*************************************************************/
void INIT_SCI(void) 
{
  SCI0BD = BUS_CLOCK/16/BAUD;   //����SCI0������Ϊ9600
  SCI0CR1 = 0x00;        //����SCI0Ϊ����ģʽ����λ����λ������żУ��
  SCI0CR2 = 0x2c;        //������պͷ������ݣ���������жϹ��� 
}

/*************************************************************/
/*                       ���ڷ��ͺ���                        */
/*************************************************************/
void SCI_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
  SCI0DRL = data;
}
/*************************************************************/
/*                       ���ڽ��պ���                        */
/*************************************************************/
unsigned char SCI_receive(void) 
{
  while(!SCI0SR1_RDRF);          //�ȴ��������ݼĴ�����
  return(SCI0DRL);
}