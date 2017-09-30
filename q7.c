#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void q7 (char **arr);

int trim (char *x)
{
	int len = strlen(x);
	while (x[len - 1] == 13 || x[len - 1] == 10) len--;
	x[len] = 0;

	return len;
}

int main ()
{
	FILE *fp = fopen("data/q7.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		int n;
		fscanf(fp, "%d\n", &n);

		char **data = malloc(sizeof(char *) * (n + 1));
		for (int i = 0; i < n; i++)
		{
			size_t size = 0;
			data[i] = NULL;
			size = getline(&data[i], &size, fp);
			if (!size) return -1;
			size = trim(data[i]);
		}
		data[n] = NULL;

		q7(data);

		for (int i = 0; i < n; i++) free(data[i]);
		free(data);
	}

	return 0;
}

enum status {END, START};
struct q
{
	double val;
	enum status start;
};

int sort (const void *a, const void *b)
{
	return ((struct q *)a)->val * 1000 - ((struct q *)b)->val * 1000;
}

void q7 (char **arr)
{
	int h, m;
	double s, dur;
	struct q *data;
	int n = 0;
	while (arr[++n]) ;

	data = malloc(sizeof(struct q) * n * 2);

	for (int i = 0; i < n; i++)
	{
		sscanf(arr[i], "2016-09-15 %d:%d:%lf %lfs\n", &h, &m, &s, &dur);
		data[i * 2].val = h*60*60 + m*60 + s;
		data[i * 2].start = END;
		data[i * 2 + 1].val = data[i*2].val - dur + 0.001;
		data[i * 2 + 1].start = START;
	}

	qsort(data, n * 2, sizeof(struct q), sort);

	int count = 0, last = 0, max = 0;
	for (int i = 0; i < 2 * n; i++)
	{
		count += (data[i].start == START);

		while (data[i].val * 1000 - data[last].val * 1000 >= 1000)
		{
			count -= (data[last].start == END);
			last++;
		}

		if (max < count) max = count;
	}

	free(data);

	printf("%d\n", max);
}
