/* klib.asm */
PUBLIC void	out_byte(u16 port, u8 value);
PUBLIC void	disp_str(char * info);
PUBLIC u8	in_byte(u16 port);
PUBLIC	void*	memcpy(void* pDst, void* pSrc, int iSize);