#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void q7 (char **arr);

int trim (char *x)
{
	int len = strlen(x);
	while (x[len - 1] == 13 || x[len - 1] == 10) len--;
	x[len] = 0;

	return len;
}

int main ()
{
	FILE *fp = fopen("data/q7.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		int n;
		fscanf(fp, "%d\n", &n);

		char **data = malloc(sizeof(char *) * (n + 1));
		for (int i = 0; i < n; i++)
		{
			size_t size = 0;
			data[i] = NULL;
			size = getline(&data[i], &size, fp);
			if (!size) return -1;
			size = trim(data[i]);
		}
		data[n] = NULL;

		q7(data);

		for (int i = 0; i < n; i++) free(data[i]);
		free(data);
	}

	return 0;
}
