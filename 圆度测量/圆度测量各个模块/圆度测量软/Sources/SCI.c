#include "SCI.h"



unsigned char data_receive;
unsigned char data_receive1;

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
void INIT_SCI0(void) 
{
  SCI0BD = BUS_CLOCK/16/BAUD;   //����SCI0������Ϊ9600
  SCI0CR1 = 0x12;        //����SCI1Ϊ����ģʽ��9λ����λ��һ��żУ�飬һ��ֹͣλ
  SCI0CR2 = 0x0c;        //������պͷ������ݣ���ֹ�жϹ��� 
}

void INIT_SCI1(void) 
{
  SCI1BD = BUS_CLOCK/16/BAUD;   //����SCI0������Ϊ9600
  SCI1CR1 = 0x12;        //����SCI1Ϊ����ģʽ����λ����λ��һ��żУ�飬һ��ֹͣλ
  SCI1CR2 = 0x0c;        //������պͷ������ݣ���ֹ�жϹ��� 
}

/*************************************************************/
/*                       ���ڷ��ͺ���                        */
/*************************************************************/
void SCI0_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
  SCI0DRL = data;
}
/*************************************************************/
/*                       ���ڷ��ͺ���                        */
/*************************************************************/
void SCI1_send(unsigned char data) 
{
  while(!SCI1SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
  SCI1DRL = data;
}

/*************************************************************/
/*                       ���ڷ����ַ�������                        */
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
/*                       ���ڷ����ַ�������                        */
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
/*                       ���ڽ��պ���                        */
/*************************************************************/
unsigned char SCI0_receive(void) 
{
  while(!SCI0SR1_RDRF);          //�ȴ��������ݼĴ�����
  return(SCI0DRL);
}
/*************************************************************/
/*                       ���ڽ��պ���                        */
/*************************************************************/
unsigned char SCI1_receive(void) 
{
  while(!SCI1SR1_RDRF);          //�ȴ��������ݼĴ�����
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

