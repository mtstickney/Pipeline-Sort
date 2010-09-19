#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipe_util.h"

#define NPROCS (elements+3)

extern char *get_name(FILE* f);

int mk_pipe(Pipe *p)
{
	int fds[2];
	int ret;

	ret = pipe(fds);
	p->reader = fds[0];
	p->writer = fds[1];
	return ret;
}

void close_pipe(Pipe *p)
{
	close(p->reader);
	close(p->writer);
}

int begin(char *path, char  *args[], FILE *filters, unsigned int elements)
{
	Pipe pipes[2];
	Pipe *in, *out, *tmp;
	pid_t pid;
	unsigned int child;

	in = &pipes[0];
	out = &pipes[1];

	for (child = 0; child < NPROCS; child++) {
		if (child < NPROCS-1) {
			if (mk_pipe(out) != 0) {
				perror("begin");
				return -1;
			}
		}

		switch(fork()) {
		case -1:
			return pid;
		case 0:
			if (child > 0) {
				dup2(in->reader, STDIN_FILENO);
				close(in->reader);
				close(in->writer);
			}
			if (child < NPROCS-1) {
				dup2(out->writer, STDOUT_FILENO);
				close(out->writer);
				close(out->reader);
			}
			if (execv(path, args) == -1) {
				perror("begin");
				exit(1);
			};
		default:
			if (child > 0)
				close_pipe(in);
		}

		/* patch up arguments */
		if (child == 0 || child >= elements) {
			free(path);
			path = get_name(filters);
			if (path == NULL) {
				fprintf(stderr, "begin: Unexpected end of filter list\n");
				return -1;
			}
			args[0] = path;
		}
		tmp = in;
		in = out;
		out = tmp;
	}
	return 0;
}
