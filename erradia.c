#include "shellhead.h"

/**
 * _erradia - concerts a str to int
 * @s: str to convert
 *
 * Return: 0 nothing converted or -1 error
 */

int _erradia(char *s)
{
	int e = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (e = 0; s[e] != '\0'; e++)
	{
		if (s[e] >= '0' && s[e] <= '9')
		{
			result *= 10;
			result += (s[e] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}
	return (result);
}

/**
 * print_error - error message to print
 * @info: struct parameter with possible arg's
 * @estr: string containing a specific error type
 *
 * Return: 0 no num str converted, -1 on error
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_puts(estr);
}

/**
 * print_d - print base 10 decimal num
 * @input: input
 * @fd: te file descriptor to wrtite to
 *
 * Return: number of charecters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int e, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putcar = _eputchar;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (e = 1000000000; e > 1; e /= 10)
	{
		if (_abs_ / e)
		{
			__putchar('0' + current / e);
			count++;
		}
		current %= e;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * convert_number - num converter
 * @num: number to convert
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	static car *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long int n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" :
		"0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
	{
		*--ptr = sign;
	}
	return (ptr);
}

/**
 * remove_comments - replace the first instance of
 *                   of comment with '\0'
 * @buf: address of the string to change
 *
 * Return: 0 always
 */

void remove_comments(char *buf)
{
	int e;

	for (e = 0; buf[e] != '\0'; e++)
		if (buf[e] == '#' && (!e || buf[e - 1] == ' '))
		{
			buf[e] = '\0';
			break;
		}
}
