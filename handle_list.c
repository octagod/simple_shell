#include "main.h"

/**
 * add_sep_node_at_end - adds a separator found at the end
 * of a sep_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sep_list *add_sep_node_at_end(sep_list **head, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * unallocate_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void unallocate_sep_list(sep_list **head)
{
	sep_list *temp_;
	sep_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp_ = current) != NULL)
		{
			current = current->next;
			free(temp_);
		}
		*head = NULL;
	}
}

/**
 * addLineAtEndOfNode - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *addLineAtEndOfNode(line_list **head, char *line)
{
	line_list *new_line_list, *temp_;

	new_line_list = malloc(sizeof(line_list));
	if (new_line_list == NULL)
		return (NULL);

	new_line_list->line = line;
	new_line_list->next = NULL;
	temp_ = *head;

	if (temp_ == NULL)
	{
		*head = new_line_list;
	}
	else
	{
		while (temp_->next != NULL)
			temp_ = temp_->next;
		temp_->next = new_line_list;
	}

	return (*head);
}

/**
 * unallocate_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void unallocate_line_list(line_list **head)
{
	line_list *temp_;
	line_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp_ = current) != NULL)
		{
			current = current->next;
			free(temp_);
		}
		*head = NULL;
	}
}
