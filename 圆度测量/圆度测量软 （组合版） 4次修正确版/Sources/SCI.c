#include "SCI.h"



//unsigned char data_receive;
//unsigned char data_receive1;

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

