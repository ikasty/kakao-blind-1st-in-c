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

void q6 (int m, int n, char **arr)
{
	int find = 1;
	char **set = malloc(sizeof(char *) * m);
	for (int i = 0; i < m; i++)
	{
		set[i] = malloc(sizeof(char) * n);
		memset(set[i], 0, sizeof(char) * n);
	}

	int count = 0;

	while (find)
	{
		find = 0;

		// check
		for (int i = 0; i < m - 1; i++)
		{
			for (int j = 0; j < n - 1; j++)
			{
				if (arr[i][j] == -1)              continue;
				if (arr[i][j] != arr[i][j+1])     continue;
				if (arr[i+1][j] != arr[i+1][j+1]) continue;
				if (arr[i][j] != arr[i+1][j])     continue;
				set[i][j]++;
				set[i][j+1]++;
				set[i+1][j]++;
				set[i+1][j+1]++;
			}
		}

		// sum
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				count += !!set[i][j];
				find = find || !!set[i][j];
				if (set[i][j]) arr[i][j] = -1;
				set[i][j] = 0;
			}
		}

		// move
		for (int j = 0; j < n; j++)
		{
			int blank = -1;
			for (int i = m - 1; i >= 0; i--)
			{
				if (blank == -1 && arr[i][j] != -1) continue;
				if (blank == -1)
				{
					blank = i;
					continue;
				}
				if (arr[i][j] == -1) continue;

				arr[blank--][j] = arr[i][j];
				arr[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < m; i++) free(set[i]);
	free(set);

	printf("%d\n", count);
}
