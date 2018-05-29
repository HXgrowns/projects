#include "key.h"

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

 int i;
 int max = 0;
 int min = 0;
 int wucha = 0;
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
      }
      }
      if(STOP == 0) 
      {
         
      }
   }   
}
#pragma CODE_SEG DEFAULT

