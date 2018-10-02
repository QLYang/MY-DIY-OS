src1=echo.c
src2=start.asm
src3=../lib/c_runtime.a
src4=pwd.c

src=$(src1) $(src2) $(src3) $(src4)
#hd
HD= ../80m.img
#flag
gcc_flag=-m32 -fno-builtin -I ../include/ -Wno-implicit-function-declaration \
	-Wno-int-conversion -fno-stack-protector -Wall -c
nasm_flag=-I ../include/ -f elf
ld_flag=-Ttext $(ENTRY_POINT) -m elf_i386
ENTRY_POINT=0x1000

#Command
.PHONY:all evething clean

all:evething clean

evething:$(src)
	#echo
	gcc $(gcc_flag) -o echo.o $(src1)
	nasm $(nasm_flag) -o start.o start.asm
	ld $(ld_flag) -o echo echo.o start.o $(src3)
	#pwd
	gcc $(gcc_flag) -o pwd.o $(src4)
	nasm $(nasm_flag) -o start.o $(src2)
	ld $(ld_flag) -o pwd pwd.o start.o $(src3)
	#kernel.bin
	cp ../kernel.bin ./ -v
	#make .tar
	tar vcf inst.tar kernel.bin pwd echo
	#write into hd
	dd if=inst.tar of=$(HD) seek=`echo "obase=10;ibase=16;(\`egrep -e '^ROOT_BASE' ../boot/include/load.inc | sed -e 's/.*0x//g'\`+\`egrep -e '#define[[:space:]]*INSTALL_START_SECT' ../include/config.h | sed -e 's/.*0x//g'\`)*200" | bc` bs=1 count=`ls -l inst.tar | awk -F " " '{print $$5}'` conv=notrunc
clean:
	sudo rm -f *.o *.tar *.bin