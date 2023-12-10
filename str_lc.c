#include "shellhead.h"

/**
 * str_len - length of a sring to return
 * @s: the string to check
 *
 * Return: length of string
 */

int str_len(char *s)
{
	int e = 0;

	if (!s)
		return (0);
	while (*s++)
		e++;
	return (e);
}

/**
 * strcomp - func to compare 2 strings
 * @s_1: first astring
 * @s_2: second string
 *
 * Return: - if s_1<s_2,
 *         + if s_1>s_2
 *         or 0 if s_1=s_2
 */

int strcomp(char *s_1, char *s_2)
{
	while (*s_1 && *s_2)
	{
		if (*s_1 != *s_2)

			return (*s_1 - *s_2);
		s_1++;
		s_2++;
	}
	if (*s_1 == *s_2)
		return (0);
	else
		return (*s_1 < *s_2 ? -1 : 1);
}

/**
 * starts_with - needle in hastack to check
 * @haystack: the string haystack to check
 * @needle: the substring to find
 *
 * Return: next haystack char in address
 *         otherwise NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _catstr - copies two strings
 * @dst: destination of  of buffer
 * @src: source of buffer
 *
 * Return: ptr to destination of buffer
 */

char *_catstr(char *dst, char *src)
{
	char *ret = dst;

	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (ret);
}
