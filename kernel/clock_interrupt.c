#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"

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