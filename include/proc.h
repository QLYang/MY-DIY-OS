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
	STACK_FRAME regs;

	u16 ldt_sel;
	DESCRIPTOR ldts[LDT_SIZE];

	int ticks;		/*剩余的执行时间*/
	int priority;

	u32 pid;
	char name[16];

	int  p_flags;
	MESSAGE * p_msg;
	int p_recvfrom;
	int p_sendto;
	int has_int_msg;
	struct proc * q_sending;
	struct proc * next_sending;

	int nr_tty;
}PROCESS;

typedef struct task {
	task_f	initial_eip;
	int	stacksize;
	char	name[32];
}TASK;

#define proc2pid(x) (x - proc_table)

/* Number of tasks and procs*/
#define NR_TASKS	1
#define NR_PROCS	3

#define FIRST_PROC	proc_table[0]
#define LAST_PROC	proc_table[NR_TASKS + NR_PROCS - 1]
/* stacks of tasks */
#define STACK_SIZE_TESTA	0x8000
#define STACK_SIZE_TESTB	0x8000
#define STACK_SIZE_TESTC	0x8000
#define STACK_SIZE_TTY		0x8000

#define STACK_SIZE_TOTAL	STACK_SIZE_TESTA+STACK_SIZE_TESTB+STACK_SIZE_TESTC+STACK_SIZE_TTY