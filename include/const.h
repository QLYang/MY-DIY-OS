#ifndef	_CONST_H_
#define	_CONST_H_

/* 函数类型 */
#define	PUBLIC
#define	PRIVATE	static

#define	STR_DEFAULT_LEN	1024

/* EXTERN is defined as extern except in global.c */
#define EXTERN extern

/* max() & min() */
#define	max(a,b)		((a) > (b) ? (a) : (b))
#define	min(a,b)		((a) < (b) ? (a) : (b))

/* GDT 和 IDT 中描述符的个数 */
#define	GDT_SIZE		128
#define	IDT_SIZE		256

/* 权限 */
#define	PRIVILEGE_KRNL	0
#define	PRIVILEGE_TASK	1
#define	PRIVILEGE_USER	3
/* RPL */
#define	RPL_KRNL		SA_RPL0
#define	RPL_TASK		SA_RPL1
#define	RPL_USER		SA_RPL3
/* 8259A interrupt controller ports. */
#define INT_M_CTL     	0x20 /* I/O port for interrupt controller       <Master> */
#define INT_M_CTLMASK 	0x21 /* setting bits in this port disables ints <Master> */
#define INT_S_CTL     	0xA0 /* I/O port for second interrupt controller<Slave>  */
#define INT_S_CTLMASK 	0xA1 /* setting bits in this port disables ints <Slave>  */

/* Hardware interrupts */
#define	NR_IRQ			16	/* Number of IRQs */

#define	CLOCK_IRQ		0
#define	KEYBOARD_IRQ	1
#define	CASCADE_IRQ		2	/* cascade enable for 2nd AT controller */
#define	ETHER_IRQ		3	/* default ethernet interrupt vector */
#define	SECONDARY_IRQ	3	/* RS232 interrupt vector for port 2 */
#define	RS232_IRQ		4	/* RS232 interrupt vector for port 1 */
#define	XT_WINI_IRQ		5	/* xt winchester */
#define	FLOPPY_IRQ		6	/* floppy disk */
#define	PRINTER_IRQ		7
#define	AT_WINI_IRQ		14	/* at winchester */

/*系统调用*/
#define	NR_SYS_CALL		2

#define TRUE 			1
#define FALSE 			0

/*显示--相关宏*/
/* Color */
#define BLACK   		0x0     /* 0000 */
#define WHITE   		0x7     /* 0111 */
#define RED     		0x4     /* 0100 */
#define GREEN   		0x2     /* 0010 */
#define BLUE    		0x1     /* 0001 */
#define FLASH   		0x80    /* 1000 0000 */
#define BRIGHT  		0x08    /* 0000 1000 */
#define	MAKE_COLOR(x,y)	((x<<4) | y) /* MAKE_COLOR(Background,Foreground) */
/* VGA */
#define	CRTC_ADDR_REG	0x3D4	/* CRT Controller Registers - Addr Register */
#define	CRTC_DATA_REG	0x3D5	/* CRT Controller Registers - Data Register */
#define	START_ADDR_H	0xC	/* reg index of video mem start addr (MSB) */
#define	START_ADDR_L	0xD	/* reg index of video mem start addr (LSB) */
#define	CURSOR_H		0xE	/* reg index of cursor position (MSB) */
#define	CURSOR_L		0xF	/* reg index of cursor position (LSB) */
#define	V_MEM_BASE		0xB8000	/* base of color video memory */
#define	V_MEM_SIZE		0x8000	/* 32K: B8000H -> BFFFFH */

/* TTY */
#define NR_CONSOLES		3	/* consoles */

