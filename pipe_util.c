#include <unistd.h>
#include "pipe_util.h"

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

pid_t begin(const char *path, char  *const args[], Pipe *in, Pipe *out)
{
	pid_t pid;

	dup2(in->reader, STDIN_FILENO);
	close(in->reader);
	dup2(out->writer, STDOUT_FILENO);
	close(out->writer);
	
	switch(pid = fork()) {
	case 0:
		if (execv(path,args) < 0) {
			perror("begin");
			exit(1);
		}
		break;
	case -1:
		perror("begin");
		exit(1);
		break;
	default:
		return pid;
		break;
	}

}