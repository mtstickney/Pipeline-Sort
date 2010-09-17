#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "pipe_util.h"
#include "stralloc.h"

char *get_name(FILE *f)
{
	int c;
	stralloc name = {0};
	char *strp;
	char d;

	/* consume leading whitespace */
	do {
		c = fgetc(f);	
	} while(isspace(c));
	ungetc(c, f);

	/* append non-whitespace chars */
	while (1) {
		c = fgetc(f);
		if (c < 0 || isspace(c)) {
			stralloc_0(&name);
			strp = strdup(name.s);
			stralloc_free(&name);
			return strp;
		}
		d = c;
		stralloc_append(&name, &d);
	}
}


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