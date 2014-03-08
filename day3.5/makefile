subdir=./kernel
all:img
boot:
	nasm -o bootloader hello.nas
	nasm -o haribote.bin haribote.nas
img:boot
	dd if=bootloader of=myos.img count=1 bs=512
	dd if=/dev/zero of=myos.img bs=512 seek=1 skip=1 count=2879
copy:
	mkdir -p /tmp/floppy
	mount -o loop myos.img /tmp/floppy -o fat=12
	sleep 1
	cp haribote.bin /tmp/floppy
	sleep 1
	umount /tmp/floppy
run:
	qemu-system-i386 -drive file=myos.img,if=floppy
clean:
	rm bootloader myos.img haribote.bin
