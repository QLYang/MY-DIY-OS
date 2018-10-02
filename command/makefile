src1=echo.c
src2=start.asm
src3=../lib/c_runtime.a

src=$(src1) $(src2) $(src3)

gcc_flag=-m32 -fno-builtin -I ../include/ -Wno-implicit-function-declaration \
	-Wno-int-conversion -fno-stack-protector -Wall -c
nasm_flag=-I ../include/ -f elf
ENTRY_POINT=0x1000

ld_flag=-Ttext $(ENTRY_POINT) -m elf_i386

.PHONY:all evething clean

all:evething clean

evething:$(src)
	gcc $(gcc_flag) -o echo.o $(src1)
	nasm $(nasm_flag) -o start.o start.asm
	ld $(ld_flag) -o echo echo.o start.o $(src3)

clean:
	sudo rm -f *.o