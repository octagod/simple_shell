#include "main.h"

/**
 * deletecomment_ - deletes comments from the line_pointer
 *
 * @in: line_pointer string
 * Return: line_pointer without comments
 */
char *deletecomment_(char *in)
{
	int a = 0, number;

	number = 0;
	while (in[a])
	{
		if (in[a] == '#')
		{
			if (a == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[a - 1] == ' ' || in[a - 1] == '\t' || in[a - 1] == ';')
				number = a;
		}
		a++;
	}

	if (number != 0)
	{
		in = _reallocate(in, a, number + 1);
		in[number] = '\0';
	}

	return (in);
}

/**
 * shloop_ - repitition of shell
 * @datash: data relevant (av, line_pointer, args)
 *
 * Return: no return.
 */
void shloop_(data_shell *datash)
{
	int repitition, end_of_file_indicator;
	char *line_pointer;

	for (repitition = 1; repitition == 1;)
	{
		write(STDIN_FILENO, "#(Simple Shell)$$ ", 18);
		line_pointer = readline_(&end_of_file_indicator);
		if (end_of_file_indicator != -1)
		{
			line_pointer = deletecomment_(line_pointer);
			if (line_pointer == NULL)
				continue;

			if (check_syntax_err(datash, line_pointer) == 1)
			{
				datash->status = 2;
				free(line_pointer);
				continue;
			}
			line_pointer = repvar_(line_pointer, datash);
			repitition = _split(datash, line_pointer);
			datash->counter += 1;
			free(line_pointer);
		}
		else
		{
			repitition = 0;
			free(line_pointer);
		}
	}
}
