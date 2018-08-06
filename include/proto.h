/* klib.asm */
PUBLIC void	out_byte(u16 port, u8 value);
PUBLIC void	disp_str(char * info);
PUBLIC u8	in_byte(u16 port);
PUBLIC	void*	memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC	void	memset(void* p_dst, char ch, int size);
/* klib.c */
PUBLIC void	delay(int time);

/* protect.c */
PUBLIC void	init_prot();
PUBLIC u32	seg2phys(u16 seg);

/* kernel.asm */
void restart();

/* main.c */
void TestA();