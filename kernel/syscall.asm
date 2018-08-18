%include "include/sconst.inc"

_NR_get_ticks       equ 0 ;sys_call_table的索引
INT_VECTOR_SYS_CALL equ 0x90

global	get_ticks

bits 32
[section .text]

;======================================
;			get_ticks
;======================================
get_ticks:
	mov	eax, _NR_get_ticks
	int	INT_VECTOR_SYS_CALL
	ret