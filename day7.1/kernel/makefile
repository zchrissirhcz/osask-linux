#
# Makefile fragment for the JOS kernel.
# This is NOT a complete makefile;
# you must run GNU make in the top-level directory
# where the GNUmakefile is located.
#
#entry.S  main.c
OBJCOPY	:= $(GCCPREFIX)objcopy
OBJDUMP	:= $(GCCPREFIX)objdump
OBJDIR=.
entry_objs= entry.o
ccode_objs=main.o screen.o font.o print.o idtgdt.o int.o asmint32.o
CFLAGS := $(CFLAGS) -O1 -fno-builtin -I$(OBJDIR) -MD 
CFLAGS += -fno-omit-frame-pointer
CFLAGS += -Wall -Wno-format -Wno-unused  -gstabs -m32  -fno-stack-protector
LDFLAGS = -m elf_i386

%.o:%.c
	$(CC) -nostdinc $(CFLAGS) -Os -c -o $@ $<


%.o:%.S
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<	
	
%.o:%.asm
	nasm  -f elf -o $@ $<

kernel:entry cobj
	cat cobj>>entry
	cp  entry kernel
	
entry:$(entry_objs)
cobj:$(ccode_objs)




entry: 
	@echo "addr=$(addr)"
	$(LD)  $(LDFLAGS) -N -e entry -Ttext 0xc400 -o $@.out $^
	$(OBJDUMP) -S -D $@.out >$@.asm
	$(OBJCOPY) -S -O binary -j .text $@.out $@
	
cobj: 
	@echo "addr=0x00"
	$(LD)  $(LDFLAGS) -N -e bootmain -T kernel.ld -o $@.out $^
	$(OBJDUMP)  -S -D $@.out >$@.asm
	$(OBJCOPY)  -S -O binary  $@.out $@


clean:
	-rm -f *.d *.o *.out main.o kernel kernel.asm cobj* entry.o entry.asm entry
	
run:
#	dd if=boot of=boot.img bs=512 count=1
	qemu -drive file=kernel,if=floppy