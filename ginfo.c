#include "shellhead.h"

/**
 * cl_info - initiallses info_t struct
 * @info: struct parameter with possible arg's
 */

void cl_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info_set - intialize inor_t struct
 * @info: struct with possible arg's
 * @av: argument vector
 */

void info_set(info_t *info, char **av)
{
	int e = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtwrd(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _dupstr(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (e = 0; info->argv && info->argv[e]; e++)
			info->argc = e;
		alias_replace(info);
		var_replace (info);
	}
}

/**
 * ffinfo - releases info struct feilds
 * @info: struct address to free
 * @all: conditions of freeing all feilds
 */

void ffinfo(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freelist(&(info->env));
		if (info->history)
			freelist(&(info->history));
		if (info->alias)
			freelist(&(info->alias));

		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
