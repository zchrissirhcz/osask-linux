addr=0x7c00
OBJDIR=.
entry_objs=entry.o
ccode_objs=main.o screen.o font.o print.o idtgdt.o

CFLAGS := $(CFLAGS) -O1 -fno-builtin -I$(OBJDIR) -MD                                                                                        
CFLAGS += -fno-omit-frame-pointer
CFLAGS += -Wall -Wno-format -Wno-unused -Werror -gstabs -m32


LDFLAGS=-m elf_i386

all:kernel

kernel:entry cobj
	cat cobj>>entry
	cp entry kernel

%.o:%.S
	gcc -nostdinc $(CFLAGS) -c -o $@ $<
%.o:%.c
	@#对应《30天》中的bootpack.c
	gcc -nostdinc $(CFLAGS) -Os -c -o $@ $<
%.o:.asm
	nasm -f elf -o $@ $<

entry:$(entry_objs)
cobj:$(ccode_objs)

entry:
	@echo "addr=$(addr)"
	ld $(LDFLAGS) -N -e entry -Ttext 0xc400 -o $@.out $^
	objdump -S -D $@.out > $@.asm
	objcopy -S -O binary -j .text $@.out $@

cobj:
	ld $(LDFLAGS) -N -e bootmain -T kernel.ld -o $@.out $^
	objdump -D $@.out >$@.asm
	objcopy -S -O binary $@.out $@

run:
	qemu-system-i386 -drive file=kernel,if=floppy

clean:
	@rm -f *.d *.o *.out main.o kernel kernel.asm cobj* entry.o entry.asm entry
