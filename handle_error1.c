#include "main.h"

/**
 * strcat_cd_error - function that concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd_error(data_shell *datash, char *msg,
		char *error, char *ver_str)
{
	char *flag;

	_copy(error, datash->av[0]);
	_concatstr(error, ": ");
	_concatstr(error, ver_str);
	_concatstr(error, ": ");
	_concatstr(error, datash->args[0]);
	_concatstr(error, msg);
	if (datash->args[1][0] == '-')
	{
		flag = malloc(3);
		flag[0] = '-';
		flag[1] = datash->args[1][1];
		flag[2] = '\0';
		_concatstr(error, flag);
		free(flag);
	}
	else
	{
		_concatstr(error, datash->args[1]);
	}

	_concatstr(error, "\n");
	_concatstr(error, "\0");
	return (error);
}

/**
 * get_cd_error - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *get_cd_error(data_shell *datash)
{
	int len, length_ID;
	char *err, *ver_str, *msg;

	ver_str = int_to_string(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		length_ID = 2;
	}
	else
	{
		msg = ": can't cd to ";
		length_ID = _strlen(datash->args[1]);
	}

	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(ver_str) + _strlen(msg) + length_ID + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}

	err = strcat_cd_error(datash, msg, err, ver_str);

	free(ver_str);

	return (err);
}

/**
 * error_notFound - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_notFound(data_shell *datash)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = int_to_string(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	_copy(err, datash->av[0]);
	_concatstr(err, ": ");
	_concatstr(err, ver_str);
	_concatstr(err, ": ");
	_concatstr(err, datash->args[0]);
	_concatstr(err, ": not found\n");
	_concatstr(err, "\0");
	free(ver_str);
	return (err);
}

/**
 * exit_shell_error - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *exit_shell_error(data_shell *datash)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = int_to_string(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_copy(err, datash->av[0]);
	_concatstr(err, ": ");
	_concatstr(err, ver_str);
	_concatstr(err, ": ");
	_concatstr(err, datash->args[0]);
	_concatstr(err, ": Illegal number: ");
	_concatstr(err, datash->args[1]);
	_concatstr(err, "\n\0");
	free(ver_str);

	return (err);
}
