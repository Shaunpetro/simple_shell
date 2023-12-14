#include "shellhead.h"

/**
 * _eputs - prints an input string
 * @str: string to print
 *
 * Return: nothing
 */

void _eputs(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_eputchar(str[e]);
		e++;
	}
}

/**
 * _eputchar - writes a charecter c to STDERR
 * @c: the char to print
 *
 * Return: 1 success, -1 error
 *         then set errno accordingly
 */

int _eputchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(2, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 * _putfd - writes the c to given fd
 * @c: char to write
 * @fd: file descritor
 *
 * Return: 1 success, -1 error
 *        & set errno appropriately
 */

int _putfd(char c, int fd)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(fd, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 * _putsfd - prints an input str
 * @str: string to print
 * @fd: file descriptor
 *
 * Return: number of charecter to input
 */

int _putsfd(char *str, int fd)
{
	int e = 0;

	if (!str)
		return (0);
	while (*str)
		e += _putfd(*str++, fd);
	return (e);
}
