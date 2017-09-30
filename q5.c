#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void q5 (char *str1, char *str2);

void trim (char *x)
{
	int len = strlen(x);
	while (x[len - 1] == 13 || x[len - 1] == 10) len--;
	x[len] = 0;
}

int main ()
{
	FILE *fp = fopen("data/q5.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		char str1[1001], str2[1001];
		if (fgets(str1, 1000, fp) == NULL) return -1;
		if (fgets(str2, 1000, fp) == NULL) return -1;

		trim(str1);
		trim(str2);

		q5(str1, str2);
	}

	return 0;
}

int sort (const void *a, const void *b)
{
	char *x = (char *)a;
	char *y = (char *)b;
	int ret = x[0] - y[0];
	if (!ret) ret = x[1] - y[1];
	return ret;
}

void create(char *str, char list[1000][2], int *count)
{
	int i = 0, p = 0;
	char before = 0;
	while (str[i])
	{
		char now = tolower(str[i++]);
		if (!(now >= 'a' && now <= 'z')) {
			before = 0;
			continue;
		}
		if (!before) {
			before = now;
			continue;
		}

		list[p][0] = before;
		list[p][1] = now;
		before = now;
		p++;
	}
	*count = p;
}

void q5 (char *str1, char *str2)
{
	char a[1000][2], b[1000][2];
	int cnt1 = 0, cnt2 = 0;
	
	create(str1, a, &cnt1);
	create(str2, b, &cnt2);
	if (!cnt1 && !cnt2) {
		printf("%d\n", 65536);
		return ;
	}

	qsort(a, cnt1, sizeof(a[0]), sort);
	qsort(b, cnt2, sizeof(b[0]), sort);

	int same = 0;
	int p1 = cnt1 - 1, p2 = cnt2 - 1;
	while (p1 >= 0 && p2 >= 0)
	{
		int cmp = sort(a[p1], b[p2]);

			 if (cmp < 0) p2--;
		else if (cmp > 0) p1--;
		else			  p1-- & p2-- & same++;
	}

	same = same * 65536 / (double)(cnt1 + cnt2 - same);
	printf("%d\n", same);
}
