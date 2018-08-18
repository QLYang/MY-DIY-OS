#Source
src1=boot/boot.asm
src2=boot/loader.asm
src3=kernel/kernel.asm
src4=lib/k_lib.asm
src5=kernel/start.c
src6=kernel/init8259A.c
src7=kernel/global.c
src8=kernel/protect.c
src9=lib/k_liba.c
src10=kernel/main.c
src11=kernel/clock_interrupt.c
src12=kernel/syscall.asm
src13=kernel/proc.c

src=$(src1) $(src2) $(src3) $(src4) $(src5) $(src6) $(src7) $(src8) $(src9) $(src10) $(src11) $(src12) $(src13)
#Target
debug_tar1=boot.com
debug_tar2=loader.bin
debug_tar=$(debug_tar1) $(debug_tar2)
#flag
gcc-flag=-m32 -fno-builtin -I include -Wno-implicit-function-declaration \
	-Wno-int-conversion -fno-stack-protector
nasm-flag=-I boot/include/
#target
tar1=boot.bin
tar2=loader.bin
tar3=kernel.bin
tar= $(tar1) $(tar2) $(tar3)
#Floppy
img=a.img
#Command
.PHONY:all debug evething clean

all:evething clean

clean:
	sudo rm -f *.bin *.o

debug:$(src)
	#boot.asm
	nasm $(src1) -o $(debug_tar1)
	sudo mount -o loop $(img) /mnt/floppy/
	sudo cp $(debug_tar1) /mnt/floppy/ -v
	sudo umount /mnt/floppy/
	#loader
	nasm $(src2) -o $(debug_tar2)
	sudo mount -o loop $(img) /mnt/floppy/
	sudo cp $(debug_tar2) /mnt/floppy/ -v
	sudo umount /mnt/floppy/
	#clean
	sudo rm -f $(debug_tar)

#must add ';' before define! Change bochsrc
evething:$(src)
	#boot.asm
	nasm  $(nasm-flag) $(src1) -o $(tar1)
	dd if=$(tar1) of=$(img) bs=512 count=1 conv=notrunc

	#loader.asm
	nasm $(nasm-flag) $(src2) -o $(tar2)
	sudo mount -o loop $(img) /mnt/floppy/
	sudo cp $(tar2) /mnt/floppy/ -v
	sudo umount /mnt/floppy/

	#kernel.asm
	nasm $(nasm-flag) -f elf $(src3) -o kernel.o
	nasm $(nasm-flag) -f elf $(src4) -o k_lib.o

	gcc $(gcc-flag) -c $(src5) -o start.o #compile in i386 arch
	gcc $(gcc-flag) -c $(src6) -o init8259A.o
	gcc $(gcc-flag) -c $(src7) -o global.o
	gcc $(gcc-flag) -c $(src8) -o protect.o
	gcc $(gcc-flag) -c $(src9) -o k_liba.o
	gcc $(gcc-flag) -c $(src10) -o main.o
	gcc $(gcc-flag) -c $(src11) -o clock_interrupt.o
	nasm $(nasm-flag) -f elf $(src12) -o syscall.o
	gcc $(gcc-flag) -c $(src13) -o proc.o

	ld -s -Ttext 0x30400 -m elf_i386 kernel.o k_lib.o start.o init8259A.o \
	global.o k_liba.o protect.o main.o clock_interrupt.o syscall.o proc.o \
	-o $(tar3)

	sudo mount -o loop $(img) /mnt/floppy/
	sudo cp $(tar3) /mnt/floppy/ -v
	sudo umount /mnt/floppy/