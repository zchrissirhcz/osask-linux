addr=0x7c00
OBJDIR=.

CFLAGS := $(CFLAGS) -O1 -fno-builtin -I$(OBJDIR) -MD                                                                                        
CFLAGS += -fno-omit-frame-pointer
CFLAGS += -Wall -Wno-format -Wno-unused -Werror -gstabs -m32


LDFLAGS=-m elf_i386

all:kernel

kernel:entry.o main.o screen.o
	ld $(LDFLAGS) -N -e start -Ttext $(addr) -o $@.out $^
	objdump -S $@.out >$@.asm
#	objcopy -S -O binary -j .text $@.out $@
	objcopy -S -O binary $@.out $@

entry.o:entry.S
	gcc -nostdinc $(CFLAGS) -c -o $@ $<
main.o:main.c
	@#对应《30天》中的bootpack.c
	gcc -nostdinc $(CFLAGS) -Os -c -o $@ $<
screen.o:screen.c
	gcc -nostdinc $(CFLAGS) -c -o $@ $<

run:
	qemu-system-i386 -drive file=kernel,if=floppy

clean:
	@rm -f entry.o main.o screen.o kernel.out kernel.asm kernel *.d
