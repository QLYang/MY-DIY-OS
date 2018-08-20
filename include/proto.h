/* klib.asm */
PUBLIC 	void	out_byte(u16 port, u8 value);
PUBLIC 	void	disp_str(char * info);
PUBLIC 	u8		in_byte(u16 port);
PUBLIC	void*	memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC	void	memset(void* p_dst, char ch, int size);
PUBLIC 	void 	enable_int();
PUBLIC 	void 	disable_int();

/* klib.c */
PUBLIC void	delay(int time);
PUBLIC void clear();

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
PUBLIC void init_keyboard_handler();
PUBLIC void keyboard_read();

/*proc.c*/
PUBLIC int sys_get_ticks();
PUBLIC void sys_call();

/*syscall.asm*/
PUBLIC int get_ticks();

/*tty.c*/
PUBLIC void tty();
PUBLIC void in_process(u32 key);