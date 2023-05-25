#include "main.h"

/**
 * cpy_env_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new_env env or alias.
 */
char *cpy_env_info(char *name, char *value)
{
	int name_length, val_length, length;
	char *new_env;

	name_length = _strlen(name);
	val_length = _strlen(value);
	length = name_length + val_length + 2;
	new_env = malloc(sizeof(char) * (length));
	_copy(new_env, name);
	_concatstr(new_env, "=");
	_concatstr(new_env, value);
	_concatstr(new_env, "\0");

	return (new_env);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int x;
	char *env_, *env_name;

	for (x = 0; datash->_environ[x]; x++)
	{
		env_name = _strtok(env_, "=");
		env_ = _strdup(datash->_environ[x]);
		if (_compare(env_name, name) == 0)
		{
			free(datash->_environ[x]);
			datash->_environ[x] = cpy_env_info(env_name, value);
			free(env_);
			return;
		}
		free(env_);
	}

	datash->_environ = _reallocatedp(datash->_environ,
			x, sizeof(char *) * (x + 2));
	datash->_environ[x] = cpy_env_info(name, value);
	datash->_environ[x + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		geterror_(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_env;
	char *env_, *env_name;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		geterror_(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		env_ = _strdup(datash->_environ[i]);
		env_name = _strtok(env_, "=");
		if (_compare(env_name, datash->args[1]) == 0)
		{
			k = i;
		}
		free(env_);
	}
	if (k == -1)
	{
		geterror_(datash, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_env;
	return (1);
}
