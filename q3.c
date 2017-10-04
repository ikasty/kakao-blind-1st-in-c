#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 30
#define IDX(s, i) (&s[i * MAX_LEN])
#define CACHE_HIT 1
#define CACHE_MISS 5

char *cache;
int cache_len, cache_pnt;
void init_cache (const int n)
{
	if (!n) return ;

	// 최대 글자 * 캐시 크기만큼 1차원 배열 생성
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
	// 캐시 체크는 뒤에서부터 전부 체크
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
	// 캐시 생성
	init_cache(size);

	// 도시 이름을 전부 대문자화
	for (int i = 0; data[i]; i++)
	{
		for (char *t = data[i]; *t; t++) *t = toupper(*t);
	}

	int sum = 0;
	int i = 0;
	while (data[i])
	{
		// 캐시 사용해서 검색
		sum += check_cache(data[i++]);
	}

	printf("%d\n", sum);
	cache_del();
}
