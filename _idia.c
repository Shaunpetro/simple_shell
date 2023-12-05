#include "shellhead.h"

/**
 * intactive - checks the mode of shell
 *             then return true
 * @info: struct address with possible arg's
 *
 * Return: 1 if shell is interactive or 0
 */

int intactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * pt_delm - checks if char is delimeter
 * @j: char to checl
 * @delm: delimeter str
 *
 * Return: 1 if tru, else 0
 */

int pt_delm(char j, char *delm)
{
	while (*delm)
	{
		if (*delm++ == j)
			return (1);
	}
	return (0);
}

/**
 * ptalpha - checks for alphabet char
 * @j: char to input
 *
 * Return: 1 if j aphebet else 0 if not
 */

int ptalpha(int j)
{
	if ((j >= 'a' && j <= 'z') || (j >= 'A' && j <= 'Z'))
	{
		return (1);
	}
	else
	return (0);
}

/**
 * _idia - convert string to interger
 * @s: string to conver
 *
 * Return: 0 if no no# in string, else the converted no#s
 */

int _idia(char *s)
{
	int e, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (e = 0; s[e] != '\0' && flag != 2; e++)
	{
		if (s[e] == '-')
			sign *= -1;
		if (s[e] >= '0' && s[e] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[e] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
