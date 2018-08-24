#include "type.h"
#include "const.h"

/*======================================================================*
                                vsprintf
 *======================================================================*/
int vsprintf(char *buf, const char *fmt, va_list args)
{
	char*	p;
	char	tmp[256];
	va_list	p_next_arg = args;

	for (p=buf;*fmt;fmt++) {
		if (*fmt != '%') {
			*p++ = *fmt;/*不是‘%’,将字符放入缓冲*/
			continue;
		}

		fmt++;/*‘%’后的字符*/

		switch (*fmt) {
		case 'x':
			itoa(tmp, *((int*)p_next_arg));/*num->hex*/
			strcpy(p, tmp);
			p_next_arg += 4;
			p += strlen(tmp);
			break;
		case 's':
			break;
		default:
			break;
		}
	}

	return (p - buf);
}