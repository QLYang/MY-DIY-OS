#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"
#include "keyboard.h"

KB_INPUT kb_in;

PUBLIC void keyboard_handler(int irq){
	u8 scan_code = in_byte(KB_DATA);

	if (kb_in.count < KB_IN_BYTES) {
		*(kb_in.p_head) = scan_code;
		kb_in.p_head++;
		if (kb_in.p_head == kb_in.buf + KB_IN_BYTES) {
			kb_in.p_head = kb_in.buf;
		}
		kb_in.count++;
	}
}

PUBLIC void init_keyboard_handler(){
	kb_in.count=0;
	kb_in.p_head=
	put_irq_handler(KEYBOARD_IRQ, keyboard_handler); /* 设定时钟中断处理程序 */
    enable_irq(KEYBOARD_IRQ);
}