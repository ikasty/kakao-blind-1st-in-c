#include <stdio.h>
#include <stdlib.h>

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

			if (last < user[pnt])
			{
				before = last;
				last = user[pnt];
			}
			pnt++;
		}

		if (cap && last < bus)
		{
			before = last;
			last = bus;
		}
		if (!cap) last = before;

		bus += t;
	}

	printf("%02d:%02d\n", last / 60, last % 60);

	free(user);
}
