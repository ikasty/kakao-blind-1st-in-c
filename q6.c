#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void q6 (int m, int n, char **arr)
{
	// 없앨 블록을 찾는 배열 생성
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

		// 없앨 블록 후보들을 탐색
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

		// 몇 개의 블록이 사라지는지 센다
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

		// 없어진 블록을 채운다
		for (int j = 0; j < n; j++)
		{
			// 채워야 하는 블록 포인터
			int blank = -1;
			for (int i = m - 1; i >= 0; i--)
			{
				if (blank == -1 && arr[i][j] != -1) continue;
				if (blank == -1)
				{
					// 첫 사라진 블록을 찾아냄
					// arr[i][j] == -1
					blank = i;
					continue;
				}
				if (arr[i][j] == -1) continue;

				// 블록을 채움
				arr[blank--][j] = arr[i][j];
				arr[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < m; i++) free(set[i]);
	free(set);

	printf("%d\n", count);
}
