#include <stdio.h>
#include <stdlib.h>

void q1 (int n, int *arr1, int *arr2);

int main ()
{
	FILE *fp = fopen("q1.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d", &testcase);

	while (testcase--)
	{
		int n;
		fscanf(fp, "%d", &n);

		int *a1 = malloc(sizeof(int) * n);
		int *a2 = malloc(sizeof(int) * n);

		for (int i = 0; i < n; i++)
			fscanf(fp, "%d", &a1[i]);
		
		for (int i = 0; i < n; i++)
			fscanf(fp, "%d", &a2[i]);

		q1(n, a1, a2);
		free(a1);
		free(a2);
	}
}

void q1 (int n, int *arr1, int *arr2)
{
	int *res = malloc(sizeof(int) * n);
	int bit = 1;

	for (int i = 0; i < n; i++)
	{
		res[i] = arr1[i] | arr2[i];
		bit *= 2;
	}

	for (int i = 0; i < n; i++)
	{
		int seek = bit;
		while (seek /= 2)
		{
			putchar(res[i] & seek ? '#' : ' ');
		}
		printf("\n");
	}

	return ;
}
