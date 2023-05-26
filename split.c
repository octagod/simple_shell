#include "main.h"

/**
 * swapchar_ - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swapchar_(char *input, int bool)
{
	int a;

	if (bool == 0)
	{
		a = 0;
		while (input[a])
		{
			if (input[a] == '|')
			{
				if (input[a + 1] != '|')
					input[a] = 16;
				else
					a++;
			}

			if (input[a] == '&')
			{
				if (input[a + 1] != '&')
					input[a] = 12;
				else
					a++;
			}
			a++;
		}
	}
	else
	{
		a = 0;
		while (input[a])
		{
			input[a] = (input[a] == 16 ? '|' : input[a]);
			input[a] = (input[a] == 12 ? '&' : input[a]);
			a++;
		}
	}
	return (input);
}

/**
 * addnodes_ - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void addnodes_(sep_list **head_s, line_list **head_l, char *input)
{
	int a;
	char *string;

	input = swapchar_(input, 0);

	a = 0;
	while (input[a])
	{
		if (input[a] == ';')
			add_sep_node_at_end(head_s, input[a]);

		if (input[a] == '|' || input[a] == '&')
		{
			add_sep_node_at_end(head_s, input[a]);
			a++;
		}
		a++;
	}

	string = _strtok(input, ";|&");
	while (string != NULL)
	{
		string = swapchar_(string, 1);
		addLineAtEndOfNode(head_l, string);
		string = _strtok(NULL, ";|&");
	}

}

/**
 * go_to_next - go to the next command string stored
 *
 * @list_s: separator list
 * @list_l: command string list
 * @datash: data structure
 * Return: no return
 */
void go_to_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int separation_of_loop;
	sep_list *list_of_arg_0;
	line_list *list_of_arg_1;

	separation_of_loop = 1;
	list_of_arg_0 = *list_s;
	list_of_arg_1 = *list_l;

	while (list_of_arg_0 != NULL && separation_of_loop)
	{
		if (datash->status == 0)
		{
			if (list_of_arg_0->separator == '&' || list_of_arg_0->separator == ';')
				separation_of_loop = 0;
			if (list_of_arg_0->separator == '|')
				list_of_arg_1 = list_of_arg_1->next, list_of_arg_0 = list_of_arg_0->next;
		}
		else
		{
			if (list_of_arg_0->separator == '|' || list_of_arg_0->separator == ';')
				separation_of_loop = 0;
			if (list_of_arg_0->separator == '&')
				list_of_arg_1 = list_of_arg_1->next, list_of_arg_0 = list_of_arg_0->next;
		}
		if (list_of_arg_0 != NULL && !separation_of_loop)
			list_of_arg_0 = list_of_arg_0->next;
	}

	*list_s = list_of_arg_0;
	*list_l = list_of_arg_1;
}

/**
 * _split - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int _split(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	addnodes_(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = _splitline(datash->input);
		loop = execute_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_to_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	unallocate_sep_list(&head_s);
	unallocate_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * _splitline - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **_splitline(char *input)
{
	size_t buffer_size;
	size_t a;
	char **array_of_tokken;
	char *string_tokken;

	buffer_size = TOK_BUFSIZE;
	array_of_tokken = malloc(sizeof(char *) * (buffer_size));
	if (array_of_tokken == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	string_tokken = _strtok(input, TOK_DELIM);
	array_of_tokken[0] = string_tokken;

	for (a = 1; string_tokken != NULL; a++)
	{
		if (a == buffer_size)
		{
			buffer_size += TOK_BUFSIZE;
			array_of_tokken = _reallocatedp(array_of_tokken, a, sizeof(char *) * buffer_size);
			if (array_of_tokken == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		string_tokken = _strtok(NULL, TOK_DELIM);
		array_of_tokken[a] = string_tokken;
	}

	return (array_of_tokken);
}
