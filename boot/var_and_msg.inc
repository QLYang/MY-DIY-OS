;======================================
;				Useless
;======================================
;--------------------------------------
;Message
message: db "hello"
len equ $-message

MessageLength		equ	9
BootMessage:		db	"Booting  "; 9字节, 不够则用空格补齐. 序号 0
Message1:		db	"Ready    "; 9字节, 不够则用空格补齐. 序号 1
Message2:		db	"No LOADER"; 9字节, 不够则用空格补齐. 序号 2

;--------------------------------------
;变量
BaseOfLoader		equ	09000h	; LOADER.BIN 被加载到的位置 ----  段地址
OffsetOfLoader		equ	0100h	; LOADER.BIN 被加载到的位置 ---- 偏移地址
LoaderFileName		db	"LOADER  BIN", 0 ; LOADER.BIN 之文件名
bOdd			db	0		; 奇数还是偶数

;--------------------------------------
;Stack
%ifdef __debug__
BaseOfStack equ 0100h
%else
BaseOfStack equ 07c00h
%endif
