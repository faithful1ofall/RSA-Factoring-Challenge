#include "rsa.h"

int main(int argc, char *argv[])
{
	FILE *file = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (access(argv[1], R_OK) == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		perror("");
		exit(EXIT_FAILURE);
	}

	factorize_any(file);

	fclose(file);
	return (0);
}

void factorize_any(FILE *file)
{
	size_t num, numberLen = 0;
	char *number = NULL;

	while (getline(&number, &numberLen, file) != -1)
	{
		numberLen = strlen(number);
		if (numberLen < 9)
		{
			num = atoi(number);
			algo_trivial_division_s(num);
		}
		else if (numberLen >= 9 && numberLen <= 13)
		{
			remove_newline(number, numberLen);
			algo_trivial_division(number);
		}
		else if (numberLen > 13)
		{
			remove_newline(number, numberLen);
			algo_quadratic_sieve(number);
		}
	}

	free(number);
}
