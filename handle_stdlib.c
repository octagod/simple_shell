#include "main.h"

/**
 * get_num_len - Get the length of a number.
 * @n: type int number.
 * Return: length of a number.
 */
int get_num_len(int n)
{
	int length = 1;
	unsigned int number_one;

	if (n < 0)
	{
		number_one = n * -1;
		length++;
	}
	else
	{
		number_one = n;
	}
	for (; number_one > 9;)
	{
		number_one = number_one / 10;
		length++;
	}

	return (length);
}
/**
 * int_to_string - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *int_to_string(int n)
{
	unsigned int number_one;
	int length = get_num_len(n);
	char *string_pointer;

	string_pointer = malloc(sizeof(char) * (length + 1));
	if (string_pointer == 0)
		return (NULL);

	*(string_pointer + length) = '\0';

	if (n < 0)
	{
		string_pointer[0] = '-';
		number_one = n * -1;
	}
	else
	{
		number_one = n;
	}

	length--;
	for (; number_one > 0; )
	{
		*(string_pointer + length) = (number_one % 10) + '0';
		length--;
		number_one = number_one / 10;
	}
	return (string_pointer);
}

/**
 * parseint - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int parseint(char *s)
{
	unsigned int string_counter = 0, string_length = 0, x= 0, y= 1, z= 1, a;

	for (; *(s + string_counter) != '\0';)
	{
		if (string_length > 0 && (*(s + string_counter) < '0' || *(s + string_counter) > '9'))
			break;

		if (*(s + string_counter) == '-')
			y*= -1;

		if ((*(s + string_counter) >= '0') && (*(s + string_counter) <= '9'))
		{
			if (string_length > 0)
				z*= 10;
			string_length++;
		}
		string_counter++;
	}

	a = string_counter - string_length;
	while (a < string_counter)
	{
		x= x+ ((*(s + a) - 48) * z);
		z/= 10;
		a++;
	}
	return (x* y);
}
