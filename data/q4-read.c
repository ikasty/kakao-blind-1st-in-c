#include <stdio.h>
#include <stdlib.h>

void q4 (int n, int t, int m, char **timetable);

int main ()
{
	FILE *fp = fopen("data/q4.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		int n, t, m;
		fscanf(fp, "%d %d %d", &n, &t, &m);

		int len;
		fscanf(fp, "%d\n", &len);

		char **list = malloc(sizeof(char *) * (len + 1));
		for (int i = 0; i < len; i++)
		{
			int h, m;
			list[i] = malloc(sizeof(char) * 6);
			fscanf(fp, "%6s", list[i]);
		}
		list[len] = NULL;

		q4(n, t, m, list);

		for (int i = 0; i < len; i++) free(list[i]);
		free(list);
	}

	return 0;
}
