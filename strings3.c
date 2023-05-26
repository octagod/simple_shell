#include "main.h"

/**
 * _strrev - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void _strrev(char *s)
{
	int index = 0, x, y;
	char *word, short_time;

	for (; index >= 0; index++)
	{
		if (s[index] == '\0')
			break;
	}
	word = s;
	x = 0;
	while (x < (index - 1))
	{
		for (y = x + 1; y > 0; y--)
		{
			short_time = *(word + y);
			*(word + y) = *(word + (y - 1));
			*(word + (y - 1)) = short_time;
		}
		x++;
	}
}
