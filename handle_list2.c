#include "main.h"

/**
 * addNodeToRvar - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var *addNodeToRvar(r_var **head, int lvar, char *val, int lval)
{
	r_var *new_rvar_list, *temp_;

	new_rvar_list = malloc(sizeof(r_var));
	if (new_rvar_list == NULL)
		return (NULL);

	new_rvar_list->len_var = lvar;
	new_rvar_list->val = val;
	new_rvar_list->len_val = lval;

	new_rvar_list->next = NULL;
	temp_ = *head;

	if (temp_ == NULL)
	{
		*head = new_rvar_list;
	}
	else
	{
		while (temp_->next != NULL)
			temp_ = temp_->next;
		temp_->next = new_rvar_list;
	}

	return (*head);
}

/**
 * unallocate_rvar_list - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void unallocate_rvar_list(r_var **head)
{
	r_var *temp_;
	r_var *current;

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
