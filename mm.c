#include "shellhead.h"

/**
 * bfree - frees & zeros a ptr address
 * @ptr: address of ptr
 *
 * Return: 1 freed, otherwise 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
