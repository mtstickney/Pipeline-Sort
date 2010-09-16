#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include "stralloc.h"
#include "pipe_util.h"
#include "chan.h"

struct io
{
	Channel *in;
	Channel *out;
};

void *split(void *arg)
{
	struct io *chans;
	stralloc name = {0};
	char d;

	chans = (struct io *)arg;
	while (recv(chans->in, &d) != -1) {
		if (isspace(d)) {
			/* flush buffer */
			if (count != 0) {
				stralloc_0(&name);
				send(chans->out, strdup(name.s));
				stralloc_free(&name);
			}
			continue;
		} else {
			stralloc_append(&name, &d);
		}
	}

	if (name.len != 0) {
		stralloc_0(&name);
		send(chans->out, strdup(name.s);
	}
	stralloc_free(&name);
	return NULL;
}

void *chain(void *arg)
{
	Channel *procs;
	Channel c, newc;
	char *proc_name;
	char *const args[] = {NULL, NULL};
	int ret;
	int no_redir = -1;
	Pipe p;

	procs = (Channel *)arg;
	
	/* start the first process */
	proc_name = recv_string(procs);
	if (proc_name == NULL)
		fprintf(stderr, "chain: failed to recv process name\n");
		goto BAD_PROCNAME;
	}
	args[0] = proc_name;
	if (mk_chan(&c, sizeof(int)) == -1) {
		fprintf(stderr, "chain: error creating channel\n");
		goto BAD_CHAN;
	}
	
	if (begin(proc_name, args, &c) == -1) {
		fprintf(stderr, "chain: error forking new process \"%s\"\n", proc_name);
		BAD_CHAN;
	}
	/* don't redirect lead process's input */
	if (send(&c, &no_redir) == -1) {
		fprintf(stderr, "chain: failed sending no_redir as head process's input\n");
		goto BAD_CHAN;
	}

	/* chain the rest of the proc list */
	while ((proc_name = recv_string(procs)) != NULL) {
		if (*proc_name == 0) {
			/* end of process list */
			if (send(&c, &no_redir) == -1) {
				fprintf("chain: failed sending no_redir to final proc\n");
				goto BAD_CHAN;
			}
			free_chan(&c);
			free(proc_name);
			break;
		}

		if (mk_pipe(&p) == -1) {
			fprintf(stderr, "chain: failed to create pipe\n");
			goto BAD_PIPE;
		}
		if (mk_chan(&newc, sizeof(int)) == -1) {
			fprintf(stderr, "chain: error creating new channel\n");
			goto BAD_NEWCHAN;
		}
		args[0] = proc_name;
		if (begin(proc_name, args, &newc) == -1) {
			fprintf(stderr, "chain: error forking new process\n");
			goto BAD_NEWCHAN;
		}
		if (send(&c, &(p.writer) == -1) {
			fprintf(stderr, "chain: error sending fd to old process\n");
			goto BAD_NEWCHAN;
		}
		if (send(&newc, &(p.reader)) == -1) {
			fprintf(stderr, "chain: error sending fd to new process\n");
			goto BAD_NEWCHAN;
		}
		free_chan(&c);
		c = newc;
	}
	if (proc_name == NULL) {
		/* should have recieved 0-length end-of-list string */
		fprintf(stderr, "chain: error recieving process name\n");
		goto BAD_NEWCHAN;
	}

	return 1; /* non-NULL void* value */
}

int main(int argc, char **argv)
{
	int elements;

	if (argc != 2 || sscanf(argv[1], "%d", &elements) != 1) {
		printf("Usage: sort count filter_file\n");
		return 1;
	}

	pipe(chan1);
	pipe(chan2);
	write_to(chan1);