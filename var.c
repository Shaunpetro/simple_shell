#include "shellhead.h"
/**
 * pt_chain - current char tested in buffer
 * @info: parameter struct with possible args
 * @buf: the charecter buffer
 * @p: current address in buffer
 *
 * Return: 1 char chain delimeter,
 *        oe 0 if not
 */

int pt_chain(info_t *info, char *buf, size_t *p)
{
	size_t f = *p;

	if (buf[f] == '|' && buf[f + 1] == '|')
	{
		buf[f] = 0;
		f++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[f] == '&' && buf[f + 1] == '&')
	{
		buf[f] = 0;
		f++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[f] == ';')
	{
		buf[f] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = f;
	return (1);
}

/**
 * chk_chain - checks if chain should continue
 * @info: parameter struct containing possible args
 * @buf: charecter buf
 * @p: address of curent position
 * @i: start pos
 * @len: length of buff
 *
 * Return: void
 */

void chk_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t f = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			f = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			f = len
		}
	}
	*p = f;
}

/**
 * alias_replace - replaces an alias in the string thats tokenized
 * @info: info parameter struct with possible args
 *
 * Return: 1 if replaced, otherwised 0
 */

int alias_replace(info_t *info)
{
	int e;
	list_t *node;
	char *p;

	for (e = 0; e < 10; e++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * var_replace - replaces variables in toke str
 * @info: parameter struct containing possible args
 *
 * Return: 1 replaced, 0 otherwise
 */

int var_replace(info_t *info)
{
	int e = 0;
	list_t *node;

	for (e = 0; info->argv[e]; e++)
	{
		if (info->argv[e][0] != '$' || !info->argv[e][1])
			continue;

		if (!_strcmp(info->argv[e], "$?"))
		{
			replace_string(&(info->argv[e]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[e], "$$"))
		{
			replace_string(&(info->argv[e]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[e][1], '=');
			if (node)
			{
				replace_string(&(info->argv[e]),
						_strdup(_strchr(node->str, '=') + 1));
				continue;
			}
			replace_string(&info->argv[e], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces a string
 * @pst: past adress of string
 * @new: address of new string
 *
 * Return: 1 for replaced or 0 otherwise
 */

int replace_string(char **pst, char *new)
{
	free(*pst);
	*pst = new;
	return (1);
}
