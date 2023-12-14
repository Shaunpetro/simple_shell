#include "shellhead.h"

/**
 * genv - returns a copy of array string of the env
 * @info: struct parameter with possible arg's
 *
 * Return: 0 always
 */

char **genv(info_t *info)
{
	if (!info->env || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _usenv - removes env vars
 * @info: struct with possible arg's
 * @var: the string env var property
 *
 * Return: 1 deleted, 0 otherwise
 */

int _usenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t e = 0;
	char *p;

	if (!node || !var)
	{
		return (0);
	}
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delnode_at_index(&(info->env), e);
			e = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		e++;
	}
	return (info->env_changed);
}

/**
 * _senv - new environment var to initialize
 * @info: struct with possible arg's
 * @var: str var property
 * @value: str environment value
 *
 * Return: 0 always
 */

int _senv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	cpy_str(buf, var);
	_catstr(buf, "=");
	_catstr(buf, value);
	node = info->env;

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
