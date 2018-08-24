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
PUBLIC void init_clock();

/* keyboard_interrupt.c */
PUBLIC void init_keyboard();
PUBLIC void keyboard_read();

/*proc.c*/
PUBLIC int sys_get_ticks();
PUBLIC void sys_call();
PUBLIC int sys_write(char* buf, int len, PROCESS* p_proc);

/*syscall.asm*/
PUBLIC int get_ticks();
PUBLIC void write(char* buf, int len);
/*tty.c*/
PUBLIC void task_tty();
PUBLIC void in_process(TTY* p_tty,u32 key);
PUBLIC void tty_write(TTY* p_tty, char* buf, int len);
PUBLIC int sys_write(char* buf, int len, PROCESS* p_proc);
/*console.c*/
PUBLIC void init_screen(TTY* p_tty);
PUBLIC void select_console(int nr_console);
PUBLIC void out_char(CONSOLE* p_con, char ch);
PUBLIC void scroll_screen(CONSOLE* p_con, int direction);
/* printf.c */
PUBLIC  int     printf(const char *fmt, ...);
/* vsprintf.c */
PUBLIC  int     vsprintf(char *buf, const char *fmt, va_list args);