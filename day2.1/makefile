subdir=./kernel
all:img
boot:
	nasm -o bootloader hello.nas
img:boot
	dd if=bootloader of=myos.img count=1 bs=512
	dd if=/dev/zero of=myos.img bs=512 seek=1 skip=1 count=2879
run:
	qemu-system-i386 -drive file=myos.img,if=floppy
clean:
	rm bootloader myos.img
