BaseOfLoader	equ	09000h
OffsetOfLoader	equ 0100h

BaseOfLoaderPhyAddr	equ	BaseOfLoader*10h

BaseOfKernelFile	equ	08000h
OffsetOfKernelFile	equ 0h

BaseOfKernelFilePhyAddr	equ	BaseOfKernelFile * 10h
KernelEntryPointPhyAddr	equ	030400h 	;Remember to change the flag while ld!

PageDirBase		equ	100000h	; 页目录开始地址:		2M
PageTblBase		equ	101000h	; 页表开始地址:			2M + 4K