/*assert*/
#define ASSERT
#ifdef ASSERT
void assertion_failure(char *exp, char *file, char *base_file, int line);
#define assert(exp)  if (exp) ; \
        else assertion_failure(#exp, __FILE__, __BASE_FILE__, __LINE__)
#else
#define assert(exp)
#endif

/* magic chars used by `printx' */
#define MAG_CH_PANIC	'\002'
#define MAG_CH_ASSERT	'\003'

/* ipc */
#define SEND			1
#define RECEIVE			2
#define BOTH			3	/* BOTH = (SEND | RECEIVE) */
/* tasks */
#define ANY				(NR_TASKS + NR_PROCS + 10)
#define NO_TASK			(NR_TASKS + NR_PROCS + 20)

#define INTERRUPT		-10

#define INVALID_DRIVER	-20
#define TASK_TTY		0
#define TASK_SYS		1
#define TASK_HD			2
#define TASK_FS			3
#define TASK_MM			4
#define INIT  			5
/* Process */
#define SENDING   		0x02	/* set when proc trying to send */
#define RECEIVING 		0x04	/* set when proc trying to recv */
#define FREE_SLOT 		0x20	/* set when proc table entry is not used
			 					* (ok to allocated to a new process)
			 					*/
#define WAITING   		0x08	/* set when proc waiting for the child to terminate */
#define HANGING   		0x10	/* set when proc exits without being waited by parent */

enum msgtype {
	/*
	 * when hard interrupt occurs, a msg (with type==HARD_INT) will
	 * be sent to some tasks
	 */
	HARD_INT = 1,

	/* SYS task */
	GET_TICKS,GET_PID,

	/* message type for drivers */
	DEV_OPEN = 1001,
	DEV_CLOSE,
	DEV_READ,
	DEV_WRITE,
	DEV_IOCTL,

	/* FS */
	OPEN,
	CLOSE,
	READ,
	WRITE,
	LSEEK,
	STAT,
	UNLINK,

	/* TTY, SYS, FS, MM, etc */
	SYSCALL_RET,
	/* for debug */
	DISK_LOG,

	/* FS & TTY */
	SUSPEND_PROC, RESUME_PROC,

	/* MM */
	FORK, EXIT,WAIT,EXEC,
};

/* 8253/8254 PIT (Programmable Interval Timer) */
#define HZ             		100  /* clock freq (software settable on IBM-PC) */

/*message*/
#define	RETVAL				u.m3.m3i1
#define	DEVICE				u.m3.m3i4
#define	POSITION			u.m3.m3l1
#define	CNT					u.m3.m3i2
#define	PROC_NR				u.m3.m3i3
#define	BUF					u.m3.m3p2
#define	REQUEST				u.m3.m3i2

#define	PATHNAME			u.m3.m3p1
#define	FLAGS				u.m3.m3i1
#define	NAME_LEN			u.m3.m3i2
#define	FD					u.m3.m3i1

#define	PID					u.m3.m3i2
#define	STATUS				u.m3.m3i1

#define	NAME_LEN			u.m3.m3i2
#define	BUF_LEN				u.m3.m3i3

/*hd_ioctl p->REQUEST*/
#define	DIOCTL_GET_GEO		1

/* Hard Drive */
#define SECTOR_SIZE			512
#define SECTOR_BITS			(SECTOR_SIZE * 8)
#define SECTOR_SIZE_SHIFT	9

#define	MAX_DRIVES			2
#define	NR_PART_PER_DRIVE	4
#define	NR_SUB_PER_PART		16
#define	NR_SUB_PER_DRIVE	(NR_SUB_PER_PART * NR_PART_PER_DRIVE)
#define	NR_PRIM_PER_DRIVE	(NR_PART_PER_DRIVE + 1)

#define	MAX_PRIM			(MAX_DRIVES * NR_PRIM_PER_DRIVE - 1)
#define	MAX_SUBPARTITIONS	(NR_SUB_PER_DRIVE * MAX_DRIVES)

/* major device numbers (corresponding to kernel/global.c::dd_map[]) */
#define	NO_DEV				0
#define	DEV_FLOPPY			1
#define	DEV_CDROM			2
#define	DEV_HD				3
#define	DEV_CHAR_TTY		4
#define	DEV_SCSI			5

/* make device number from major and minor numbers */
#define	MAJOR_SHIFT			8
#define	MAKE_DEV(a,b)		((a << MAJOR_SHIFT) | b)
/* separate major and minor numbers from device number */
#define	MAJOR(x)			((x >> MAJOR_SHIFT) & 0xFF)
#define	MINOR(x)			(x & 0xFF)

/* device numbers of hard disk */
#define	MINOR_hd1a			0x10
#define	MINOR_hd2a			(MINOR_hd1a+NR_SUB_PER_PART)

#define	ROOT_DEV			MAKE_DEV(DEV_HD, MINOR_BOOT)

#define	P_PRIMARY			0
#define	P_EXTENDED			1

#define Our_PART			0x99	/* Our partition */
#define NO_PART				0x00	/* unused entry */
#define EXT_PART			0x05	/* extended partition */

/*inode*/
#define	INVALID_INODE		0
#define	ROOT_INODE			1

/* INODE::i_mode (octal, lower 12 bits reserved) */
#define I_REGULAR       	0100000
#define I_NAMED_PIPE		0010000
#define I_DIRECTORY     	0040000
/*special*/
#define I_TYPE_MASK     	0170000
#define I_BLOCK_SPECIAL 	0060000
#define I_CHAR_SPECIAL  	0020000

#define	is_special(m)	((((m) & I_TYPE_MASK) == I_BLOCK_SPECIAL) ||	\
			 (((m) & I_TYPE_MASK) == I_CHAR_SPECIAL))

/*number of default file sectors(used in sector map initialization)*/
#define	NR_DEFAULT_FILE_SECTS	2048 /* 2048 * 512 = 1MB */

/*Definition of file system*/
#define	NR_FILES			64
#define	NR_FILE_DESC		64
#define	NR_INODE			64
#define	NR_SUPER_BLOCK		8

/*stdio*/
#define	O_CREAT		1
#define	O_RDWR		2

#define SEEK_SET	1
#define SEEK_CUR	2
#define SEEK_END	3

#define	MAX_PATH	128

/*syslog*/
//#ifdef ENABLE_DISK_LOG
#define SYSLOG syslog
//#endif

#endif