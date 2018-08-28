#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"


/*======================================================================*
                            kernel_main
 *======================================================================*/
PUBLIC int kernel_main()
{
	clear();/*清屏*/
	disp_str("-----\"kernel_main\" begins-----\n");
	TASK*		p_task= task_table;
	PROCESS*	p_proc= proc_table;
	char*		p_task_stack= task_stack + STACK_SIZE_TOTAL;
	u16		selector_ldt= SELECTOR_LDT_FIRST;
	int i;
    u8      privilege;
    u8      rpl;
    int     eflags;
	for (i = 0; i < NR_TASKS+NR_PROCS; i++) {
    	if (i < NR_TASKS) {     /* 任务 */
        	p_task    = task_table + i;
            privilege = PRIVILEGE_TASK;
            rpl       = RPL_TASK;
            eflags    = 0x1202; /* IF=1, IOPL=1, bit 2 is always 1 */
        }
        else {                  /* 用户进程 */
            p_task    = user_proc_table + (i - NR_TASKS);
            privilege = PRIVILEGE_USER;
            rpl       = RPL_USER;
            eflags    = 0x202; /* IF=1, bit 2 is always 1 */
            }

		strcpy(p_proc->name, p_task->name);	// name of the process
		p_proc->pid = i;			// pid

		p_proc->ldt_sel = selector_ldt;

		memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3],
		   	sizeof(DESCRIPTOR));
		p_proc->ldts[0].attr1 = DA_C | privilege << 5;
		memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3],
		   	sizeof(DESCRIPTOR));
		p_proc->ldts[1].attr1 = DA_DRW | privilege << 5;
		p_proc->regs.cs	= (0 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ds	= (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.es	= (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.fs	= (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ss	= (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.gs	= (SELECTOR_KERNEL_GS & SA_RPL_MASK) | rpl;

		p_proc->regs.eip = (u32)p_task->initial_eip;
		p_proc->regs.esp = (u32)p_task_stack;
		p_proc->regs.eflags = eflags;

		p_proc->nr_tty = 0;

		p_task_stack -= p_task->stacksize;
		p_proc++;
		p_task++;
		selector_ldt += 1 << 3;
	}
	proc_table[0].ticks=proc_table[0].priority=15;/*tty_task*/
	proc_table[1].ticks=proc_table[1].priority=5;/*task_x*/
	proc_table[2].ticks=proc_table[2].priority=5;
	proc_table[3].ticks=proc_table[3].priority=5;

	proc_table[1].nr_tty = 0;/*task_x*/
    proc_table[2].nr_tty = 1;
    proc_table[3].nr_tty = 1;

	kernel_reenter = 0;
	ticks = 0;

	p_proc_ready= proc_table;

	init_clock();/*初始化时钟中断*/
	init_keyboard();/*初始化键盘中断*/
	restart();

	while(1){}
}

/*======================================================================*
                               TestA
 *======================================================================*/
void TestA()
{
	while(1){
		int i = 0;
		printf("A");
		delay(1);

	}
}
/*======================================================================*
                               TestB
 *======================================================================*/
void TestB()
{
	while(1){
		int i = 0x1000;
		printf("B");
		delay(1);
	}
}
/*======================================================================*
                               TestC
 *======================================================================*/
void TestC()
{
	while(1){
		printf("C");
		delay(1);
	}
}

/*======================================================================*
                                panic
 *======================================================================*/
PUBLIC void panic(const char *fmt, ...)
{
	int i;
	char buf[256];

	va_list arg = (va_list)((char*)&fmt + 4);

	i = vsprintf(buf, fmt, arg);

	printl("%c !!panic!! %s", MAG_CH_PANIC, buf);

	/* should never arrive here */
	__asm__ __volatile__("ud2");
}