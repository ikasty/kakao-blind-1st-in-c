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
