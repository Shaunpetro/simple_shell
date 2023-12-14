#include "shellhead.h"

/**
 * _mexit - exit shell
 * @info: struct parameter with possible arg's
 *
 * Return: exit with the exit status
 */

int _mexit(info_t *info)
{
	int exitchk;

	if (info->argv[1])
	{
		exitchk = _erradia(info->argv[1]);
		if (exitchk == -1)
		{
			info->status = 2;
			print_error(info, "Unallowed Number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erradia(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - canges the current directory
 * @info: struct containing possible arg's
 *
 * Return: 0 always
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	if (!s)
		_puts("TODO: >>get dierectory failure msg here<<\n");
	if (!info->argv[1])
	{
		dir = _genv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _genv(info,
							"PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strcomp(argv[1], "-") == 0)
	{
		if (!_genv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_genv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _genv(info,
						"OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Oops, can not change directory to ");
		_puts(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_senv(info, "OLDPWD", _genv(info, "PWD="));
		_senv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _mhelp - helper to change current directory
 * @info: struct wit possible arg's
 *
 * Return: 0 alwasy
 */

int _mhelp(info_t *info)
{
	char **arr_arg;

	arr_arg = info->argv;
	_puts("Oops! Help works fine, seems the function isn't executed yet\n");
	if (0)
		_puts(*arr_arg);
	return (0);
}
