#include "shell.h"

/**
* _myexit - is to exits the shell
* @info: contains potential arguments for maintaining
* constant function prototype.
* Return: this exit with a given a status
* (0) if info.argv[0] != "exit"
* Function use to exit the shell. Takes a structure info as an argument,
* that may contain potential arguments for the exit command.
* once the command is entered
* the function is to return 0 without exiting the shell.
* If the command is "exit", the function will
* exits the shell with a given exit status.
*/

int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is a given exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
* _mycd - will change the current dir of the process
* @info: contains potential arguments for maintaining
* a constant function prototype.
* Return: Always 0
* Function use to change the current dir of the process. It takes
* in a structure info as an argument,
* that may contain potential arguments for the
* change dir (cd) command. The function will changes
* the directory to the specified dir in the arguments,
* or to the home directory if there is no dir provided in the argument.
* The function always returns 0,
* in term of the function prototype.
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
* @info: contains potential arguments for maintaining
* a constant function prototype.
* Return: Always 0
* Function is used to display the shell help message. It takes
* structure info as an argument, that may contain potential arguments when
* the help command is intiated. This function will
* display information about the shell, including
* list of in-built commands and with their descriptions.
* The function always returns 0,
* in terms of the function prototype.
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
