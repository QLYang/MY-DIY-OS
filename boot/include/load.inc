BaseOfLoader	equ	09000h
OffsetOfLoader	equ 0100h

BaseOfLoaderPhyAddr	equ	BaseOfLoader*10h

BaseOfKernelFile	equ	07000h
OffsetOfKernelFile	equ 0h

BaseOfKernelFilePhyAddr	equ	BaseOfKernelFile * 10h
KernelEntryPointPhyAddr	equ	0x1000 	;Remember to change the flag while ld!

PageDirBase		equ	100000h	; 页目录开始地址:			2M
PageTblBase		equ	101000h	; 页表开始地址:			2M + 4K

;;     Macros below should corresponding with C source.
BOOT_PARAM_ADDR		equ	0x900
BOOT_PARAM_MAGIC	equ	0xB007

;; we don't calculate the base sector nr of the root device while loading
;; but define it as a macro for two reasons:
;; 1. it is a constant for any certain system
;; 2. it simplifies boot sector and loader
ROOT_BASE		equ	0x56C0