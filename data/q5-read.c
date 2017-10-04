#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void q5 (char *str1, char *str2);

void trim (char *x)
{
	int len = strlen(x);
	while (x[len - 1] == 13 || x[len - 1] == 10) len--;
	x[len] = 0;
}

int main ()
{
	FILE *fp = fopen("data/q5.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		char str1[1001], str2[1001];
		if (fgets(str1, 1000, fp) == NULL) return -1;
		if (fgets(str2, 1000, fp) == NULL) return -1;

		trim(str1);
		trim(str2);

		q5(str1, str2);
	}

	return 0;
}
