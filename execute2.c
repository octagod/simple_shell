#include "main.h"

/**
 * execute_line - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int execute_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = _getbuiltin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (_execute(datash));
}
