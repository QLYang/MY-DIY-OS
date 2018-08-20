/* klib.asm */
PUBLIC void	out_byte(u16 port, u8 value);
PUBLIC void	disp_str(char * info);
PUBLIC u8	in_byte(u16 port);
PUBLIC	void*	memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC	void	memset(void* p_dst, char ch, int size);
PUBLIC
/* klib.c */
PUBLIC void	delay(int time);

/* protect.c */
PUBLIC void	init_prot();
PUBLIC u32	seg2phys(u16 seg);

/* kernel.asm */
void restart();

/* main.c */
void TestA();
void TestB();
void TestC();

/* i8259.c */
PUBLIC void put_irq_handler(int irq, irq_handler handler);
PUBLIC void spurious_irq(int irq);

/* clock_interrupt.c */
PUBLIC void init_clock_handler();
/* keyboard_interrupt.c */
/*proc.c*/
PUBLIC int sys_get_ticks();
PUBLIC void sys_call();
/*syscall.asm*/
PUBLIC int get_ticks();
