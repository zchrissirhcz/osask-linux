#include <mmu.h>

# Start the CPU: switch to 32-bit protected mode, jump into C.
# The BIOS loads this code from the first sector of the hard disk into
# memory at physical address 0x7c00 and starts executing in real mode
# with %cs=0 %ip=7c00.
#define CYLS			0x0ff0			
#define LEDS			0x0ff1
#define VMODE			0x0ff2			
#define SCRNX			0x0ff4			
#define SCRNY			0x0ff6			
#define VRAM			0x0ff8	


#define BOTPAK 			0X00280000
#define DSKCAC 			0x00100000
#define DSKCAC0			0X00008000 


.set CR0_PE_ON,      0x1         # protected mode enable flag

.globl entry
entry:
  .code16                     # Assemble for 16-bit mode
  
  jmp start

  msg:
  .asciz "\r\n\n\rmy kernel is runing jos"
  
 try:
  .asciz "\r\n\n\rtry it again"

puts:

	movb (%si),%al
	add $1,%si
	cmp $0,%al
	je over
	movb $0x0e,%ah
	movw $15,%bx
	int $0x10
	jmp puts
over:
	ret
start:
 # Set up the important data segment registers (DS, ES, SS).
  xorw    %ax,%ax             # Segment number zero
  movw    %ax,%ds             # -> Data Segment
  movw    %ax,%es             # -> Extra Segment
  movw    %ax,%ss             # -> Stack Segment
 
#################### # 利用中断int 0x10来改变显示模式
  movb $0x13,%al  # ;vga 320x200x8 位,color mode 
  movb $0x00,%ah  
   int $0x10   
#save color mode in ram 0x0ff0
 movb  $10,(CYLS)
 movb $8,(VMODE)
 movw $320,(SCRNX)
 movw $200,(SCRNY)
 movl $0x000a0000,(VRAM)

 #get keyboard led status
 movb	$0x02,%ah 
 int     $0x16			#keyboard interrupts
 movb   %al,(LEDS)		
#diplay "my kernel is runing jos"
  movw $msg,%si
  call puts
  

#这一部分在做什么也不知道，先翻译成at&t格式再说：
  movb $0xff,%al
  outb %al, $0x21 #format  outb data port
  nop
  out %al, $0xa1
  #jmp .
   cli                         # Disable interrupts
  # cld                         # String operations increment

  # Enable A20:
  #   For backwards compatibility with the earliest PCs, physical
  #   address line 20 is tied low, so that addresses higher than
  #   1MB wrap around to zero by default.  This code undoes this. 
seta20.1:
  inb     $0x64,%al               # Wait for not busy
  testb   $0x2,%al   #if 1 :busy ,if 0:idle
  jnz     seta20.1
#对port 0x64  写0xd1
  movb    $0xd1,%al               # 0xd1 -> port 0x64
  outb    %al,$0x64
seta20.2:
  inb     $0x64,%al               # Wait for not busy
  testb   $02,%al
  jnz     seta20.2
#对port 0x60 写0xdf
  movb    $0xdf,%al               # 0xdf -> port 0x60
  outb    %al,$0x60 
#通过对上面的Port的操作，实现enable A20
  # Switch from real to protected mode, using a bootstrap GDT       this is vip ,but i don`t know it clearly now
  # and segment translation that makes virtual addresses 
  # identical to their physical addresses, so that the 
  # effective memory map does not change during the switch.
  movw $msg,%si
  call puts
  
  #jmp .
  lgdt     gdtdesc
  movl     %cr0, %eax
  andl     $0x7fffffff,%eax
  orl      $CR0_PE_ON, %eax  #CR0_PE_ON=0x1 
  movl     %eax, %cr0  
  #这个地方非常的重要，一但这条movl %eax,%cr0把cr0的pe位打开后，下面的
  #代码就是32位的，所以空上ljmp的指令是条过度指令，选择 用的gdt是1*8,
  #也就是第一个gdt(从0开始的)。

  # Jump to next instruction, but in 32-bit code segment.
  # Switches processor into 32-bit mode.  这一个跳转的意义重大
  ljmp    $(1*8), $protcseg #PROT_MODE_CSEG=0x8 #32位的跳转指令。 ljmp selector ,offset
	
#######################################################################
#正式进入32位的保护模式。	
	
  .code32                     # Assemble for 32-bit mode
protcseg:
  # Set up the protected-mode data segment registers
 # movw    $PROT_MODE_DSEG, %ax    # Our data segment selector

  movw    $(3*8) , %ax
  movw    %ax, %ds                # -> DS: Data Segment  //vip
  movw    %ax, %es                # -> ES: Extra Segment
  movw    %ax, %fs                # -> FS
  movw    %ax, %gs                # -> GS
  movw    %ax, %ss                # -> SS: Stack Segment

  # Set up the stack pointer and call into C.
  movl    $start, %esp
  #call bootmain
  
ccode: 
  #把c代码部分复制到其它的memory的地址  1024个扇区的内容
  #memcopy(bootmain,BOTPAK,size=512*1024/4);#BOTPAK =0X00280000
  movl $main, %esi
  movl $BOTPAK  , %edi
  movl $(512*1024/4),%ecx
  call memcpy
  #ljmp   $(2*8),$0x0000
bootsector:  
 #把bootsector的内容复制到 0x100000的位置  
  movl $0x7c00, %esi
  movl $DSKCAC , %edi  # DSKCAC=0x00100000 把bootsector的内容复制到0x100000地址处
  movl $(512/4),%ecx
  call memcpy
all:
#把整个软盘上的内容复制到 0x100000内存地址处
  movl $(DSKCAC0+512), %esi
  movl $(DSKCAC+512) , %edi  # 
  movl $0,%ecx
  movb (CYLS),%cl
  imul $(512*18*2/4) , %ecx
  subl  $(512/4),       %ecx
  call memcpy
  
  
#下面的这部分不明白，先不管了   这 一部分还真有可能是bootpack的头文件。  这一部分是小日本自己写的一个header,用了小日本自己的工具，所以我没有要这个header
  #movl $BOTPAK ,%ebx  ；ebx=0x280000
  #movl 16(%ebx),%ecx    ecx= int (*0x280010) 跳过16个字节
  #addl  $3     ,%ecx    ecx=ecx+3
  #shr   $2     ,%ecx    ecx=ecx/4   ecx中放的是c部分代码的大小
  #jz   skip
  #movl 20(%ebx),%esi
 #addl %ebx    ,%esi
  #movl 12(%ebx),%edi
 # call memcpy  
  
#skip:
 # movl 12(%ebx),%esp

 ljmp  $(2*8), $0x00000000
 #ljmp  $(1*8), $main


memcpy:
  movl  (%esi),%eax
  addl  $4    ,%esi
  movl  %eax ,(%edi)
  addl   $4    ,%edi
  subl   $1    ,%ecx
  jnz    memcpy
  ret
  
  
  # If bootmain returns (it shouldn't), loop.



# Bootstrap GDT
.p2align 2                               # force 4 byte alignment
gdt:
  SEG_NULL				 # null seg  0
  SEG(STA_X|STA_R, 0x0000, 0xffffffff)   # entry.S code selector 1
  SEG(STA_X|STA_R, 0x280000, 0xffffffff) # main.c  code selector 2
  SEG(STA_W ,0x000000, 0xffffffff)	 # entry.S main.c data selector 3
  
gdtdesc:
  .word   31         #4*8-1                 # sizeof(gdt) - 1
  .long   gdt                             # address gdt
main:
#spin:
#  jmp spin
#.fill 310