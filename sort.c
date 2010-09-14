#include <unistd.h>
#include "pipe_util.h"

int main(int argc, char **argv)
{
	int fd1[2];
	int fd2[2];
	int **chan1=fd1, **chan2=fd2;

	if (argc != 2) {
		printf("Usage: sort 

	pipe(chan1);
	pipe(chan2);
	write_to(chan1);