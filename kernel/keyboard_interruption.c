#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"

PUBLIC void keyboard_handler(int irq){
	disp_str("*");
}

PUBLIC void init_keyboard_handler(){
	put_irq_handler(KEYBOARD_IRQ, keyboard_handler); /* 设定时钟中断处理程序 */
    enable_irq(KEYBOARD_IRQ);
}