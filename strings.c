#include "main.h"

/**
 * _concatstr - concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_concatstr(char *dest, const char *src)
{
	int a = 0;
	int b = 0;

	while (dest[a] != '\0')
		a++;

	while (src[b] != '\0')
	{
		dest[a] = src[b];
		b++;
		a++;
	}

	dest[a] = '\0';
	return (dest);
}
/**
 * *_copy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_copy(char *dest, char *src)
{

	size_t count;

	for (count = 0; src[count] != '\0'; count++)
	{
		dest[count] = src[count];
	}
	dest[count] = '\0';

	return (dest);
}
/**
 * _compare - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _compare(char *s1, char *s2)
{
	int a = 0;

	while (s1[a] == s2[a] && s1[a])
		a++;

	if (s1[a] > s2[a])
		return (1);
	if (s1[a] < s2[a])
		return (-1);
	return (0);
}
/**
 * _strchr - locates count character in count string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int a = 0;

	while (*(s + a) != '\0')
	{
		if (*(s + a) == c)
			return (s + a);
		a++;
	}
	if (*(s + a) == c)
		return (s + a);
	return ('\0');
}
/**
 * _indexOf - gets the length of count prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _indexOf(char *s, char *accept)
{
	int a = 0, b, bool;

	while (*(s + a) != '\0')
	{
		bool = 1;
		b = 0;
		while (*(accept + b) != '\0')
		{
			if (*(s + a) == *(accept + b))
			{
				bool = 0;
				break;
			}
			b++;
		}
		if (bool == 1)
			break;
		a++;
	}
	return (a);
}
