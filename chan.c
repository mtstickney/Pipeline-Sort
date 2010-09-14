#include <stdlib.h>
#include <unistd.h>
#include "pipe_util.h"
#include "chan.h"

Channel *mk_chan(size_t elsize)
{
	Channel *c;

	c = (Channel *) malloc(sizeof(Channel));
	if (c == NULL)
		return NULL;

	if (mk_pipe(&(c->data_chan)) != 0)
		goto BAD_DATA_PIPE;
	if (mk_pipe(&(c->barrier)) != 0)
		goto BAD_SYNCH_PIPE;
	c->elsize = elsize;
	return c;

BAD_SYNCH_PIPE:
	close_pipe(&(c->data_chan));
BAD_DATA_PIPE:
	free(c);
	return NULL;
}

void free_chan(Channel *c)
{
	close_pipe(&(c->data_chan));
	close_pipe(&(c->barrier));
}

int send(Channel *c, const void *data)
{
	ssize_t ret;
	size_t sent=0;
	char d = 0;

	do {
		ret = write(c->data_chan.writer, data, c->elsize-sent);
		if (ret < 0)
			return -1;
		data = (char *)data + ret;
	} while ((sent += ret) < c->elsize);

	/* block until receiver gets data */
	read(c->barrier.reader, &d, 1);

	return 0;
}

int recv(Channel *c, void *data)
{
	ssize_t ret;
	size_t recved=0;
	char d = 0;

	do {
		ret = read(c->data_chan.reader, data, c->elsize-recved);
		if (ret <= 0)
			return -1;
		data = (char *)data + ret;
	} while ((recved += ret) < c->elsize);

	/* read blocks on sends for us, so unblock senders */
	/* NOTE: do not put this before the read loop or we can get deadlocks
		when the kernel's pipe buffer fills up. */
	write(c->barrier.writer, &d, 1);
	
	return 0;
}