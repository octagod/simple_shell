#include "main.h"

/**
 * is_crr_dir - checks ":" if is in the current directory.
 * @location: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the location is searchable in the cd, 0 otherwise.
 */
int is_crr_dir(char *location, int *x)
{
	if (location[*x] == ':')
		return (1);

	while (location[*x] != ':' && location[*x])
	{
		*x += 1;
	}

	if (location[*x])
		*x += 1;

	return (0);
}

/**
 * _locate_cmd - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_locate_cmd(char *cmd, char **_environ)
{
	char *_path, *print_path, *dir, *tok;
	int dirLen, cmd_len, y;
	struct stat st;

	_path = _getenv("PATH", _environ);
	if (_path)
	{
		print_path = _strdup(_path);
		cmd_len = _strlen(cmd);
		tok = _strtok(print_path, ":");
		y = 0;
		while (tok != NULL)
		{
			if (is_crr_dir(_path, &y))
				if (stat(cmd, &st) == 0)
					return (cmd);
			dirLen = _strlen(tok);
			dir = malloc(dirLen + cmd_len + 2);
			_copy(dir, tok);
			_concatstr(dir, "/");
			_concatstr(dir, cmd);
			_concatstr(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(print_path);
				return (dir);
			}
			free(dir);
			tok = _strtok(NULL, ":");
		}
		free(print_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * _isexec - determines if is an executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int _isexec(data_shell *datash)
{
	struct stat st;
	int x;
	char *value;

	value = datash->args[0];
	for (x = 0; value[x]; x++)
	{
		if (value[x] == '.')
		{
			if (value[x + 1] == '.')
				return (0);
			if (value[x + 1] == '/')
				continue;
			else
				break;
		}
		else if (value[x] == '/' && x != 0)
		{
			if (value[x + 1] == '.')
				continue;
			x++;
			break;
		}
		else
			break;
	}
	if (x == 0)
		return (0);

	if (stat(value + x, &st) == 0)
	{
		return (x);
	}
	geterror_(datash, 127);
	return (-1);
}

/**
 * cmd_error_check - verifies if user has permissions to access
 *
 * @dest_dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */
int cmd_error_check(char *dest_dir, data_shell *datash)
{
	if (dest_dir == NULL)
	{
		geterror_(datash, 127);
		return (1);
	}

	if (_compare(datash->args[0], dest_dir) != 0)
	{
		if (access(dest_dir, X_OK) == -1)
		{
			geterror_(datash, 126);
			free(dest_dir);
			return (1);
		}
		free(dest_dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			geterror_(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * _execute - executes command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */
int _execute(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int pos;
	int exec;
	char *dir;
	(void)wpd;

	exec = _isexec(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _locate_cmd(datash->args[0], datash->_environ);
		if (cmd_error_check(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _locate_cmd(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		while (!WIFEXITED(pos) && !WIFSIGNALED(pos))
		{
			wpd = waitpid(pd, &pos, WUNTRACED);
		}
	}

	datash->status = pos / 256;
	return (1);
}
