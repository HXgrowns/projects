#include "SCI.h"



//unsigned char data_receive;
//unsigned char data_receive1;

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

