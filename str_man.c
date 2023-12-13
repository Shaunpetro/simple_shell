#include "shellhead.h"

/**
 * cpy_str - copy a string
 * @dst: destination to copy to
 * @src: source of string
 *
 * Return: ptr to destination
 */

char *cpy_str(char *dst, char *src)
{
	int e = 0;

	if (dst == src || src == 0)
	{
		return (dst);
	}
	while (src[e])
	{
		dst[e] = src[e];
		e++;
	}
	dst[e] = 0;
	return (dst);
}

/**
 * _dupstr - string duplicator
 * @str: string to duplicate
 *
 * Return: ptr to duplicated string
 */

char *_dupstr(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; legnth--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - input str
 * @str: the string to print
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_putchar(str[e]);
		e++;
	}
}

/**
 * _putchar - writes the char "c" TSOUT
 * @c: the charecter to print
 *
 * Return: 1 success, -1 on error and set errno
 */

int _putchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(1, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}
