#include "LED.h"

unsigned char LED_SEG_TAB[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x1a,0x7a,0x9e,0x8e,0x01};

unsigned char display_ge=0;
unsigned char display_shi=0;
unsigned char display_bai=0;
unsigned char display_qian=0;

unsigned char Led_Buf1[4];		//显存4字节，4个数码管
unsigned char Led_Buf2[4];		//显存4字节，4个数码管
unsigned char Led_Buf3[4];		//显存4字节，4个数码管
unsigned char point_1;//第一数码管小数点选择位
unsigned char point_2;//第二数码管小数点选择位
unsigned char point_3;//第三数码管小数点选择位

# define SER1  PORTB_PB0
# define SER1_dir DDRB_DDRB0
# define SCK1  PORTB_PB1
# define SCK1_dir DDRB_DDRB1 
# define RCK1  PORTB_PB2
# define RCK1_dir DDRB_DDRB2                         //0    1    2     3    4    5    6    7    8    9    0    a    b    c    d    e    f.

# define SER2  PORTB_PB3
# define SER2_dir DDRB_DDRB3
# define SCK2  PORTB_PB4
# define SCK2_dir DDRB_DDRB4
# define RCK2  PORTB_PB5
# define RCK2_dir DDRB_DDRB5

# define SER3  PORTK_PK0
# define SER3_dir DDRK_DDRK0
# define SCK3  PORTK_PK1
# define SCK3_dir DDRK_DDRK1
# define RCK3  PORTK_PK2
# define RCK3_dir DDRK_DDRK2

 /************************************************************/
/*                        延时函数                           */
/*************************************************************/
void Delay_us(int us)	
{
	 int ii,jj;
    for(ii=0;ii<us;ii++)
      for(jj=0;jj<10;jj++);
 }  
void Delay_ms(unsigned int ms) 
{
  unsigned int i,j;
  for(j=0;j<ms;j++)
  for(i=0;i<160;i++);
}
/*============================================
送一个字节
=============================================*/
void Led_Send_Byte1(unsigned char data_temp)
{
	unsigned char i,temp;
	temp=data_temp;
	for(i=0;i<8;i++)
	{
		if((temp & 0x01)==0)
		{SER1=0;}
		else
		{SER1=1;}
		SCK1=0;
		Delay_us(20);
		SCK1=1;
		temp=temp/2;
	}
}
/*============================================
送一个字节
=============================================*/
void Led_Send_Byte2(unsigned char data_temp)
{
	unsigned char i,temp;
	temp=data_temp;
	for(i=0;i<8;i++)
	{
		if((temp & 0x01)==0)
		{SER2=0;}
		else
		{SER2=1;}
		SCK2=0;
		Delay_us(20);
		SCK2=1;
		temp=temp/2;
	}
}
/*============================================
送一个字节
=============================================*/
void Led_Send_Byte3(unsigned char data_temp)
{
	unsigned char i,temp;
	temp=data_temp;
	for(i=0;i<8;i++)
	{
		if((temp & 0x01)==0)
		{SER3=0;}
		else
		{SER3=1;}
		SCK3=0;
		Delay_us(20);
		SCK3=1;
		temp=temp/2;
	}
}

/*============================================
锁存，锁存已经发送的数据
=============================================*/
void Led_Lock1(void)
{
	RCK1=0;
	Delay_us(100);
	RCK1=1;
}
/*============================================
锁存，锁存已经发送的数据
=============================================*/
void Led_Lock2(void)
{
	RCK2=0;
	Delay_us(100);
	RCK2=1;
}
/*============================================
锁存，锁存已经发送的数据
=============================================*/
void Led_Lock3(void)
{
	RCK3=0;
	Delay_us(100);
	RCK3=1;
}

/*============================================
刷新显示，将buf字符组数据全部送出，并锁存显示
count为数码管个数，等于buf字节数
=============================================*/
void Led_Send_Buf1(unsigned char *buf,unsigned char count)
{
	unsigned char i;
	for(i=0;i<count;i++)
	{
		if(point_1==i)
		   Led_Send_Byte1(LED_SEG_TAB[*buf]|0b00000001);
		else
		   Led_Send_Byte1(LED_SEG_TAB[*buf]);
		   
		buf++;
	}
	Led_Lock1();
}
/*============================================
刷新显示，将buf字符组数据全部送出，并锁存显示
count为数码管个数，等于buf字节数
=============================================*/
void Led_Send_Buf2(unsigned char *buf,unsigned char count)
{
	unsigned char i;
	for(i=0;i<count;i++)
	{
		if(point_2==i)
		   Led_Send_Byte2(LED_SEG_TAB[*buf]|0b00000001);
		else
		   Led_Send_Byte2(LED_SEG_TAB[*buf]);
		   
		buf++;
	}
	Led_Lock2();
}
/*============================================
刷新显示，将buf字符组数据全部送出，并锁存显示
count为数码管个数，等于buf字节数
=============================================*/
void Led_Send_Buf3(unsigned char *buf,unsigned char count)
{
	unsigned char i;
	for(i=0;i<count;i++)
	{
		if(point_3==i)
		   Led_Send_Byte3(LED_SEG_TAB[*buf]|0b00000001);
		else
		   Led_Send_Byte3(LED_SEG_TAB[*buf]);
		   
		buf++;
	}
	Led_Lock3();
}

/*============================================
                   给LED灯赋值
=============================================*/
void LED_on(int err) 
{
  if(err>= 9899) 
  {
  err = 9899;
  }
  Led_Buf1[0]=err%10;
	Led_Buf1[1]=(err/10)%10;
	Led_Buf1[2]=(err/100)%10;
	Led_Buf1[3]=err/1000;
	Led_Send_Buf1(&Led_Buf1[0],4);	
  Led_Send_Buf1(&Led_Buf1[0],4);
/*	Led_Buf2[0]=2;
	Led_Buf2[1]=2;
	Led_Buf2[2]=3;
	Led_Buf2[3]=4;
	Led_Send_Buf2(&Led_Buf2[0],4);
	Led_Send_Buf2(&Led_Buf2[0],4);
	Led_Send_Buf2(&Led_Buf2[0],4);
	Led_Send_Buf2(&Led_Buf2[0],4); 

	Led_Buf3[0]=1;
	Led_Buf3[1]=2;
	Led_Buf3[2]=3;
	Led_Buf3[3]=4;
	Led_Send_Buf3(&Led_Buf3[0],4);
	Led_Send_Buf3(&Led_Buf3[0],4);
	Led_Send_Buf3(&Led_Buf3[0],4);
	Led_Send_Buf3(&Led_Buf3[0],4); */

//	for(;;)
	//{
	
	    point_1=3;
	  	Led_Send_Buf1(&Led_Buf1[0],4);
		  //Delay_ms(50);
		
	  	//point_1=2;
		  //Led_Send_Buf1(&Led_Buf1[0],4);
		  //Delay_ms(5000);
		
	  //	point_1=3;
	  //	Led_Send_Buf1(&Led_Buf1[0],4);
		 // Delay_ms(5000);
//	}
		
		
}
