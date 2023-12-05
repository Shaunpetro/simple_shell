#ifndef _SHELL_H_
#define _SHELL_H_

/*----------------- sys libraries--------------------------------*/
/* -- kernel lib (base sys) -- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* number conversion */
#define CONVERT_UNSIGNED	1
#define CONVERT_LOWERCASE	2

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/*-------------------------file prototypes----------------------*/

/* -- VAR.C --*/
int pt_chain(info_t *, char *, size_t *);
void chk_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_replace(info_t *);
int var_replace(info_t *);
int replace_string(char **, char *);

/* -- _dia.c -- */
int intactive(info_t *info);
int pt_delm(char j, char *delm);
int _ptalpha(int j);
int _idia(char *s);

/* -- tok.c -- */
char **strtwrd(char *, char *);
char **str2wrd(char *, char);
#endif
