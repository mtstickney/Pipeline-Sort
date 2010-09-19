#ifndef TIMEOUTCONN_H
#define TIMEOUTCONN_H

#include "uint16.h"

extern int timeoutconn(int s,const char *ip,uint16 port,unsigned int timeout);
extern int timeoutconn6(int s,const char *ip,uint16 port,unsigned int scope_id,unsigned int timeout);

#endif
