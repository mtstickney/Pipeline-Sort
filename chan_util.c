#include "chan_util.h"

int send_string(const char *str, Channel *c)
{
	struct str_header h;
	char *bufp = str;

	h.len = strlen(str);
	if (mk_chan(&(h.bytes), sizeof(char)) == -1)
		return -1;

	if (send(c, &h) == -1)
		return -1;
	while (*bufp) {
		if (send(&(h.bytes), bufp++) == -1)
			return -1;
	}
	/* send the NUL */
	if (send(&(h.bytes), bufp) == -1)
		return -1;
	return 0;
}