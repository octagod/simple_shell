#include "main.h"

/**
 * env_help - Help information for the builtin env
 * Return: no return
 */
void env_help(void)
{
	char *hlp = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));

}
/**
 * setenv_help - Help information for the builtin setenv
 * Return: no return
 */
void setenv_help(void)
{

	char *hlp = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "int replace)\n\t";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
/**
 * unsetenv_help - Help information for the builtin unsetenv
 * Return: no return
 */
void unsetenv_help(void)
{
	char *hlp = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}


/**
 * general_help - Entry point for hlp information for the hlp builtin
 * Return: no return
 */
void general_help(void)
{
	char *hlp = "#(Simple Shell)$$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "These commands are defined internally.Type 'hlp' to see the list";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Type 'hlp name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "unsetenv [variable]\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
/**
 * custom_exit_help - Help information fot the builint exit
 * Return: no return
 */
void custom_exit_help(void)
{
	char *hlp = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
