#ifndef	_HD_H_
#define	_HD_H_

/********************************************/
/* I/O Ports used by hard disk controllers. */
/********************************************/
#define REG_DATA		0x1F0			/*	Data						I/O		*/
#define REG_FEATURES	0x1F1			/*	Features					O		*/
#define REG_ERROR		REG_FEATURES	/*	Error						I		*/

#define REG_NSECTOR		0x1F2		/*	Sector Count					I/O		*/
#define REG_LBA_LOW		0x1F3		/*	Sector Number / LBA Bits 0-7	I/O		*/
#define REG_LBA_MID		0x1F4		/*	Cylinder Low / LBA Bits 8-15	I/O		*/
#define REG_LBA_HIGH	0x1F5		/*	Cylinder High / LBA Bits 16-23	I/O		*/
#define REG_DEVICE		0x1F6		/*	Drive | Head | LBA bits 24-27	I/O		*/

#define REG_STATUS	0x1F7			/*	Status							I		*/
#define	STATUS_BSY	0x80
#define	STATUS_DRDY	0x40
#define	STATUS_DFSE	0x20
#define	STATUS_DSC	0x10
#define	STATUS_DRQ	0x08
#define	STATUS_CORR	0x04
#define	STATUS_IDX	0x02
#define	STATUS_ERR	0x01

#define REG_CMD			REG_STATUS		/*	Command						O		*/

#define REG_DEV_CTRL	0x3F6			/*	Device Control				O		*/

#define REG_ALT_STATUS	REG_DEV_CTRL	/*	Alternate Status			I		*/

#define REG_DRV_ADDR	0x3F7			/*	Drive Address				I		*/
/*structure of hd command register*/
struct hd_cmd {
	u8	features;
	u8	count;
	u8	lba_low;
	u8	lba_mid;
	u8	lba_high;
	u8	device;
	u8	command;
};
/*structure of part information*/
struct part_info {
	u32	base;	/* # of start sector (NOT byte offset, but SECTOR) */
	u32	size;	/* how many sectors in this partition */
};

/* main drive struct, one entry per drive */
struct hd_info
{
	/* int			cylinders; */
	/* int			heads; */
	/* int			sectors; */
	/* int			precomp; */
	/* int			lzone; */
	/* int			ctl; */
	int			open_cnt;
	struct part_info	primary[NR_PRIM_PER_DRIVE];
	struct part_info	logical[NR_SUB_PER_DRIVE];
};
/*structure of partition entry*/
struct part_ent {
	u8 boot_ind;		/**
				 * boot indicator
				 *   Bit 7 is the active partition flag,
				 *   bits 6-0 are zero (when not zero this
				 *   byte is also the drive number of the
				 *   drive to boot so the active partition
				 *   is always found on drive 80H, the first
				 *   hard disk).
				 */

	u8 start_head;		/**
				 * Starting Head
				 */

	u8 start_sector;	/**
				 * Starting Sector.
				 *   Only bits 0-5 are used. Bits 6-7 are
				 *   the upper two bits for the Starting
				 *   Cylinder field.
				 */

	u8 start_cyl;		/**
				 * Starting Cylinder.
				 *   This field contains the lower 8 bits
				 *   of the cylinder value. Starting cylinder
				 *   is thus a 10-bit number, with a maximum
				 *   value of 1023.
				 */

	u8 sys_id;		/**
				 * System ID
				 * e.g.
				 *   01: FAT12
				 *   81: MINIX
				 *   83: Linux
				 */

	u8 end_head;		/**
				 * Ending Head
				 */

	u8 end_sector;		/**
				 * Ending Sector.
				 *   Only bits 0-5 are used. Bits 6-7 are
				 *   the upper two bits for the Ending
				 *    Cylinder field.
				 */

	u8 end_cyl;		/**
				 * Ending Cylinder.
				 *   This field contains the lower 8 bits
				 *   of the cylinder value. Ending cylinder
				 *   is thus a 10-bit number, with a maximum
				 *   value of 1023.
				 */

	u32 start_sect;	/**
				 * starting sector counting from
				 * 0 / Relative Sector. / start in LBA
				 */

	u32 nr_sects;		/**
				 * nr of sectors in partition
				 */

} PARTITION_ENTRY;

/***************/
/* DEFINITIONS */
/***************/
#define	HD_TIMEOUT				10000	/* in millisec */
#define	PARTITION_TABLE_OFFSET	0x1BE
#define ATA_IDENTIFY			0xEC
#define ATA_READ				0x20
#define ATA_WRITE				0x30

/* for DEVICE register. */
#define	MAKE_DEVICE_REG(lba,drv,lba_highest) (((lba) << 6) |		\
					      ((drv) << 4) |		\
					      (lba_highest & 0xF) | 0xA0)


#endif