#include "main.h"

/**
 * get_rep_char_num - string_counts the repetitions of a char
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
	int string_count;

	string_count = 0;
	if (*input == '\0')
		return (0);

	if (*input == '\t' || *input == ' ')
		return (_syntax_err(input + 1, i + 1, last));

	if (*input == ';')
		if (last == ';' || last == '&' || last == '|')
			return (i);

	if (*input == '|')
	{
		if (last == '&' || last == ';')
			return (i);

		if (last == '|')
		{
			string_count = get_rep_char_num(input, 0);
			if (string_count == 0 || string_count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == '|' || last == ';')
			return (i);

		if (last == '&')
		{
			string_count = get_rep_char_num(input, 0);
			if (string_count == 0 || string_count > 1)
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

	*i = 0;
	while (input[*i])
	{
		if (input[*i] == ' ' || input[*i] == '\t')
		{
			*i += 1;
			continue;
		}

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
		{
			*i += 1;
			return (-1);
		}

		*i += 1;
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
 * @bool: to control report error
 * Return: no return
 */
void prt_syntax_err(data_shell *datash, char *input, int i, int bool)
{
	char *report, *report2, *report3, *error, *string_counter;
	int string_length;

	if (input[i] == ';')
	{
		if (bool == 0)
			report = (input[i + 1] == ';' ? ";;" : ";");
		else
			report = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		report = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		report = (input[i + 1] == '&' ? "&&" : "&");

	report2 = ": Syntax error: \"";
	report3 = "\" unexpected\n";
	string_counter = int_to_string(datash->counter);
	string_length = _strlen(datash->av[0]) + _strlen(string_counter);
	string_length += _strlen(report) + _strlen(report2) + _strlen(report3) + 2;

	error = malloc(sizeof(char) * (string_length + 1));
	if (error == 0)
	{
		free(string_counter);
		return;
	}
	_copy(error, datash->av[0]);
	_concatstr(error, ": ");
	_concatstr(error, string_counter);
	_concatstr(error, report2);
	_concatstr(error, report);
	_concatstr(error, report3);
	_concatstr(error, "\0");

	write(STDERR_FILENO, error, string_length);
	free(error);
	free(string_counter);
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
	int start = 0;
	int function_charcter = 0;
	int i = 0;

	function_charcter = index_of_first_char(input, &start);
	if (function_charcter == -1)
	{
		prt_syntax_err(datash, input, start, 0);
		return (1);
	}

	i = _syntax_err(input + start, 0, *(input + start));
	if (i != 0)
	{
		prt_syntax_err(datash, input, start + i, 1);
		return (1);
	}

	return (0);
}
