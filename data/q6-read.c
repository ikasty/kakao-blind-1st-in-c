#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void q6 (int m, int n, char **arr);

void trim (char *x)
{
	int len = strlen(x);
	while (x[len - 1] == 13 || x[len - 1] == 10) len--;
	x[len] = 0;
}

int main ()
{
	FILE *fp = fopen("data/q6.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		int m, n;
		fscanf(fp, "%d %d\n", &m, &n);

		char **arr = malloc(sizeof(char *) * m);
		for (int i = 0; i < m; i++)
		{
			arr[i] = malloc(sizeof(char) * n);
			fscanf(fp, "%s\n", arr[i]);
		}

		q6(m, n, arr);

		for (int i = 0; i < m; i++) free(arr[i]);
		free(arr);
	}

	return 0;
}
