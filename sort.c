#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipe_util.h"
#include "stralloc.h"

unsigned int elements;

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
	FILE *filters;
	char *name;
	char *args[] = {NULL, NULL};
	int i;

	if (argc != 3 || sscanf(argv[1],"%u", &elements) != 1){
		printf("Usage: sort n filters.txt\n");
		exit(1);
	}

	filters = fopen(argv[2], "r");
	if (filters == NULL) {
		fprintf(stderr, "Couldn't open filter list '%s'\n", argv[2]);
		return 1;
	}
	name = get_name(filters);
	if (name == NULL) {
		fprintf(stderr, "Expected at least one filter name in filter list\n");
		return 1;
	}
	args[0] = name;
	begin(name, args, filters, elements);
	
	for (i=0; i<elements+3; i++) {
		wait(NULL);
	}

	return 0;
}
