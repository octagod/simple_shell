#include "main.h"

/**
 * freedata_ - frees data structure
 *
 * @datash: data structure
 * Return: no return
 */
void freedata_(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * setdata_ - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 * Return: no return
 */
void setdata_(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = int_to_string(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, handle_signal);
	setdata_(&datash, av);
	shloop_(&datash);
	freedata_(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}