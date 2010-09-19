/* include list
	unistd.h
	stdio.h
*/

typedef struct pipe {
	int reader;
	int writer;
} Pipe;

int mk_pipe(Pipe *p);

void close_pipe(Pipe *p);

int chain(char *path, char *args[], FILE *need_file_pointer_here, unsigned int elements);

