#include "shellhead.h"

/**
 * *cpy_nstr - copy the nth string
 * @dst: destination of the str
 * @n: amount of char to copy
 * @src: the source of the str
 *
 * Return: the copied string
 */

char *cpy_nstr(char *dst, char *src, int n)
{
	int e, f;
	char *s = dst;

	e = 0;
	while (src[e] != '\0' && e < n - 1)
	{
		dst[e] = src[e];
		e++;
	}
	if (e < n)
	{
		f = e;
		while (f < n)
		{
			dst[f] = '\0';
			f++;
		}
	}
	return (s);
}

/**
 * cat_nstr - copies two strings
 * @dst: destination
 * @src: source to copy from
 * @n: max amount of str to copy
 *
 * Return: the cocatinated strings
 */

char *cat_nstr(char *dst, char *src, int n)
{
	int e, f;
	char *s = dst;

	e = 0;
	f = 0;
	while (dst[e] != '\0')
		e++;
	while (src[f] != '\0' && f < n)
	{
		dst[e] = src[f];
		e++;
		f++;
	}
	if (f < n)
	{
		dst[e] = '\0';
	}
	return (s);
}

/**
 * *_fcharstr - locates a char in a string
 * @s: the string to parse
 * @c: the char to look for
 *
 * Return: ptr to the memory of str
 */

char *_fcharstr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
