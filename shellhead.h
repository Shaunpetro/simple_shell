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
#include <fcntl.h>
#include <errno.h>

/* number conversion */
#define CONVERT_UNSIGNED	1
#define CONVERT_LOWERCASE	2

/**
 * struct builtin - contains builtin str
 * @type: builtin cmd flag
 * @func: builtin flag
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* -- RW buffers --*/
#define READ_BUF_SIZE	1024
#define WRITE_BUF_SIZE	1024
#define BUF_FLUSH	-1

/**
 * struct passinfo - with pseudo arg's passing into functions
 * @arg: str gnerated for getline arg's
 * @argv: str arg's array
 * @argc: argument count
 * @line_count: error count
 * @linecount_flag: if on count line
 * @env: LL local copy
 * @environ: custom modified copy of environ
 * @env_changed: on if env was changed
 * @history: hist node
 * @histcount: history ;ine number count
 * @path: string path with command
 * @err_num: error code
 * @fname: program filename
 * @alias: alias node
 * @cmd_buf: address of ptr to cmd buf
 * @cmd_buf_type: command type
 * @readfd: the fd for reading lines
 * @status: return stastus of last x command
 */

typedef struct passinfo
{
	char *arg;
	int argc;
	char **argv;
	int err_num;
	char *fname;
	list_t *env;
	char **environ;
	int env_changed;
	char *path;
	unsigned int line_count;
	int linecount_flag;
	list_t *alias;
	list_t *history;
	int histcount;
	int status;
	char **cmd_buf;
	int readfd;
	int cmd_buf_type;
} info_t;
extern char **environ;

#define HIST_FILE	".sSh_hist"
#define HIST_MAX	4096

/*-- gline() */
#define USE_GETLINE	0
#define USE_STRTOK	0

/* -- chain CMD - */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

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

/* -- env.c -- */
int _menv(info_t *);
char *_genv(info_t *, const char *);
int _musenv(info_t *);
int _msenv(info_t *);
int pop_env_list(info_t *);

/* -- genv -- */
char **genv(info_t *);
int _usenv(info_t *, char *);
int _senv(info_t *, char *, char *);

/* -- prs.c -- */
int pt_cmd(info_t *, char *);
char *dupchars(char *, int start, int end);
char *f_path(info_t *, char *, char *);

/* --- hist.c -- */
char *ghist_file(info_t *);
int whist(info_t *);
int rhist(info_t *);
int renum_hist(info_t *);
int bhist_list(info_t *, char *, int linrcount);

/* -- gline.c -- */
ssize_t inbuf(info_t *, char **, size_t);
ssize_t getinput(info_t *);
int _gline(info_t *, char **, size_t);
void sig_int_handler(int);

/* -- mm.c -- */
int bfree(void **);

/* -- allre.c -- */
char *mem_set(char *, char, unsigned int);
void ssfree(char *);
void *_re_alloc(void *, unsigned int, unsigned int);

/* -- ginfo.c -- */
void cl_info(info_t *);
void set_info(info_t *, char **);
void ffinfo(info_t *, int);

/* -- str_lc.c -- */
int st4r_len(char *);
int strcomp(char *, char *);
char *starts_with(const char *, const char *);
char *_catstr(char *, char *);

/* -- listt.c -- */
list_t *add_node(list_t **, const char *, int);
list_t *add_end_node(list_t **, const char *, int);
size_t print_liststr(const list_t *);
int delnode_at_index(list_t **, unsigned int);
void freelist(list_t **);

/* -- shlp.c --*/
int hsh(info_t *, char **);
int find_buin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* -- sizet.c -- */
size_t list_len(const list_t *);
char **lt_strings(list_t *);
list_t *node_swith(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);

/* -- str_man.c -- */
char *cpy_str(char *, char *);
char *_dupstr(const char *);
void _puts(char *);
int _putchar(char);

/* -- quit.c -- */
char *cpy_nstr(char *, char *, int);
char *cat_nstr(char *, char *, int);
char *_fcharstr(char *, char);

/* -- adhis.c --*/
int _mexit(info_t *);
int _mycd(info_t *);
int _mhelp(info_t *);

/* -- direx.c --*/
int _mhist(info_t *);
int alias_us(info_t *, char *);
int salias(info_t *, char *);
int print_alias(list_t *);

/* -- erradia.c -- */
int _erradia(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* -- putfunc.c -- */
int _putchar(char);
int _putfd(char, int);
int _putsfd(char *, int);

/* -- mainshell -- */
int main(int, char **);

#endif
