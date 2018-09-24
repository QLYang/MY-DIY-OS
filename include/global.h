/* EXTERN is defined as extern except in global.c */
#ifdef	GLOBAL_VARIABLES_HERE
#undef	EXTERN
#define	EXTERN
#endif

/*protect*/
EXTERN	int			disp_pos;
EXTERN	u8			gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
EXTERN	DESCRIPTOR	gdt[GDT_SIZE];
EXTERN	u8			idt_ptr[6];	/* 0~15:Limit  16~47:Base */
EXTERN	GATE		idt[IDT_SIZE];
/*proc*/
EXTERN	TSS			tss;
EXTERN	PROCESS*	p_proc_ready;

extern	PROCESS		proc_table[];
extern	char		task_stack[];

extern	TASK		task_table[];
extern  TASK        user_proc_table[];

EXTERN  u32 		kernel_reenter;
extern	irq_handler irq_table[];
/*get ticks*/
EXTERN  int			ticks;

/*tty console*/
extern	TTY			tty_table[];
extern  CONSOLE         console_table[];
EXTERN	int			nr_current_console;

/* FS */
extern	struct 			dev_drv_map	dd_map[];
extern	const int		FSBUF_SIZE;
extern	u8 *			fsbuf;