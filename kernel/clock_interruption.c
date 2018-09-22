#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "hd.h"
#include "fs.h"
#include "global.h"
#include "proto.h"

PUBLIC void clock_handler(int irq){
	ticks++;
	p_proc_ready->ticks--;

	if (kernel_reenter!=0){
		return;
	}
	if (p_proc_ready->ticks>0){/*在当前进程的ticks减到0之前，其他进程没有执行机会*/
		return;
	}
	schedule();
}

PUBLIC void init_clock(){
	put_irq_handler(CLOCK_IRQ, clock_handler); /* 设定时钟中断处理程序 */
    enable_irq(CLOCK_IRQ);
}