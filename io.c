#include "io.h"

void writeb(unsigned int addr, unsigned char value)
{
	*(volatile unsigned int *)addr = value;
}

void writew(unsigned int addr, unsigned short value)
{
	*(volatile unsigned int *)addr = value;
}

void writel(unsigned int addr, unsigned int value)
{
	*(volatile unsigned int *)addr = value;
}

unsigned char readb(unsigned int addr)
{
	return *(volatile unsigned int *)addr;
}

unsigned short readw(unsigned int addr)
{
	return *(volatile unsigned int *)addr;
}

unsigned int readl(unsigned int addr)
{
	return *(volatile unsigned int *)addr;
}
