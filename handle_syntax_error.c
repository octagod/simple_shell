#include "main.h"

/**
 * get_rep_char_num - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int get_rep_char_num(char *input, int i)
{
	if (*(input - 1) == *input)
		return (get_rep_char_num(input - 1, i + 1));

	return (i);
}

/**
 * _syntax_err - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int _syntax_err(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (_syntax_err(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = get_rep_char_num(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = get_rep_char_num(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (_syntax_err(input + 1, i + 1, *input));
}

/**
 * index_of_first_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int index_of_first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * prt_syntax_err - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void prt_syntax_err(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = int_to_string(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_copy(error, datash->av[0]);
	_concatstr(error, ": ");
	_concatstr(error, counter);
	_concatstr(error, msg2);
	_concatstr(error, msg);
	_concatstr(error, msg3);
	_concatstr(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_err - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_err(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = index_of_first_char(input, &begin);
	if (f_char == -1)
	{
		prt_syntax_err(datash, input, begin, 0);
		return (1);
	}

	i = _syntax_err(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		prt_syntax_err(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
