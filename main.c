#include "boot.h"

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
	volatile unsigned short dat = 0;

	writel(GPKCON0, 0x11112222);
#if 1	
	dat = *((volatile unsigned int*)GPKDAT);
	dat |= 0xfaf;
#else
	readl(GPKDAT, dat);
	dat |= 0xfaf;
#endif	

	writel(GPKDAT, dat);
}

int main(int argc, char *argv[])
{
//	unsigned char dat[100];

	led_init();
//	uart_init();
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

