#include <stdio.h>
#include <stdlib.h>

int main()
{
	int c, low;
	ssize_t ret;

	ret = scanf("%d", &low);
	if (ret < 1) {
		perror("bubble main()");
		return 1;
	}

	while (scanf("%d", &c) == 1) {
		if (c < low) {
			printf("%d\n", low);
			low = c;
		} else {
			printf("%d\n", c);
		}
	}

	if (!feof(stdin)) {
		perror("bubble main()");
		return 1;
	}
	
	printf("%d\n", low);
	return 0;
}