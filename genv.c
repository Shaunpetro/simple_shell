#include "shellhead.h"

/**
 * _menv - current environment of sys
 * @info: struct with possible arg's
 *
 * Return: alwaus 0
 */

int _menv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _genv - gets the value of the env variables
 * @info: struct parameter with possible arg's
 * @name: name of env variable
 *
 * Return: value of env
 */

char *_genv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _msenv - set new env variable or modify exisiting
 * @info: struct parameter with possible arg's
 *
 * Return: 0 always
 */

int _msenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Wrong Number of Arguments. \n");
		return (1);
	}
	if (_senv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _musenv - remove environment variable
 * @info: struct with possible arg's
 *
 * Return: always 0
 */

int _musenv(info_t *info)
{
	int e;

	if (info->argc == 1)
	{
		_eputs("There aren't Enough Arguments. \n");
		return (1);
	}
	for (e = 1; e <= info->argc; e++)
		_usenv(info, info->argv[e]);
	return (0);
}
/**
 * pop_env_list - populates the environment LL
 * @info: struct with possible arg's
 *
 * Return: always 0
 */

int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t e;

	for (e = 0; environ[e]; e++)
		add_node_end(&node, environ[e], 0);
	info->env = node;
	return (0);
}
