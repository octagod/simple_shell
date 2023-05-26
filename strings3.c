#include "main.h"

/**
 * _strrev - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void _strrev(char *s)
{
	int location = 0, a, b;
	char *line_string, string_copy;

	while (location >= 0)
	{
		if (s[location] == '\0')
			break;
		location++;
	}
	line_string = s;

	for (a = 0; a < (location - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			string_copy = *(line_string + b);
			*(line_string + b) = *(line_string + (b - 1));
			*(line_string + (b - 1)) = string_copy;
		}
	}
}
