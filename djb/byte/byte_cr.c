#include "byte.h"

void byte_copyr(register void* To,register unsigned int n,
		register const void* From)
{
  register char *to=(char*)To+n;
  register const char *from=(char*)From+n;
  for (;;) {
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
  }
}
