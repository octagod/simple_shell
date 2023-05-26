#include "main.h"

/**
 * freedata_ - frees data structure
 *
 * @datash: data structure
 * Return: no return
 */
void freedata_(data_shell *datash)
{
	unsigned int a = 0;

	while (datash->_environ[a])
	{
		free(datash->_environ[a]);
		a++;
	}

	free(datash->pid);
	free(datash->_environ);
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
	unsigned int a = 0;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	while (environ[a])
		a++;

	datash->_environ = malloc(sizeof(char *) * (a + 1));

	a = 0;
	while (environ[a])
	{
		datash->_environ[a] = _strdup(environ[a]);
		a++;
	}

	datash->_environ[a] = NULL;
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
