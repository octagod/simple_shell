#include "main.h"

/**
 * _help - Help information for the builtin hlp.
 * Return: no return
 */
void _help(void)
{
	char *hlp = "hlp: hlp [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
/**
 * alias_help - Help information for the builtin alias.
 * Return: no return
 */
void alias_help(void)
{
	char *hlp = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
/**
 * cd_help - Help information for the builtin alias.
 * Return: no return
 */
void cd_help(void)
{
	char *hlp = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
