#include "shellhead.h"

/**
 * hsh - shell loop
 * @info: struct parameter with possible arg's
 * @av: arg vector
 *
 * Return: 0 success, 1 error & err code
 */

int hsh(info_t *info, char **av)
{
	ssize_t e = 0;
	int buin_ret = 0;

	while (e != -1 && buin_ret != -2)
	{
		cl_info(info);
		if (intactive(info))
			_puts("m$ ");
		_eputchar(BUF_FLUSH);
		e = getinput(info);
		if (e != -1)
		{
			set_info(info, av);
			buin_ret = find_buin(info);
			if (buin_ret == -1)
				find_cmd(info);
		}
		else if (intactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	whist(info);
	free_info(info, 1);
	if (!intactive(info) && info->status)
		exit(info->status);
	if (buin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (buin_ret);
}

/**
 * find_buin - finder of built in command
 * @info: structure parameter with possible arg's
 *
 * Return: -1 not found, 1 found not success
 *         or 2 points to exit
 */

int find_buin(info_t *info)
{
	int e, built_in_ret = -1;
	buin_table builtintbl[] = {
		{"exit", _mexit}, {"env", _menv},
		{"help", _mhelp}, {"history", _myhist},
		{"setenv", _msenv}, {"unsetenv", _musenv},
		{"cd", _mycd}, {"alias", _myalias},
		{NULL, NULL}
	};
	for (e = 0; builtintbl[e].type; e++)
		if (strcomp(info->argv[0], builtintbl[e].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[e].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - cmd to find in path
 * @info: parameter struct with possible arg's
 *
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int e, f;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (e = 0, f = 0; info->arg[e]; e++)
		if (!pt_delm(info->arg[e], "\t\n"))
			f++;
	if (!f)
		return;
	path = find_path(info, _genv(info, "PATH= "), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkcmd(info);
	}
	else
	{
		if ((intactive(info) || _genv(info, "PATH= ")
					|| info->argv[0][0] == '/') && pt_cmd(info, info->argv[0]))
			forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "NOT found. \n");
		}
	}
}

/**
 * forkcmd - forks an executable thread to run cmd
 * @info: struct parameter with return structure
 *
 * Return: void
 */

void forkcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("ERROR Description: ");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCESS)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "The Permission is Denied. \n");
		}
	}
}
