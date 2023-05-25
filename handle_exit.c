#include "main.h"

/**
 * _exit_sh - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int _exit_sh(data_shell *datash)
{
	unsigned int ustatus;
	int is_int;
	int _strlen_;
	int big_number;

	if (datash->args[1] != NULL)
	{
		ustatus = parseint(datash->args[1]);
		is_int = _isdigit(datash->args[1]);
		_strlen_ = _strlen(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_int || _strlen_ > 10 || big_number)
		{
			geterror_(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}
