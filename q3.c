#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void q3 (int size, char **data);

int trim (char *x)
{
	int len = strlen(x);
	while (x[len - 1] == 13 || x[len - 1] == 10) len--;
	x[len] = 0;

	return len;
}

int main ()
{
	FILE *fp = fopen("data/q3.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		int size, count;
		fscanf(fp, "%d %d\n", &size, &count);

		char **data = malloc(sizeof(char *) * (count + 1));
		for (int i = 0; i < count; i++)
		{
			size_t size = 0;
			data[i] = NULL;
			size = getline(&data[i], &size, fp);
			if (!size) return -1;
			size = trim(data[i]);
		}
		data[count] = NULL;

		q3(size, data);

		for (int i = 0; i < count; i++) free(data[i]);
		free(data);
	}

	return 0;
}

#define MAX_LEN 30
#define IDX(s, i) (&s[i * MAX_LEN])
#define CACHE_HIT 1
#define CACHE_MISS 5

char *cache;
int cache_len, cache_pnt;
void init_cache (const int n)
{
	if (!n) return ;

	cache = malloc(sizeof(char) * MAX_LEN * n);
	memset(cache, 0, sizeof(char) * MAX_LEN * n);
	cache_len = n;
	cache_pnt = 0;
}

void cache_del ()
{
	if (cache_len) free(cache);
	cache_len = 0;
}

void cache_add (const char *text)
{
	if (!cache_len) return ;

	memcpy(IDX(cache, cache_pnt), text, MAX_LEN);
	cache_pnt = (cache_pnt + 1) % cache_len;
}

int check_cache (const char *text)
{
	int i = cache_len;
	while (i--)
	{
		if (!strncmp(text, IDX(cache, i), MAX_LEN))
		{
			cache_add(text);
			return CACHE_HIT;
		}
	}

	cache_add(text);
	return CACHE_MISS;
}

void q3 (int size, char **data)
{
	init_cache(size);

	for (int i = 0; data[i]; i++)
	{
		for (char *t = data[i]; *t; t++) *t = toupper(*t);
	}

	int sum = 0;
	int i = 0;
	while (data[i])
	{
		sum += check_cache(data[i++]);
	}

	printf("%d\n", sum);
	cache_del();
}
