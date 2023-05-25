#include "main.h"

/**
 * deletecomment_ - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *deletecomment_(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _reallocate(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shloop_ - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shloop_(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "#(Simple Shell)$$ ", 18);
		input = readline_(&i_eof);
		if (i_eof != -1)
		{
			input = deletecomment_(input);
			if (input == NULL)
				continue;

			if (check_syntax_err(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = repvar_(input, datash);
			loop = _split(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
