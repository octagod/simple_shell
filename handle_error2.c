#include "main.h"

/**
 * env_error - error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: err message.
 */
char *env_error(data_shell *datash)
{
	int len;
	char *err;
	char *ver_string;
	char *message;

	ver_string = int_to_string(datash->counter);
	message = ": Unable to add/remove from environment\n";
	len = _strlen(datash->av[0]) + _strlen(ver_string);
	len += _strlen(datash->args[0]) + _strlen(message) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver_string);
		return (NULL);
	}

	_copy(err, datash->av[0]);
	_concatstr(err, ": ");
	_concatstr(err, ver_string);
	_concatstr(err, ": ");
	_concatstr(err, datash->args[0]);
	_concatstr(err, message);
	_concatstr(err, "\0");
	free(ver_string);

	return (err);
}
/**
 * path_126_err - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The err string.
 */
char *path_126_err(data_shell *datash)
{
	int len;
	char *ver_string;
	char *err;

	ver_string = int_to_string(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_string);
	len += _strlen(datash->args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver_string);
		return (NULL);
	}
	_copy(err, datash->av[0]);
	_concatstr(err, ": ");
	_concatstr(err, ver_string);
	_concatstr(err, ": ");
	_concatstr(err, datash->args[0]);
	_concatstr(err, ": Permission denied\n");
	_concatstr(err, "\0");
	free(ver_string);
	return (err);
}
