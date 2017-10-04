#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status {END, START};
struct q
{
	double val;
	enum status start;
};

int sortfn (const void *a, const void *b)
{
	return ((struct q *)a)->val * 1000 - ((struct q *)b)->val * 1000;
}

void q7 (char **arr)
{
	int h, m;
	double s, dur;
	struct q *data;
	int n = 0;

	// 로그 개수를 세고, 데이터를 저장할 블록 동적 할당
	while (arr[++n]) ;
	data = malloc(sizeof(struct q) * n * 2);

	// 데이터 생성 및 시간대별로 정렬
	for (int i = 0; i < n; i++)
	{
		sscanf(arr[i], "2016-09-15 %d:%d:%lf %lfs\n", &h, &m, &s, &dur);
		data[i * 2].val = h*60*60 + m*60 + s;
		data[i * 2].start = END;
		data[i * 2 + 1].val = data[i*2].val - dur + 0.001; // 0.001초 차이가 발생한다
		data[i * 2 + 1].start = START;
	}
	qsort(data, n * 2, sizeof(struct q), sortfn);

	// 시간 순으로 이동하면서 처리중인 로그를 센다
	int count = 0, last = 0, max = 0;
	for (int i = 0; i < 2 * n; i++)
	{
		count += (data[i].start == START);

		// 윈도우 사이즈를 맞춤
		while (data[i].val * 1000 - data[last].val * 1000 >= 1000)
		{
			count -= (data[last].start == END);
			last++;
		}

		// 최대값 갱신
		if (max < count) max = count;
	}

	free(data);
	printf("%d\n", max);
}
