/*---------------------------------------------------------*/
/************************************************************
飞翔科技MC9S12XEP100汽车电子综合开发平台 
E-mail: 2008f.d@163.com
淘宝店：http://fxfreefly.taobao.com
************************************************************/
/*---------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "SCI.h"
#include "LED.h" 

#define LEDCPU PORTA_PA0
#define LEDCPU_dir DDRA_DDRA0
#define LED_ON 0              
#define LED_OFF 1

#define BUZZCPU PORTA_PA3
#define BUZZCPU_dir DDRA_DDRA3
#define BUZZ_ON 0              
#define BUZZ_OFF 1


#define BUS_CLOCK		   32000000	   //总线频率
#define QSC_CLOCK		   16000000	   //晶振频率
#define BAUD 38400
  
int systemmax = 0; 
unsigned int wucha1 = 0;
unsigned int wucha2 = 0;
unsigned int shang = 0;
  
    
   
 unsigned char flag =0; 
 unsigned char fl =0;
  /*************************************************************/
/*                        延时函数                           */
/*************************************************************/
void delay(unsigned int n) 
{
  unsigned int i,j;
  for(j=0;j<n;j++)
  for(i=0;i<40000;i++);
}
/*************************************************************/
/*                     PIT模块初始化函数                     */
/*************************************************************/
 void init_PIT()
 {
 
 PITMTLD0=249;     //为0通道8位计数器赋值
 PITLD0= 63999;     //为0通道16位计数器赋值   //(249+1)*(3839+1)=16000000个总线周期=0.5秒
 PITMUX_PMUX0=0;   //第0通道使用微计数器0
 PITCE_PCE0=1;     //第0通道计数器工作 
 PITCFLMT=0X80;    //使能周期中断定时器
 PITINTE_PINTE0=1; //0通道定时器定时中断被使能
 }

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
/*                        初始化看门狗                       */
/*************************************************************/
/*void INIT_COP(void)
{
  COPCTL = 0x07;     //设置看门狗复位间隔为1.048576s
} */
/*************************************************************/
/*                       初始化按键                          */
/*************************************************************/
void Init_INTH(void) 
{
     DDRH_DDRH0=0;      //0为输入、1位输出
    
     PPSH_PPSH0 = 0;		      //选择  下降沿  触发  外部中断
     PIEH_PIEH0 = 1;		      //中断使能寄存器;
     PIFH_PIFH0 = 1;					//清除标志位，写1;

}
/*************************************************************/
/*                    按键中断函数                           */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

interrupt 25 void PTH_inter(void) 
{
 
     
   if(PIFH_PIFH0 == 1)     //判断中断标志
   {
      PIFH_PIFH0 = 1;     //清除中断标志
          if(fl ==0) {
           //init_PIT();
        //  INIT_SCI0();
        // INIT_SCI1();
          fl =1;
          } 
          flag = 1;
          //sum =0;
          wucha1 = 0;
          wucha2 = 0;
          shang = 0;
         systemmax = 0;
         //LED_on(systemmax);
       //  LEDCPU=1;
         BUZZCPU=BUZZ_OFF;
   }   
}
interrupt 66 void PIT_INTER(void) 
{ 
    if(PITTF_PTF0==1) {
      
      PITTF_PTF0=1;            
     LED_on(systemmax);
    }
}
/*interrupt 21 void receivedata(void) 
{
    data_receive = SCI_receive();
    if(data_receive == 'O') 
    {
      SCI_send('Y');
      LEDCPU = LED_ON;
    }
    if(data_receive == 'C')
    {
      SCI_send('V');
      LEDCPU = LED_OFF;
    }
} */
#pragma CODE_SEG DEFAULT


/*************************************************************/
/*                         主函数                            */
/*************************************************************/
void main(void)
 {
 
   static int sum = 0;
   int origin;
   int sign;
   unsigned char data[] ={0x80,0x03,0x00,0x00,0x00,0x08,0x5A,0x1D}; 
   unsigned char data_receive[21] = {0};
    int shan;
   
   
  DisableInterrupts; 
  INIT_PLL();
  SER1_dir = 1;
  SCK1_dir = 1;
  RCK1_dir = 1;
  
  SER2_dir = 1;
  SCK2_dir = 1;
  RCK2_dir = 1;
  //INIT_SCI0();
  INIT_SCI1();
  SER3_dir = 1;
  SCK3_dir = 1;
  RCK3_dir = 1;
  
  LEDCPU_dir = 1;
  BUZZCPU_dir = 1;
  
  Init_INTH();
  EnableInterrupts;
  
  delay(10);
 
 for(;;) { 
 
  SCI1_send_string(data,8);
  SCI1_receive_string(data_receive,21);
  if(data_receive[3]>0) 
  {
     sign = -1 ;
  } 
  else
  {
    sign = 1;
  }
  if(flag==1) 
  {
      origin =sign*(data_receive[5]*16*16+data_receive[6]);
      flag = 0;
  } 
  else
      sum =sign*(data_receive[5]*16*16+data_receive[6]);
    
  if(sum>origin) 
     {
      wucha1 = sum-origin;
     }
      else 
      {
       wucha2 = origin-sum;
      }
      shang = wucha1 + wucha2;
      systemmax = systemmax>shang?systemmax:shang;
      LED_on(systemmax);
      shan++;
      if(shan>20)
       {
        
          if(systemmax>200||systemmax<-200)
           {
            
             
                  LEDCPU=~LEDCPU;
                  //BUZZCPU=BUZZ_ON;
                  shan=0;
           }
       }
        
       
  } 
}
                    


