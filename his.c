#include "shellhead.h"

/**
 * ghist_file - get history
 * @info: struct parameter with possible arg's
 *
 * Return: allocated str with history file
 */

char *ghist_file(info_t *info)
{
	char *buf, *dir;

	dir = _genv(info, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));

	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}


/**
 * whist - create or append hist file to existing file
 * @info: struct parameter weith possible arg's
 *
 * Return: 1 sucess, otherwise -1
 */

int whist(info_t *info)
{
	ssize_t fd;
	char *filename = ghist_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT |  O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
	{
		return (-1);
	}
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rhist - read history from file
 * @info: parameter struct with possible arg's
 *
 * Return: histcount on success, if not 0
 */

int rhist(info_t *info)
{
	int e, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = ghist_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
	{
		fsize = st.st_size;
	}
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (e = 0; e < fsize; e++)
		if (buf[e] == '\n')
		{
			buf[e] = 0;
			bhist_list(info, buf + last, linecount++);
			last = e + 1;
		}
	if (last != e)
		bhist_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delnode_at_index(&(info->history), 0);
	renum_hist(info);
	return (info->histcount);
}

/**
 * bhist_list - entry addiotion to histor LL
 * @info: struct parameter with possible arg's
 * @buf: buffer
 * @linecount: the history linecount (histcount)
 *
 * Return: 0 alwasy
 */

int bhist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_end_node(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_hist - renumbers history of LL after changes
 * @info: struct parameter with possible arg's
 *
 * Return: new hist count
 */

int renum_hist(info_t *info)
{
	list_t *node = info->history;
	int e = 0;

	while (node)
	{
		node->num = e++;
		node = node->next;
	}
	return (info->histcount = e);
}
