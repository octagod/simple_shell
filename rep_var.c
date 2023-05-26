#include "main.h"

/**
 * checkenv_ - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void checkenv_(r_var **h, char *in, data_shell *data)
{
	int y = 0, x, j, string_length_of_vector;
	char **_envr;

	_envr = data->_environ;
	while (_envr[y])
	{
		for (j = 1, x = 0; _envr[y][x]; x++)
		{
			if (_envr[y][x] == '=')
			{
				string_length_of_vector = _strlen(_envr[y] + x + 1);
				addNodeToRvar(h, j, _envr[y] + x + 1, string_length_of_vector);
				return;
			}

			if (in[j] == _envr[y][x])
				j++;
			else
				break;
		}
		y++;
	}

	while (in[j])
	{
		if (in[j] == ';' || in[j] == '\n'  || in[j] == ' ' || in[j] == '\t')
			break;
		j++;
	}

	addNodeToRvar(h, j, NULL, 0);
}

/**
 * checkvars_ - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last ptr_stat of the Shell
 * @data: data structure
 * Return: no return
 */
int checkvars_(r_var **h, char *in, char *st, data_shell *data)
{
	int a, list_argumenr_3, list_data;

	list_argumenr_3 = _strlen(st);
	list_data = _strlen(data->pid);

	for (a = 0; in[a]; a++)
	{
		if (in[a] == '$')
		{
			if (in[a + 1] == '?')
				addNodeToRvar(h, 2, st, list_argumenr_3), a++;
			else if (in[a + 1] == '$')
				addNodeToRvar(h, 2, data->pid, list_data), a++;
			else if (in[a + 1] == '\n')
				addNodeToRvar(h, 0, NULL, 0);
			else if (in[a + 1] == '\0')
				addNodeToRvar(h, 0, NULL, 0);
			else if (in[a + 1] == ' ')
				addNodeToRvar(h, 0, NULL, 0);
			else if (in[a + 1] == '\t')
				addNodeToRvar(h, 0, NULL, 0);
			else if (in[a + 1] == ';')
				addNodeToRvar(h, 0, NULL, 0);
			else
				checkenv_(h, in + a, data);
		}
	}

	return (a);
}

/**
 * replaceinput_ - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaceinput_(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *ptr_index;
	int a, j, k;

	ptr_index = *head;
	for (j = a = 0; a < nlen; a++)
	{
		if (input[j] == '$')
		{
			if (!(ptr_index->len_var) && !(ptr_index->len_val))
			{
				new_input[a] = input[j];
				j++;
			}
			else if (ptr_index->len_var && !(ptr_index->len_val))
			{
				for (k = 0; k < ptr_index->len_var; k++)
					j++;
				a--;
			}
			else
			{
				for (k = 0; k < ptr_index->len_val; k++)
				{
					new_input[a] = ptr_index->val[k];
					a++;
				}
				j += (ptr_index->len_var);
				a--;
			}
			ptr_index = ptr_index->next;
		}
		else
		{
			new_input[a] = input[j];
			j++;
		}
	}
	return (new_input);
}

/**
 * repvar_ - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *repvar_(char *input, data_shell *datash)
{
	r_var *head, *ptr_index;
	char *ptr_stat, *new_input;
	int old_length, new_length;

	ptr_stat = int_to_string(datash->status);
	head = NULL;

	old_length = checkvars_(&head, input, ptr_stat, datash);

	if (head == NULL)
	{
		free(ptr_stat);
		return (input);
	}

	ptr_index = head;
	new_length = 0;

	while (ptr_index != NULL)
	{
		new_length += (ptr_index->len_val - ptr_index->len_var);
		ptr_index = ptr_index->next;
	}

	new_length += old_length;

	new_input = malloc(sizeof(char) * (new_length + 1));
	new_input[new_length] = '\0';

	new_input = replaceinput_(&head, input, new_input, new_length);

	free(input);
	free(ptr_stat);
	unallocate_rvar_list(&head);

	return (new_input);
}
