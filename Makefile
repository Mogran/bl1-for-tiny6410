TARGET=boot
TEXTBASE=0x0C000000

CROSS_COMPILE=arm-none-linux-gnueabi-
#gnu c compiler
CC       = $(CROSS_COMPILE)gcc 
#generate ELF format file
LD       = $(CROSS_COMPILE)ld
#STL generate 
AR       = $(CROSS_COMPILE)ar
#arm-linux-copy src_file dst_file (different file format)
OBJCOPY  = $(CROSS_COMPILE)objcopy
#arm-linux-dump src_file ? remove src_file's symbol and unused info.
OBJDUMP  = $(CROSS_COMPILE)objdump
#arm-linux-strip 
STRIP    = $(CROSS_COMPILE)strip
#arm-linux-readelf
READELF  = $(CROSS_COMPILE)readelf

CFLAGS =-g -O2 -Wall -nostdinc -nostdlib -fno-builtin
AFLAGS = ${CFLAGS} -D_ASSEMBLY__

LDFALGS= -nostartfiles -T $(TARGET).lds -Ttext $(TEXTBASE)

SRC_C=$(wildcard *.c)
SRC_S=$(wildcard *.S)

OBJ_C=$(patsubst %.c,%.o,$(SRC_C))
OBJ_S=$(patsubst %.S,%.o,$(SRC_S))
OBJ_ALL=$(OBJ_C) $(OBJ_S)

.PHONY:all
all:${OBJ_ALL}
	${LD} ${LDFALGS} -o ${TARGET}.elf ${OBJ_ALL}
	${OBJCOPY} -O binary -S ${TARGET}.elf ${TARGET}.bin
	rm -rf *.o *.elf
#	rm -rf /mnt/hgfs/share/bootstrap.bin 
#	cp -a ${TARGET}.bin /mnt/hgfs/share/	

%.o:%.c
	${CC} ${CFLAGS} -c -o $@ $<
%.o:%.S
	${CC} ${AFLAGS} -c -o $@ $<

clean:
	rm -rf *.elf ${TARGET}.bin *.o

