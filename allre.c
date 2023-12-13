#include "shellhead.h"

/**
 * set_mem - fills the memory with a constant byte
 * @b:bytes to fill
 * @p: ptr to memory area
 * @n: amount of bytes to be filled
 *
 * Return: p to memory
 */

char *set_mem(char *p, char b, unsigned int n)
{
	unsigned int e;

	for (e = 0; e < n; e++)
		p[e] = b;
	return (s);
}
/**
 * ssfree - frees a string of string
 * @ss: string of strings
 */

void ssfree(char **ss)
{
	char **a = ss;

	if (!ss)
	{
		return;
	}
	while (*ss)
		free(*ss++);
	free(a);
}
/**
 * _re_alloc - allocates a block of memory again
 * @ptr: pointer to preciously sllocated memory block
 * @old_size: byte suze ofprev block
 * @new_size: bytes of new mem block
 *
 * Return: pointer to old block
 */

void *_re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
