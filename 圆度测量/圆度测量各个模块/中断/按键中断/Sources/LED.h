#include <iom128v.h>
#include <macros.h>			//Í·ÎÄ¼þ
#include <delay16m.c>

void Led_Send_Byte1(unsigned char data_temp);
void Led_Send_Byte2(unsigned char data_temp);
void Led_Send_Byte3(unsigned char data_temp);
void Led_Send_Byte4(unsigned char data_temp);

void Led_Lock1(void);
void Led_Lock2(void);
void Led_Lock3(void);
void Led_Lock4(void);

void Led_Send_Buf1(unsigned char *buf,unsigned char count);
void Led_Send_Buf2(unsigned char *buf,unsigned char count);
