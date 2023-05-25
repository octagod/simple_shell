#include "main.h"

/**
 * compare_env - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int compare_env(const char *nenv, const char *name)
{
	int z;

	for (z = 0; nenv[z] != '='; z++)
	{
		if (nenv[z] != name[z])
		{
			return (0);
		}
	}

	return (z + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int z, err_num;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	err_num = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (z = 0; _environ[z]; z++)
	{
		/* If name and env are equal */
		err_num = compare_env(_environ[z], name);
		if (err_num)
		{
			ptr_env = _environ[z];
			break;
		}
	}

	return (ptr_env + err_num);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int k, j;

	for (k = 0; datash->_environ[k]; k++)
	{

		for (j = 0; datash->_environ[k][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[k], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
