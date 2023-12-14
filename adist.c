#include "shellhead.h"

/**
 * _mhist  - shows te history by list from 0,
 *           one cmonnand per line
 * @info: struct with possible arg's
 *
 * Return: 0 always
 */

int _mhist(info_t *info)
{
	char *p, c;
	int ret;

	p = _fcharstr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delnode_at_index(&(info->alias, node_swith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * salias - sets alias to str
 * @info: struct parameter with possible arg's
 * @str: alias str
 *
 * Return: 0 success, 1 error
 */

int salias(info_t *info, char *str)
{
	char *p;

	p = _fcharstr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_us(info, str));
	alias_us(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints the alias str
 * @node: node
 *
 * Return: 0 success or 1 error
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _fcharstr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - imatates te built in alias
 * @info: struct parameter with possible arg's
 *
 * Return: 0 always
 */

int _myalias(info_t *info)
{
	int e = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (e = 1; info->argv[e]; e++)
	{
		p = _fcharstr(info->argv[e], e++);
		if (p)
			set_alias(info, info->argv[e]);
		else
			print_alias(node_swith(info->alias, info->argv[e], '='));
	}
	return (0);
}
