/* include before this file:
	stdlib.h
	pipe_util.h
*/

typedef struct chan
{
	size_t elsize;
	Pipe data_chan;
	Pipe barrier;
} Channel;

Channel *mk_chan(size_t elsize);

void free_chan(Channel *c);

int send(Channel *c, const void *data);

int recv(Channel *c, void *data);