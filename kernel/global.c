#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "proto.h"
#include "hd.h"
#include "fs.h"
#include "global.h"
/*task stack*/
PUBLIC	char			task_stack[STACK_SIZE_TOTAL];
/*irq handler*/
PUBLIC 	irq_handler		irq_table[NR_IRQ];
/*sys-call*/
PUBLIC	system_call     sys_call_table[NR_SYS_CALL]={sys_printx,sys_sendrec};
/*tty*/
PUBLIC	TTY				tty_table[NR_CONSOLES];
PUBLIC	CONSOLE			console_table[NR_CONSOLES];
/*process and task*/
PUBLIC	PROCESS			proc_table[NR_TASKS+ NR_PROCS];
PUBLIC	TASK	task_table[NR_TASKS] = {
	{task_tty, STACK_SIZE_TTY, "tty"},
	{task_sys, STACK_SIZE_SYS, "sys"},
	{task_hd, STACK_SIZE_HD, "hd"},
	{task_fs, STACK_SIZE_FS, "fs"},};
PUBLIC  TASK    user_proc_table[NR_PROCS] = {
	{Init,   STACK_SIZE_INIT,  "INIT" },
	{TestA, STACK_SIZE_TESTA, "TestA"},
	{TestB, STACK_SIZE_TESTB, "TestB"},
	{TestC, STACK_SIZE_TESTC, "TestC"},};
/*device nr map*/
struct dev_drv_map dd_map[] = {
	/* driver nr.		major device nr.
	   ----------		---------------- */
	{INVALID_DRIVER},	/**< 0 : Unused */
	{INVALID_DRIVER},	/**< 1 : Reserved for floppy driver */
	{INVALID_DRIVER},	/**< 2 : Reserved for cdrom driver */
	{TASK_HD},			/**< 3 : Hard disk */
	{TASK_TTY},			/**< 4 : TTY */
	{INVALID_DRIVER}	/**< 5 : Reserved for scsi disk driver */
};
/**
 * 6MB~7MB: buffer for FS
 */
PUBLIC	u8 *		fsbuf		= (u8*)0x600000;
PUBLIC	const int	FSBUF_SIZE	= 0x100000;