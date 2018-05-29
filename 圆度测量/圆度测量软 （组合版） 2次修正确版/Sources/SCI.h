#include <hidef.h>      /* common defines and macros */
#include "derivative.h" 

void SCI0_send(unsigned char data) ;
void SCI1_send(unsigned char data) ;
void SCI0_send_string(unsigned char data[],int len) ;
void SCI1_send_string(unsigned char data[],int len) ;
unsigned char SCI0_receive(void) ;
unsigned char SCI1_receive(void) ;
void SCI0_receive_string(unsigned char data_receive[], int len);
void SCI1_receive_string(unsigned char data_receive[], int len);