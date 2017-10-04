#include <stdio.h>
#include <stdlib.h>

int cmp (const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

void q4 (int n, int t, int m, char **timetable)
{
	// 전체 개수를 센다
	int count = 0;
	while (timetable[++count]) ;

	// 정수로 변환된 timetable
	int *user = malloc(sizeof(int) * count);

	// 문자로 된 시간을 정수로 변환하고 시간순으로 정렬
	for (int i = 0; i < count; i++)
	{
		int h, m;
		sscanf(timetable[i], "%d:%d", &h, &m);
		user[i] = h * 60 + m;
	}
	qsort(user, count, sizeof(int), cmp);

	int bus = 9 * 60 + 0; // 버스는 9시 정각
	int pnt = 0;
	int last = user[pnt] - 1;
	if (last > bus) last = bus;
	int before = last;

	// 버스 배차개수 대로 루프
	while (n--)
	{
		int cap = m;
		while (pnt < count && cap)
		{
			// 버스보다 사용자가 늦게 도착하면
			if (bus < user[pnt]) break; // 버스는 떠납니다

			// 버스 인원 제한 감소
			cap--;

			// 제일 늦게 / 두 번째로 늦게 도착한 사용자 체크
			if (last < user[pnt])
			{
				before = last;
				last = user[pnt];
			}

			// 사용자 탑승 완료
			pnt++;
		}

		// 자리가 남아있는데 버스 출발까지 사용자가 안왔다면
		if (cap && last < bus)
		{
			// 버스 출발할 때 와도 무방
			before = last;
			last = bus;
		}
		// 자리가 안 남아있다면 마지막으로 온 사람보다는 빨리 와야 한다
		if (!cap) last = before;

		bus += t;
	}

	printf("%02d:%02d\n", last / 60, last % 60);

	free(user);
}
