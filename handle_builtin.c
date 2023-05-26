#include "main.h"

/**
 * _getbuiltin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*_getbuiltin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{"env", _env},
		{"exit", _exit_sh},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", cd_cmd},
		{"help", gethelp_},
		{NULL, NULL}};
	int x;

	x = 0;
	while (builtin[x].name)
	{
		if (_compare(builtin[x].name, cmd) == 0)
			break;
		x++;
	}

	return (builtin[x].f);
}

/**
 * geterror_ - calls the error according to the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int geterror_(data_shell *datash, int eval)
{
	char *err_;

	if (eval == -1)
	{
		err_ = env_error(datash);
	}
	else if (eval == 126)
	{
		err_ = path_126_err(datash);
	}
	else if (eval == 127)
	{
		err_ = error_notFound(datash);
	}
	else if (eval == 2)
	{
		if (_compare("exit", datash->args[0]) == 0)
			err_ = exit_shell_error(datash);
		else if (_compare("cd", datash->args[0]) == 0)
			err_ = get_cd_error(datash);
	}

	if (err_)
	{
		write(STDERR_FILENO, err_, _strlen(err_));
		free(err_);
	}

	datash->status = eval;
	return (eval);
}

/**
 * gethelp_ - function that retrieves help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
 */
int gethelp_(data_shell *datash)
{

	if (datash->args[1] == 0)
		general_help();
	else if (_compare(datash->args[1], "setenv") == 0)
		setenv_help();
	else if (_compare(datash->args[1], "env") == 0)
		env_help();
	else if (_compare(datash->args[1], "unsetenv") == 0)
		unsetenv_help();
	else if (_compare(datash->args[1], "help") == 0)
		_help();
	else if (_compare(datash->args[1], "exit") == 0)
		custom_exit_help();
	else if (_compare(datash->args[1], "cd") == 0)
		cd_help();
	else if (_compare(datash->args[1], "alias") == 0)
		alias_help();
	else
		write(STDERR_FILENO, datash->args[0],
			  _strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}

/**
 * bringline_ - assigns the line var for getline_
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bringline_(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_copy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * getline_ - Read inpt from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t getline_(char **lineptr, size_t *n, FILE *stream)
{
	int x;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char zed_char = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (zed_char != '\n')
	{
		x = read(STDIN_FILENO, &zed_char, 1);
		if (x == -1 || (x == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (x == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _reallocate(buffer, input, input + 1);
		buffer[input] = zed_char;
		input++;
	}
	buffer[input] = '\0';
	bringline_(lineptr, n, buffer, input);
	retval = input;
	if (x != 0)
		input = 0;
	return (retval);
}
