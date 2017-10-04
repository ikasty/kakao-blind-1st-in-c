#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void q2 (char *str);

int main ()
{
	FILE *fp = fopen("data/q2.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		char str[20];
		if (fgets(str, 20, fp) == NULL) return -1;
		int len = strlen(str);

		// remove CR/LF
		while (str[len - 1] == 13 || str[len - 1] == 10) len--;
		str[len] = 0;

		q2(str);
	}

	return 0;
}
