#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

///*
void INIT_PLL(void);
void INIT_SCI(void);
void SCI_send(unsigned char data);
unsigned char SCI_receive(void); 
void send_string(unsigned char data[],int len );
void receive_string(unsigned char data[],int len );

//*/