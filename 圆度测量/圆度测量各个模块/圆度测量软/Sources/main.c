/*---------------------------------------------------------*/
/************************************************************
����Ƽ�MC9S12XEP100���������ۺϿ���ƽ̨ 
E-mail: 2008f.d@163.com
�Ա��꣺http://fxfreefly.taobao.com
************************************************************/
/*---------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "SCI.h"

#define LEDCPU PORTA_PA0
#define LEDCPU_dir DDRA_DDRA0
#define LED_ON 0              
#define LED_OFF 1
#define START PTIH_PTIH0
#define STOP PTIH_PTIH1
#define SELECT1 PTIH_PTIH2
#define SELECT2 PTIH_PTIH4
#define SELECT3 PTIH_PTIH5
#define SELECT4 PTIH_PTIH6  //����PH������
#define START_dir DDRH_DDRH0
#define STOP_dir DDRH_DDRH1
#define SELECT1_dir DDRH_DDRH2
#define SELECT2_dir DDRH_DDRH4
#define SELECT3_dir DDRH_DDRH5
#define SELECT4_dir DDRH_DDRH6//����PH�ڷ���

  int key_receive_data[100]={0};
  int index =0;
  int is_full=0;
  /*************************************************************/
/*                        ��ʱ����                           */
/*************************************************************/
void delay(unsigned int n) 
{
  unsigned int i,j;
  for(j=0;j<n;j++)
  for(i=0;i<40000;i++);
}

void Delay_ms(int ms)	
{
	 int ii,jj;
    for(ii=0;ii<ms;ii++)
     // for(jj=0;jj<10;jj++);      //32MHz--1us
      for(jj=0;jj<160;jj++);      //32MHz--1ms
     //for(jj=0;jj<1335;jj++);  //16MHz--1ms
     //for(jj=0;jj<3338;jj++);  //40MHz--1ms
     //for(jj=0;jj<4006;jj++);    //48MHz--1ms
      //for(jj=0;jj<5007;jj++);     //60MHz--1ms
     //for(jj=0;jj<5341;jj++);   //64MHz--1ms
     //for(jj=0;jj<6676;jj++);    //80MHz--1ms
 }  
/*************************************************************/
/*                       ��ʼ������                          */
/*************************************************************/
void init_key(void) 
{
     START_dir =0;       //����Ϊ����
     STOP_dir=0;
     SELECT1_dir=0;
     SELECT2_dir=0;
     SELECT3_dir=0;
     SELECT4_dir=0;
     PPSH = 0x00;		      //����ѡ��Ĵ���,ѡ���½���;
     PIFH = 0xff;					//��PIFH��ÿһλд1�������־λ;
     PIEH = 0xff;		      //�ж�ʹ�ܼĴ���;
}
/*************************************************************/
/*                    �����жϺ���                           */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt  void PTH_inter(void) 
{
     int i;
     int max = 0;
     int min = 0;
     int wucha = 0; 
   if(PIFH != 0)     //�ж��жϱ�־
   {
      PIFH = 0xff;     //����жϱ�־
      if(START == 0)         //����1����
      {
      for(i=0;i<100;i++)
      { 
      max=max>key_receive_data[i]?max:key_receive_data[i];
      min=min<key_receive_data[i]?min:key_receive_data[i];
      wucha = max-min;
      if(wucha>200) 
      {
      for(;;) 
      {
        
        LEDCPU = LED_ON;
        delay(10);
        LEDCPU = LED_OFF;
      }
      }
      
      }
      }
      if(STOP == 0) 
      {
         
      }
   }   
}
#pragma CODE_SEG DEFAULT


/*************************************************************/
/*                         ������                            */
/*************************************************************/
void main(void)
 {
   unsigned char data[] ={0x80,0x03,0x00,0x00,0x00,0x08,0x5A,0x1D}; 
   unsigned char data_receive[21] = {0};
   int sum; 
   int sign;
   
   int m;
   Delay_ms(1);
   m = 1;
  DisableInterrupts; 
  INIT_PLL();
  LEDCPU_dir = 1;
  INIT_SCI0();
  INIT_SCI1();
  EnableInterrupts;
    
  LEDCPU=LED_ON;
  delay(100);
  LEDCPU=LED_OFF;
 
 for(;;) { 
 
  LEDCPU=LED_ON;
  delay(100);
  LEDCPU=LED_OFF; 
 
  SCI1_send_string(data,8);
  SCI1_receive_string(data_receive,21);
  
  if(data_receive[3]>0) 
  {
     sign = 1 ;
  } 
  else
  {
    sign = -1;
  }
  
    sum =sign*(data_receive[5]*16*16+data_receive[6]);
    if(sum<0)
    {
    sum = -1*sum;
    } 
    key_receive_data[index]=sum;
    index++;
    if(index >= 100){
      is_full = 1;
      index = 0; 
    }
  }
}
                    


