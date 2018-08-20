#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"
#include "keyboard.h"

/*======================================================================*
				tty
 *======================================================================*/
PUBLIC void tty(){
	while(1){
		keyboard_read();
	}
}

/*======================================================================*
				in_process
 *======================================================================*/
PUBLIC void in_process(u32 key)
{
        char output[2] = {'\0', '\0'};

        if (!(key & FLAG_EXT)) {	/*不可打印字符都有FLAG_EXT*/
                output[0] = key & 0xFF;
                disp_str(output);
        }
}