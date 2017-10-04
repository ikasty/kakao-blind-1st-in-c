#include <stdio.h>
#include <stdlib.h>

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
