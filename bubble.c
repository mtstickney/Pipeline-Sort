#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int c, high;
	ssize_t ret;
	int i;

	if (scanf("%d", &high) != 1) {
		perror("read");
		return 1;
	}

	while (scanf("%d", &c) == 1 ) {
		if (c > high) {
			printf("%d\n", high);
			high = c;
		} else {
			printf("%d\n", c);
		}
	}
	printf("%d\n", high);
	return 0;
}