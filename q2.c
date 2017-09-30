#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void q2 (char *str);

int main ()
{
	FILE *fp = fopen("data/q2.txt", "r");
	if (!fp) return -1;

	int testcase;
	fscanf(fp, "%d\n", &testcase);

	while (testcase--)
	{
		char str[20];
		if (fgets(str, 20, fp) == NULL) return -1;
		int len = strlen(str);

		// remove CR/LF
		while (str[len - 1] == 13 || str[len - 1] == 10) len--;
		str[len] = 0;

		q2(str);
	}

	return 0;
}

void q2 (char *str)
{
	int score[4] = {0, 0, 0, 0};
	int mults[4] = {1, 1, 1, 1};
	int args[4]  = {1, 1, 1, 1};
	int current = 1;
	int is_int = 1;

	for (int pnt = 0; str[pnt]; pnt++)
	{
		if (!is_int && str[pnt] >= '0' && str[pnt] <= '9')
		{
			is_int = 1;
			current++;
		}

		is_int = 0;
		switch(str[pnt])
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
