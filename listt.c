#include "shellhead.c"

/**
 * add_node - inserts node at the start of list
 * @head: pointer address to head
 * @str: string of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	mem_set((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _dupstr(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_end_node - inserts a node at the end of list
 * @head: address of the ptr
 * @str: string node
 * @num: number index used by history
 *
 * Return: sizae of list
 */

list_t *add_end_node(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	mem_set((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _dupstr(str);
		if (!new_node->str)
		{
			new_node->str = _dupstr(str);
			if (!new_node->str)
			{
				free(new_node);
				return (NULL);
			}
		}
		if (node)
		{
			while (node->next)
				node = node->next;
			node->next = new_node;
		}
		else
			*head = new_node;
	}
	return (new_node);
}

/**
 * print_liststr - prints only LL str
 * @fn: ptr to first node
 *
 * Return: size of list
 */

size_t print_liststr(const list_t *fn)
{
	size_t e = 0;

	while (fn)
	{
		_puts(fn->str ? fn->str : "(nil)");
		_puts("\n");
		fn = fn->next;
		e++;
	}
	return (e);
}

/**
 * delnode_at_index - deletes node at given index
 * @head: address of first ptr
 * @index: index of nde to remove
 *
 * Return: 1 success or 0 failed
 */

int delnode_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int e = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (e == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		e++;
		pre_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * freelist - frees all nodes
 * @headptr: ptr to the head node
 *
 * Return: void
 */

void freelist(list_t **headptr)
{
	list_t *node, *next_node, *head;

	if (!headptr || !*headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*headptr = NULL;
}

