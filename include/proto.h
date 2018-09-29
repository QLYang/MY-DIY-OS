/* klib.asm */
PUBLIC 	void	out_byte(u16 port, u8 value);
PUBLIC 	void	disp_str(char * info);
PUBLIC 	u8		in_byte(u16 port);
PUBLIC	void*	memcpy(void* pDst, void* pSrc, int iSize);
PUBLIC	void	memset(void* p_dst, char ch, int size);
PUBLIC 	void 	enable_int();
PUBLIC 	void 	disable_int();

#define	phys_copy	memcpy
#define	phys_set	memset

/* klib.c */
PUBLIC char 	* itoa(char * str, int num);
PUBLIC void 	disp_int(int input);
PUBLIC void		delay(int time);
PUBLIC void 	clear();
PUBLIC int 		memcmp(const void * s1, const void *s2, int n);
PUBLIC int      strcmp(const char * s1, const char *s2);
/* protect.c */
PUBLIC void		init_prot();
PUBLIC u32		seg2phys(u16 seg);

/* kernel.asm */
void restart();

/* main.c */
void TestA();
void TestB();
void TestC();
PUBLIC int 		get_ticks();
PUBLIC void 	panic(const char *fmt, ...);

/*systask.c*/
PUBLIC void 	task_sys();

/* i8259.c */
PUBLIC void 	put_irq_handler(int irq, irq_handler handler);
PUBLIC void 	spurious_irq(int irq);

/* clock_interrupt.c */
PUBLIC void 	init_clock();

/* keyboard_interrupt.c */
PUBLIC void 	init_keyboard();
PUBLIC void 	keyboard_read();

/*proc.c*/
PUBLIC	void*	va2la(int pid, void* va);
PUBLIC	int		ldt_seg_linear(struct proc* p, int idx);
PUBLIC	void	reset_msg(MESSAGE* p);
PUBLIC	void	dump_msg(const char * title, MESSAGE* m);
PUBLIC	void	dump_proc(struct proc * p);
PUBLIC	int		send_recv(int function, int src_dest, MESSAGE* msg);
PUBLIC void 	inform_int(int task_nr);

/*syscall.asm*/
PUBLIC int 		get_ticks();
//PUBLIC void 	write(char* buf, int len);

/*tty.c*/
PUBLIC void 	task_tty();
PUBLIC void 	in_process(TTY* p_tty, u32 key);

/*console.c*/
PUBLIC void 	init_screen(TTY* p_tty);
PUBLIC void 	select_console(int nr_console);
PUBLIC void 	out_char(CONSOLE* p_con, char ch);
PUBLIC void 	scroll_screen(CONSOLE* p_con, int direction);

/* lib/printf.c */
PUBLIC  int     printf(const char *fmt, ...);
PUBLIC int 		printl(const char *fmt, ...);

/* vsprintf.c */
PUBLIC  int     vsprintf(char *buf, const char *fmt, va_list args);
PUBLIC	int		sprintf(char *buf, const char *fmt, ...);

/* lib/misc.c */
PUBLIC void 	spin(char * func_name);

/*hd.c*/
PUBLIC void		task_hd();
PUBLIC void 	hd_handler(int irq);

/* fs/main.c */
PUBLIC void 	task_fs();
PUBLIC int  	rw_sector(int io_type, int dev, u64 pos, int bytes, int proc_nr,void* buf);
PUBLIC struct 	inode * get_inode(int dev, int num);
PUBLIC void 	put_inode(struct inode * pinode);
PUBLIC void 	sync_inode(struct inode * p);

/*lib/open.c*/
PUBLIC int 		open(const char *pathname, int flags);

/*lib/close.c*/
PUBLIC int 		close(int fd);

/*fs/open.c*/
PUBLIC int 		do_open();
PUBLIC int 		do_close();

/*fs/misc.c*/
PUBLIC int 		search_file(char * path);
PUBLIC int 		strip_path(char * filename, const char * pathname,struct inode** ppinode);

/*fs/read_write.c*/
PUBLIC int 		do_rdwt();

/*lib/read.c*/
PUBLIC int 		read(int fd, void *buf, int count);

/*lib/write.c*/
PUBLIC int 		write(int fd, const void *buf, int count);

/* fs/disklog.c */
PUBLIC int		do_disklog();
PUBLIC int		disklog(char * logstr); /* for debug */
PUBLIC void		dump_fd_graph(const char * fmt, ...);

/*fs/link.c*/
PUBLIC int 		do_unlink();

/*lib/unlink.c*/
PUBLIC int 		unlink(const char * pathname);

/*lib/getpid.c*/
PUBLIC int 		getpid();

/*lib/syslog.c*/
PUBLIC int 		syslog(const char *fmt, ...);



/* -------------------系统调用 - 系统级 ------------------------------------*/
/* proc.c */
PUBLIC	int		sys_sendrec(int function, int src_dest, MESSAGE* m, struct proc* p);
PUBLIC	int		sys_printx(int _unused1, int _unused2, char* s, struct proc * p_proc);

/* syscall.asm */
PUBLIC  void    sys_call();             /* int_handler */

/*------------------- 系统调用 - 用户级 --------------------------------------*/
PUBLIC	int		sendrec(int function, int src_dest, MESSAGE* p_msg);
PUBLIC	int		printx(char* str);