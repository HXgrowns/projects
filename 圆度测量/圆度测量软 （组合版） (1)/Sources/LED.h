#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

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
void Delay_us(int us);
void Delay_ms(unsigned int ms);
void Led_Send_Byte1(unsigned char data_temp);
void Led_Send_Byte2(unsigned char data_temp);
void Led_Send_Byte3(unsigned char data_temp);
void Led_Lock1(void);
void Led_Lock2(void);
void Led_Lock3(void);
void Led_Send_Buf1(unsigned char *buf,unsigned char count);
void Led_Send_Buf2(unsigned char *buf,unsigned char count);
void Led_Send_Buf3(unsigned char *buf,unsigned char count);
void LED_on(int err);
