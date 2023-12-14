#include "shellhead.h"

/**
 * pt_cmd - determines execuatable cmd file
 * @info: struct parameter with possible arg's
 * @path: file path
 *
 * Return: 1 true, 0 otherwise
 */

int pt_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupchars - func to duplicate charecters
 * @strpath: string path
 * @start: index start point
 * @end: endex stopping point
 *
 * Return: pointer to new buf
 */

char *dupchars(char *strpath, int start, int end)
{
	static char buf[1024];
	int e = 0, f = 0;

	for (f = 0, e = start; e < end; e++)
		if (strpath[e] != ':')
			buf[f++] = strpath[e];
	buf[f] = 0;
	return (buf);
}

/**
 * f_path - dinds path str in cmd
 * @info: struct with possible arg's
 * @strpath: string path
 * @cmd: command to find
 *
 * Return: full name if found or NULL if not
 */

char *f_path(info_t *info, char *strpath, char *cmd)
{
	int e = 0, curr_pos = 0;
	char *path;

	if (!strpath)
		return (NULL);
	if ((str_len(cmd) > 2) && starts_with(cmd, "/"))
	{
		if (pt_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strpath[e] || strpath[e] == ':')
		{
			path = dupchars(strpath, curr_pos, e);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				strcat(path, "/");
				_strcat(path, cmd);
			}
			if (pt_cmd(info, path))
				return (path);
			if (!strpath[e])
				break;
			curr_pos = e;
		}
		e++;
	}
	return (NULL);
}
