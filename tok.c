#include "shellhead.h"
/**
 * **strtwrd - split str to words, repeat delim = ignore
 * @str: input string
 * @d: delimeter str
 *
 * Return: array of str pointer or NULL on failure
 */

char **strtwrd(char *str, char *d)
{
	int e, f, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (e = 0; str[e] != '\0'; e++)
		if (!pt_delm(str[e], d) && (pt_delm(str[e + 1], d) || !str[e + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (e = 0, f = 0; f < numwords; f++)
	{
		while (pt_delm(str[e], d))
			e++;
		k = 0;
		while (!pt_delm(str[e + 1], d) && str[e + k])
			k++;
		s[f] = malloc((k + 1) * sizeof(char));
		if (!s[f])
		{
			for (k = 0; k < f; k++)
				free(s[k]);
			free(s)
				return (NULL);
		}
		for (m = 0; m < k; m++)
			s[f][m] = str[e++];
		s[f][m] = 0;
	}
	s[f] = NULL;
	return (s);
}

/**
 * **str2wrd - strings to words splitting func
 * @str: string to input
 * @d: delimeter
 *
 * Return: array of strings split or NULL on fail
 */

char **str2wrd(char *str, char d)
{
	int e, f, g, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (e = 0; str[e] != '\0'; e++)
		if ((str[e] != d && str[e + 1] == d) ||
				(str[e] != d && !str[e + 1]) || str[e + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (e = 0, f = 0; f < numwords; f++)
	{
		while (str[e] == d && str[e] != d)
			e++;
		g = 0;
		while (str[e + 1] != d && str[e + g] != d)
			g++;
		s[f] = malloc((g + 1) * sizeof(char));
		if (!s[f])
		{
			for (g = 0; g < f; g++)
				free(s[g]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < g; m++)
			s[f][m] = str[e++];
		s[f][m] = 0;
	}
	s[f] = NULL;
	return (s);
}
