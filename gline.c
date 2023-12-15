#include "shellhead.h"

/**
 * inbuf - chained command buff
 * @info: struct parameter with possible arg's
 * @buf: buffer address
 * @len: address of len var
 *
 * Return: number of bytes read
 */

ssize_t inbuf(info_t *info, char **buf, size_t *len)
{
	ssize_t g = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_int_handler);

#if USE_GETLINE
		g = getline(buf, &len_p, stdin);
#else
		g = getline(info, buf, &len_p);
#endif
		if (g > 0)
		{
			if ((*buf)[g - 1] == '\n')
			{
				(*buf)[g - 1] = '\0';
				g--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			bhist_list(info, *buf, info->histcount++);
			{
				*len = g;
				info->cmd_buf = buf;
			}
		}
	}
	return (g);
}

/**
 * getinput - gets a line but excluding new line
 * @info: struct parameter with possible arg's
 *
 * Return: bytes read
 */

ssize_t getinput(info_t *info)
{
	static char *buf;
	static size_t e, f, len;
	ssize_t g = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	g = inputbuf(info, &buf, &len);
	if (g == -1)
		return (-1);
	if (len)
	{
		f = e;
		p = buf + e;

		chk_chain(info, buf, &j, e, len);
		while (f < len)
		{
			if (pt_chain(info, buf, &f))
				break;
			f++;
		}
		e = f + 1;
		if (e >= len)
		{
			e = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (str_len(p));
	}
	*buf_p = buf;
	return (g);
}

/**
 * r_buf - read buffer
 * @info: struct parameter with possible arg's
 * @buf: buffer to read
 * @i: size to read
 *
 * Return: g
 */

ssize_t r_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t g = 0;

	if (*i)
		return (0);
	g = read(info->readfd, buf, READ_BUF_SIZE);
	if (g >= 0)
		*i = g;
	return (g);
}

/**
 * _gline -  gets the next lline of input
 * @info: struct parameter with possible arg's
 * @ptr: address of ptr, prealloc or NULL
 * @length: size of pre-alloc otr buf
 *
 * Return: s
 */

int _gline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t e, len;
	size_t f;
	ssize_t g = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (e == len)
		e = len = 0;
	g = r_buf(info, buf, &len);
	if (g == -1 || (g == 0 && len == 0))
		return (-1);
	c = _fcharstr(buf + e, '\n');
	f = c ? 1 + (unsigned int)(c - buf) : len;
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		cat_nstr(new_p, buf + e, f - e);
	else
		cpy_nstr(new_p, buf + e, f - e + 1);
	s += f - e;
	e = f;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sig_int_handler - copies the block using control & c
 * @sig_num: the signal number
 *
 * Return: void
 */

void sig_int_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$");
	_putchar(BUF_FLUSH);
}
