#include "main.h"

/**
 * readline_ - reads the input string.
 *
 * @i_eof: return value of getline function
 * Return: input string
 */
char *readline_(int *i_eof)
{
	char *string_input = NULL;
	size_t size_of_buffer = 0;

	*i_eof = getline(&string_input, &size_of_buffer, stdin);

	return (string_input);
}
