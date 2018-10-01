typedef struct s_stackframe {/*一系列寄存器的值组成一个栈帧*/
	u32	gs;
	u32	fs;
	u32	es;
	u32	ds;
	u32	edi;
	u32	esi;
	u32	ebp;
	u32	kernel_esp;
	u32	ebx;
	u32	edx;
	u32	ecx;
	u32	eax;
	u32	retaddr;
	u32	eip;
	u32	cs;
	u32	eflags;
	u32	esp;
	u32	ss;
}STACK_FRAME;


typedef struct proc {/*保存进程相关信息*/
	STACK_FRAME 		regs;

	u16 				ldt_sel;
	DESCRIPTOR 			ldts[LDT_SIZE];

	int 				ticks;		/*剩余的执行时间*/
	int 				priority;

	u32 				pid;
	char 				name[16];
	/*msg*/
	int  				p_flags;
	MESSAGE * 			p_msg;
	int 				p_recvfrom;
	int 				p_sendto;
	int 				has_int_msg;
	struct proc * 		q_sending;
	struct proc * 		next_sending;
	/*file descriptor*/
	struct file_desc * 	filp[NR_FILES];

	int 				p_parent; /**< pid of parent process */
	int 				exit_status; /**< for parent */
}PROCESS;

typedef struct task {
	task_f				initial_eip;
	int					stacksize;
	char				name[32];
}TASK;

#define proc2pid(x) (x - proc_table)

/* Number of tasks and procs*/
#define NR_TASKS			5
#define NR_PROCS			32
#define NR_NATIVE_PROCS 	4

#define FIRST_PROC	proc_table[0]
#define LAST_PROC	proc_table[NR_TASKS + NR_PROCS - 1]
/* stacks of tasks */
#define	STACK_SIZE_DEFAULT	0x4000 /* 16 KB */

#define STACK_SIZE_INIT		STACK_SIZE_DEFAULT
#define STACK_SIZE_TESTA	STACK_SIZE_DEFAULT
#define STACK_SIZE_TESTB	STACK_SIZE_DEFAULT
#define STACK_SIZE_TESTC	STACK_SIZE_DEFAULT

#define STACK_SIZE_TTY		STACK_SIZE_DEFAULT
#define STACK_SIZE_SYS		STACK_SIZE_DEFAULT
#define STACK_SIZE_HD		STACK_SIZE_DEFAULT
#define STACK_SIZE_FS		STACK_SIZE_DEFAULT
#define STACK_SIZE_MM		STACK_SIZE_DEFAULT

#define STACK_SIZE_TOTAL	(STACK_SIZE_MM+STACK_SIZE_INIT+STACK_SIZE_TESTA+STACK_SIZE_TESTB+STACK_SIZE_TESTC+STACK_SIZE_TTY+ \
STACK_SIZE_SYS+STACK_SIZE_HD+STACK_SIZE_FS)

/**
 * All forked proc will use memory above PROCS_BASE.
 *
 */
#define	PROCS_BASE				0xA00000 /* 10 MB */
#define	PROC_IMAGE_SIZE_DEFAULT	0x100000 /*  1 MB */
#define	PROC_ORIGIN_STACK		0x400    /*  1 KB */