#include "rsa.h"

void remove_newline(char *str, size_t len)
{
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}
