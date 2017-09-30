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

int cmp (const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

void q4 (int n, int t, int m, char **timetable)
{
	int count = 0;
	while (timetable[++count]) ;

	int *user = malloc(sizeof(int) * count);

	for (int i = 0; i < count; i++)
	{
		int h, m;
		sscanf(timetable[i], "%d:%d", &h, &m);
		user[i] = h * 60 + m;
	}
	qsort(user, count, sizeof(int), cmp);

	int bus = 9 * 60 + 0;
	int pnt = 0;
	int last = user[pnt] - 1;
	if (last > bus) last = bus;
	int before = last;

	while (n--)
	{
		int cap = m;
		while (pnt < count && cap)
		{
			if (bus < user[pnt]) break; // bye bye bus
			cap--;

			if (last < user[pnt]) {
				before = last;
				last = user[pnt];
			}
			pnt++;
		}

		if (cap && last < bus) {
			before = last;
			last = bus;
		}
		if (!cap) last = before;

		bus += t;
	}

	printf("%02d:%02d\n", last / 60, last % 60);

	free(user);
}
