#include "boot.h"
#include "io.h"
#include "clock.h"
#include "uart.h"

inline void delay (unsigned long loops)  
{  
    __asm__ volatile ("1:\n"  
        "subs %0, %1, #1\n"  
        "bne 1b":"=r" (loops):"0" (loops));  
} 

void mdelay(void)
{
	volatile unsigned int tm = 4000000; //local varible needs to vlolatile! 
	
	while(tm--);
}

void led_init(void)
{
	unsigned short dat = 0;

	writel(GPKCON0, 0x11112222);
	dat = readw(GPKDAT);
	dat |= 0xfff;
	dat &= 0xfaf;
	writel(GPKDAT, dat);
}

int main(int argc, char *argv[])
{
//	unsigned char dat[100];

	led_init();

	tiny6410_clock_init();

	uart_init(0);
	
	uart_tx("hello\n");

//	nand_init();

//	nand_read_id();
//	ret = nand_erase_one_block(3);
//	if(ret == 0){
//		nand_read_one_page(3, 0, dat, 10);
//		uart_tx_multiple_bytes(dat, 10);	
//	}


	while(1){
//		led_display();
	}

	return 0;
}

