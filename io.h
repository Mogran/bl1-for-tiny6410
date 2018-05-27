#ifndef TINY6410_IO_H
#define TINY6410_IO_H

void writeb(unsigned int addr, unsigned char value);
void writew(unsigned int addr, unsigned short value);
void writel(unsigned int addr, unsigned int value);

unsigned char readb(unsigned int addr);
unsigned short readw(unsigned int addr);
unsigned int readl(unsigned int addr);

#endif
