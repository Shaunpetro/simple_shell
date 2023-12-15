#include "shellhead.h"

/**
 * list_len - lenths of LL
 * @t: first node ptr
 *
 * Return: size of list
 */

size_t list_len(const list_t *t)
{
	size_t e = 0;

	while (t)
	{
		t = t->next;
		e++;
	}
	return (e);
}

/**
 * lt_strings - returns arr of strings of the lidt
 * @head: first node ptr
 *
 * Return: array of strings
 */

char **lt_strings(list_t *head)
{
	list_t *node = head;
	size_t e = list_len(head), f;
	char **strs;
	char *str;

	if (!head || !e)
		return (NULL);
	strs = malloc(sizeof(char *) * (e + 1));
	if (!strs)
		return (NULL);
	for (e = 0; node; node = node->next, e++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (f = 0; f < e; f++)
				free(strs[f]);
			free(strs);
			return (NULL);
		}
		str = cpy_str(str, node->str);
		strs[e] = str;
	}
	strs[e] = NULL;
	return (strs);
}

/**
 * print_list - prints all LL elements
 * @t: first node ptr
 *
 * Return: size of list
 */

size_t print_list(const list_t *t)
{
	size_t e = 0;

	while (t)
	{
		_puts(convert_number(t->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(t->str ? t->str : "(nil)");
		_puts("\n");
		t = t->next;
		e++;
	}
	return (e);
}

/**
 * node_swith - return node str
 * @node: node to ptr head list
 * @prefix: prefix str to match
 * @c: next charecter after preficx
 *
 * Return: matched node, NULL otehrwise
 */

list_t *node_swith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
		{
			return (node);
			node = node->next;
		}
	}
	return (NULL);
}

/**
 * get_node_index - gets the node of the index
 * @head: head list pointer
 * @node: node pointer
 *
 * Return: index of node, otherwise -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t e = 0;

	while (head)
	{
		if (head == node)
			return (e);
		head = head->next;
		e++;
	}
	return (-1);
}
