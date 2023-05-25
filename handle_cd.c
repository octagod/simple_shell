#include "main.h"

/**
 * cd_cmd_dot - changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */
void cd_cmd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *directory, *pwd_, *pwd_token;

	getcwd(pwd, sizeof(pwd));
	pwd_ = _strdup(pwd);
	set_env("OLDPWD", pwd_, datash);
	directory = datash->args[1];
	if (_compare(".", directory) == 0)
	{
		set_env("PWD", pwd_, datash);
		free(pwd_);
		return;
	}
	if (_compare("/", pwd_) == 0)
	{
		free(pwd_);
		return;
	}
	pwd_token = pwd_;
	_strrev(pwd_token);
	pwd_token = _strtok(pwd_token, "/");
	if (pwd_token != NULL)
	{
		pwd_token = _strtok(NULL, "\0");

		if (pwd_token != NULL)
			_strrev(pwd_token);
	}
	if (pwd_token != NULL)
	{
		chdir(pwd_token);
		set_env("PWD", pwd_token, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(pwd_);
}

/**
 * cd_cmd_to - changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */
void cd_cmd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *directory, *pwd_, *cp_directory;

	getcwd(pwd, sizeof(pwd));

	directory = datash->args[1];
	if (chdir(directory) == -1)
	{
		geterror_(datash, 2);
		return;
	}

	pwd_ = _strdup(pwd);
	set_env("OLDPWD", pwd_, datash);

	cp_directory = _strdup(directory);
	set_env("PWD", cp_directory, datash);

	free(pwd_);
	free(cp_directory);

	datash->status = 0;

	chdir(directory);
}

/**
 * cd_cmd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_cmd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * cd_cmd_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_cmd_home(data_shell *datash)
{
	char *pp_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pp_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", pp_pwd, datash);
		free(pp_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		geterror_(datash, 2);
		free(pp_pwd);
		return;
	}

	set_env("OLDPWD", pp_pwd, datash);
	set_env("PWD", home, datash);
	free(pp_pwd);
	datash->status = 0;
}

/**
 * cd_cmd - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_cmd(data_shell *datash)
{
	char *dir;
	int home, home2, double_dash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		home = _compare("$HOME", dir);
		home2 = _compare("~", dir);
		double_dash = _compare("--", dir);
	}

	if (dir == NULL || !home || !home2 || !double_dash)
	{
		cd_cmd_home(datash);
		return (1);
	}

	if (_compare("-", dir) == 0)
	{
		cd_cmd_previous(datash);
		return (1);
	}

	if (_compare(".", dir) == 0 || _compare("..", dir) == 0)
	{
		cd_cmd_dot(datash);
		return (1);
	}

	cd_cmd_to(datash);

	return (1);
}
