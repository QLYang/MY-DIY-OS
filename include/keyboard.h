#ifndef	_KEYBOARD_H_
#define	_KEYBOARD_H_

#define	KB_IN_BYTES	32	/*键盘输入缓冲区大小*/
#define MAP_COLS	3	/* keymap的列 */
#define NR_SCAN_CODES	0x80	/* keymap的行 */

#define KB_DATA		0x60	/* I/O port for keyboard data (r/w) */
#define KB_CMD		0x64	/* I/O port for keyboard command (r/w)*/

typedef struct s_kb {			/*键盘输入缓冲区结构定义*/
	char*	p_head;				/* 指向缓冲区中下一个空闲位置 */
	char*	p_tail;				/* 指向键盘任务应处理的字节 */
	int	count;					/* 缓冲区中共有多少字节 */
	char	buf[KB_IN_BYTES];	/* 缓冲区 */
}KB_INPUT;

#endif