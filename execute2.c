#include "main.h"

/**
 * execute_line - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int execute_line(data_shell *datash)
{
	int (*_builtin_)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	_builtin_ = _getbuiltin(datash->args[0]);

	if (_builtin_ != NULL)
		return (_builtin_(datash));

	return (_execute(datash));
}
