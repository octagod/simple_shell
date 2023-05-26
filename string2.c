#include "main.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *s)
{
	char *update;
	size_t length_of_string;

	length_of_string = _strlen(s);
	update = malloc(sizeof(char) * (length_of_string + 1));
	if (update == NULL)
		return (NULL);
	cpy_info(update, s, length_of_string + 1);
	return (update);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int length_of_string;

	for (length_of_string = 0; s[length_of_string] != 0; length_of_string++)
	{
	}
	return (length_of_string);
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int a = 0, j = 0, k = 0;

	while (str[a])
	{
		while (delim[j])
		{
			if (str[a] == delim[j])
			{
				k++;
				break;
			}
			j++;
		}
		a++;
	}
	if (a == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
	static char *cut, *end_point;
	char *start_point;
	unsigned int a, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		cut = str;
		a = _strlen(str);
		end_point = &str[a];
	}
	start_point = cut;
	if (start_point == end_point)
		return (NULL);

	for (bool = 0; *cut; cut++)
	{
		if (cut != start_point)
			if (*cut && *(cut - 1) == '\0')
				break;
		for (a = 0; delim[a]; a++)
		{
			if (*cut == delim[a])
			{
				*cut = '\0';
				if (cut == start_point)
					start_point++;
				break;
			}
		}
		if (bool == 0 && *cut)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (start_point);
}

/**
 * _isdigit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	unsigned int a;

	for (a = 0; s[a]; a++)
	{
		if (s[a] < 48 || s[a] > 57)
			return (0);
	}
	return (1);
}
