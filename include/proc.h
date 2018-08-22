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


typedef struct s_proc {/*保存进程相关信息*/
	STACK_FRAME regs;

	u16 ldt_sel;
	DESCRIPTOR ldts[LDT_SIZE];

	int ticks;		/*剩余的执行时间*/
	int priority;

	u32 pid;
	char p_name[16];
}PROCESS;

typedef struct s_task {
	task_f	initial_eip;
	int	stacksize;
	char	name[32];
}TASK;

/* Number of tasks */
#define NR_TASKS	4

/* stacks of tasks */
#define STACK_SIZE_TESTA	0x8000
#define STACK_SIZE_TESTB	0x8000
#define STACK_SIZE_TESTC	0x8000
#define STACK_SIZE_TTY		0x8000

#define STACK_SIZE_TOTAL	STACK_SIZE_TESTA+STACK_SIZE_TESTB+STACK_SIZE_TESTC+STACK_SIZE_TTY