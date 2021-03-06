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
src11=kernel/clock_interruption.c
src12=kernel/syscall.asm
src13=kernel/proc.c
src14=kernel/keyboard_interruption.c
src15=kernel/tty.c
src16=kernel/console.c
src17=lib/printf.c
src18=kernel/vsprintf.c
src19=lib/misc.c
src20=kernel/systask.c
src21=kernel/hd.c
src22=fs/main.c
src23=fs/misc.c
src24=fs/open.c
src25=lib/open.c
src26=lib/close.c
src27=fs/read_write.c
src28=lib/read.c
src29=lib/write.c
src30=lib/getpid.c
src31=lib/syslog.c
src32=fs/disklog.c
src33=fs/link.c
src34=lib/unlink.c
src35=lib/fork.c
src36=mm/main.c
src37=mm/forkexit.c
src38=lib/exit.c
src39=lib/wait.c
src40=lib/exec.c
src41=mm/exec.c
src42=lib/stat.c
src43=lib/lseek.c

src=$(src1) $(src2) $(src3) $(src4) $(src5) $(src6) $(src7) $(src8) $(src9) $(src10) $(src11) $(src12) $(src13) $(src14) \
	$(src15) $(src16) $(src17) $(src18) $(src19) $(src20) $(src21) $(src22) $(src23) $(src24) $(src25) $(src26) \
	$(src27) $(src28) $(src29) $(src30) $(src31) $(src32) $(src33) $(src34) $(src35) $(src36) $(src37) $(src38) \
	$(src39) $(src40) $(src41) $(src42) $(src43)
#Entry Point
ENTRY_POINT=0x1000
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
.PHONY:all evething clean del_debug_file make_runtime realclean
#Normal Option
all:evething realclean

#Make runtime lib
make_runtime:evething runtime realclean

#Only keep kernel.bin
get_kernel_bin:evething clean

#keep .bin
clean:
	sudo rm -f *.o boot.bin loader.bin
realclean:
	sudo rm -f *.o *.bin
#File system debug
del_debug_file:
	sudo rm -f *.png *.dot llsyslog

#Make a runtime lib
runtime:
	ar rcs lib/c_runtime.a syscall.o lib_close.o lib_exit.o  lib_fork.o lib_getpid.o \
	lib_open.o lib_printf.o lib_read.o lib_unlink.o lib_wait.o lib_write.o \
	lib_misc.o k_lib.o k_liba.o vsprintf.o lib_exec.o lib_stat.o lib_lseek.o

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
	gcc $(gcc-flag) -c $(src11) -o clock_interruption.o
	nasm $(nasm-flag) -f elf $(src12) -o syscall.o
	gcc $(gcc-flag) -c $(src13) -o proc.o
	gcc $(gcc-flag) -c $(src14) -o keyboard_interruption.o
	gcc $(gcc-flag) -c $(src15) -o tty.o
	gcc $(gcc-flag) -c $(src16) -o console.o
	gcc $(gcc-flag) -c $(src17) -o lib_printf.o
	gcc $(gcc-flag) -c $(src18) -o vsprintf.o
	gcc $(gcc-flag) -c $(src19) -o lib_misc.o
	gcc $(gcc-flag) -c $(src20) -o systask.o
	gcc $(gcc-flag) -c $(src21) -o hd.o
	gcc $(gcc-flag) -c $(src22) -o fs_main.o
	gcc $(gcc-flag) -c $(src23) -o fs_misc.o
	gcc $(gcc-flag) -c $(src24) -o fs_open.o
	gcc $(gcc-flag) -c $(src25) -o lib_open.o
	gcc $(gcc-flag) -c $(src26) -o lib_close.o
	gcc $(gcc-flag) -c $(src27) -o fs_read_write.o
	gcc $(gcc-flag) -c $(src28) -o lib_read.o
	gcc $(gcc-flag) -c $(src29) -o lib_write.o
	gcc $(gcc-flag) -c $(src30) -o lib_getpid.o
	gcc $(gcc-flag) -c $(src31) -o lib_syslog.o
	gcc $(gcc-flag) -c $(src32) -o fs_disklog.o
	gcc $(gcc-flag) -c $(src33) -o fs_link.o
	gcc $(gcc-flag) -c $(src34) -o lib_unlink.o
	gcc $(gcc-flag) -c $(src35) -o lib_fork.o
	gcc $(gcc-flag) -c $(src36) -o mm_main.o
	gcc $(gcc-flag) -c $(src37) -o mm_forkexit.o
	gcc $(gcc-flag) -c $(src38) -o lib_exit.o
	gcc $(gcc-flag) -c $(src39) -o lib_wait.o
	gcc $(gcc-flag) -c $(src40) -o lib_exec.o
	gcc $(gcc-flag) -c $(src41) -o mm_exec.o
	gcc $(gcc-flag) -c $(src42) -o lib_stat.o
	gcc $(gcc-flag) -c $(src43) -o lib_lseek.o

	ld -s -Ttext $(ENTRY_POINT) -m elf_i386 kernel.o k_lib.o start.o init8259A.o \
	global.o k_liba.o protect.o main.o clock_interruption.o syscall.o proc.o \
	 keyboard_interruption.o tty.o  console.o lib_printf.o vsprintf.o lib_misc.o \
	 systask.o hd.o fs_main.o fs_misc.o fs_open.o lib_open.o lib_close.o \
	 fs_read_write.o lib_read.o lib_write.o lib_getpid.o lib_syslog.o fs_disklog.o \
	 fs_link.o lib_unlink.o lib_fork.o mm_main.o mm_forkexit.o lib_exit.o lib_wait.o \
	 lib_exec.o mm_exec.o lib_stat.o lib_lseek.o -o $(tar3)

	sudo mount -o loop $(img) /mnt/floppy/
	sudo cp $(tar3) /mnt/floppy/ -v
	sudo umount /mnt/floppy/