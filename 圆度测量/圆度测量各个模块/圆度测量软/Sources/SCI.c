#include "SCI.h"



unsigned char data_receive;
unsigned char data_receive1;

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
void INIT_SCI0(void) 
{
  SCI0BD = BUS_CLOCK/16/BAUD;   //设置SCI0波特率为9600
  SCI0CR1 = 0x12;        //设置SCI1为正常模式，9位数据位，一个偶校验，一个停止位
  SCI0CR2 = 0x0c;        //允许接收和发送数据，禁止中断功能 
}

void INIT_SCI1(void) 
{
  SCI1BD = BUS_CLOCK/16/BAUD;   //设置SCI0波特率为9600
  SCI1CR1 = 0x12;        //设置SCI1为正常模式，八位数据位，一个偶校验，一个停止位
  SCI1CR2 = 0x0c;        //允许接收和发送数据，禁止中断功能 
}

/*************************************************************/
/*                       串口发送函数                        */
/*************************************************************/
void SCI0_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI0DRL = data;
}
/*************************************************************/
/*                       串口发送函数                        */
/*************************************************************/
void SCI1_send(unsigned char data) 
{
  while(!SCI1SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI1DRL = data;
}

/*************************************************************/
/*                       串口发送字符串函数                        */
/*************************************************************/
void SCI0_send_string(unsigned char data[],int len) 
{ 
  int i;
  for(i=0;i<len;i++) 
  {
     SCI0_send(data[i]);
     //Delay_ms(10);
  }

}
/*************************************************************/
/*                       串口发送字符串函数                        */
/*************************************************************/
void SCI1_send_string(unsigned char data[],int len) 
{ 
  int i;
  for(i=0;i<len;i++) 
  {
     SCI1_send(data[i]);
     //Delay_ms(10);
  }

}
/*************************************************************/
/*                       串口接收函数                        */
/*************************************************************/
unsigned char SCI0_receive(void) 
{
  while(!SCI0SR1_RDRF);          //等待接收数据寄存器满
  return(SCI0DRL);
}
/*************************************************************/
/*                       串口接收函数                        */
/*************************************************************/
unsigned char SCI1_receive(void) 
{
  while(!SCI1SR1_RDRF);          //等待接收数据寄存器满
  return(SCI1DRL);
}

void SCI0_receive_string(unsigned char data_receive[], int len){
  int i=0;
  for(i=0;i<len;i++) 
  {
     data_receive[i] = SCI0_receive();
    // Delay_ms(10);
  }
  
}
void SCI1_receive_string(unsigned char data_receive[], int len){
  int i=0;
  for(i=0;i<len;i++) 
  {
     data_receive[i] = SCI1_receive();
     //Delay_ms(10);
  }
  
}

