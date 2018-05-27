#include "uart.h"
#include "io.h"

#define ULCON0 		0x7f005000
#define UCON0  		0x7f005004
#define UFCON0 		0x7f005008
#define UMCON0 		0x7f00500C
#define UTRSTAT0 	0x7f005010
#define UERSTAT0    0x7f005014
#define UFSTAT0		0x7f005018
#define UMSTAT0		0x7f00501C
#define UTXH0		0x7f005020
#define URXH0		0x7f005024
#define UBRDIV0		0x7f005028
#define UDIVSLOT0	0x7f00502C
#define UINTP0		0x7f005030
#define UINTSP0     0x7f005034
#define UINTM0		0x7f005038


void uart_init(int uart_id)
{
	/*ULCON0********************************************************
	 * bit7: reserved
	 * bit6: infra-read Mode 0:normal 1:infra-Mode
	 * bit[5:3] : parity mode : 0xx:no parity 
	 * bit[2]: number of stop bit: 0:one stop bit 1:twp stop bit7
	 * bit[1:0] 11:8bit
	 * */
	*(unsigned int*)ULCON0 = (0 << 7)|(0 << 6)|(3 < 3)|(0 <<2)|(3 << 0);	

	*(unsigned int*)UCON0 = (0 << 10)|(0 << 9)|(0<<8)|(0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<2)|(0<<0);

	*(unsigned int*)UFCON0 = (0 << 6)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0 <<0);

	*(unsigned int*)UMCON0 = 0x0;

	*(unsigned int*)UBRDIV0 = 35;
	*(unsigned int*)UDIVSLOT0 = 1;
}

void uart_tx(char *tx)
{
	while(!readl(UTRSTAT0)){
		writeb(UTXH0, *tx);
	}
}



