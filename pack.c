#include <stdio.h>
#include <math.h>
#include <unistd.h>

int main()
{
	int i;
	unsigned int chars;
	unsigned int len;

	if (scanf("%d", &i) != 1) {
		return 0;
	}

	printf("%d", i);
	chars = (int)log10(i) + 1;
	while (scanf("%d", &i) == 1) {
		len = (int)log10(i)+1;
		if (chars+len+1 >= 30) {
			printf("\n%d", i);
			chars = len;
		} else {
			printf(" %d", i);
			chars += len+1;
		}
	}
	printf("\n");
	return 0;
}