#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void q2 (char *str)
{
	int score[4] = {0, 0, 0, 0};
	int mults[4] = {1, 1, 1, 1};
	int args[4]  = {1, 1, 1, 1};
	int current = 0;
	int is_int = 0;

	// 문자열 파싱 파트
	for (int pnt = 0; str[pnt]; pnt++)
	{
		// 새로운 정수 부분 파싱 중인지?
		if (!is_int && str[pnt] >= '0' && str[pnt] <= '9') current++;

		// 문자별로 switch를 사용해 파싱
		is_int = 0;
		switch (str[pnt])
		{
		case '*':
			args[current]     *= 2;
			args[current - 1] *= 2;
			break;

		case '#':
			args[current] *= -1;
			break;

		case 'S': mults[current] = 1; break;
		case 'D': mults[current] = 2; break;
		case 'T': mults[current] = 3; break;
		
		default:
			is_int = 1;
			score[current] *= 10;
			score[current] += (str[pnt] - '0');
		}
	}

	// 점수 합계
	int sum = 0;
	for (int i = 1; i <= 3; i++)
	{
		int s = 1;
		while (mults[i]--) s *= score[i];
		s *= args[i];
		sum += s;
	}

	printf("%d\n", sum);
	return ;
}
