/* EXTERN is defined as extern except in global.c */
#ifdef	GLOBAL_VARIABLES_HERE
#undef	EXTERN
#define	EXTERN
#endif

/*protect*/
EXTERN	int					disp_pos;
EXTERN	u8					gdt_ptr[6];	/* 0~15:Limit  16~47:Base */
EXTERN	DESCRIPTOR			gdt[GDT_SIZE];
EXTERN	u8					idt_ptr[6];	/* 0~15:Limit  16~47:Base */
EXTERN	GATE				idt[IDT_SIZE];
/*proc*/
EXTERN	TSS					tss;
EXTERN	PROCESS*			p_proc_ready;

extern	PROCESS				proc_table[];
extern	char				task_stack[];

extern	TASK				task_table[];
extern  TASK        		user_proc_table[];

EXTERN  u32 				kernel_reenter;
extern	irq_handler 		irq_table[];
/*get ticks*/
EXTERN  int					ticks;

/*tty console*/
extern	TTY					tty_table[];
extern  CONSOLE         	console_table[];
EXTERN	int					nr_current_console;

/* FS */
extern	struct 				dev_drv_map	dd_map[];
extern	const int			FSBUF_SIZE;
extern	u8 *				fsbuf;

EXTERN	struct file_desc	f_desc_table[NR_FILE_DESC];
EXTERN	struct inode		inode_table[NR_INODE];
EXTERN	struct super_block	super_block[NR_SUPER_BLOCK];

EXTERN	MESSAGE				fs_msg;
EXTERN	struct proc *		pcaller;
EXTERN	struct inode *		root_inode;

EXTERN	int	key_pressed; /**
			      			* used for clock_handler
			      			* to wake up TASK_TTY when
			      			* a key is pressed
			      			*/
/* MM */
EXTERN	MESSAGE				mm_msg;
extern	u8 *				mmbuf;
extern	const int			MMBUF_SIZE;
EXTERN	int					memory_size;