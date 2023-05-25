#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"
/* #define PATH_MAX 1024 */

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

sep_list *add_sep_node_at_end(sep_list **head, char sep);
void unallocate_sep_list(sep_list **head);
line_list *addLineAtEndOfNode(line_list **head, char *line);
void unallocate_line_list(line_list **head);
r_var *addNodeToRvar(r_var **head, int lvar, char *var, int lval);
void unallocate_rvar_list(r_var **head);
char *_concatstr(char *dest, const char *src);
char *_copy(char *dest, char *src);
int _compare(char *s1, char *s2);
char *_strchr(char *s, char c);
int _indexOf(char *s, char *accept);
void cpy_info(void *newptr, const void *ptr, unsigned int size);
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocatedp(char **ptr, unsigned int old_size, unsigned int new_size);
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
void _strrev(char *s);
int get_rep_char_num(char *input, int i);
int _syntax_err(char *input, int i, char last);
int index_of_first_char(char *input, int *i);
void prt_syntax_err(data_shell *datash, char *input, int i, int bool);
int check_syntax_err(data_shell *datash, char *input);
char *deletecomment_(char *in);
void shloop_(data_shell *datash);
char *readline_(int *i_eof);
char *swapchar_(char *input, int bool);
void addnodes_(sep_list **head_s, line_list **head_l, char *input);
void go_to_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int _split(data_shell *datash, char *input);
char **_splitline(char *input);
void checkenv_(r_var **h, char *in, data_shell *data);
int checkvars_(r_var **h, char *in, char *st, data_shell *data);
char *replaceinput_(r_var **head, char *input, char *new_input, int nlen);
char *repvar_(char *input, data_shell *datash);
void bringline_(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t getline_(char **lineptr, size_t *n, FILE *stream);
int execute_line(data_shell *datash);
int is_crr_dir(char *path, int *i);
char *_locate_cmd(char *cmd, char **_environ);
int _isexec(data_shell *datash);
int cmd_error_check(char *dir, data_shell *datash);
int _execute(data_shell *datash);
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);
char *cpy_env_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);
void cd_cmd_dot(data_shell *datash);
void cd_cmd_to(data_shell *datash);
void cd_cmd_previous(data_shell *datash);
void cd_cmd_home(data_shell *datash);
int cd_cmd(data_shell *datash);
int (*_getbuiltin(char *cmd))(data_shell *datash);
int _exit_sh(data_shell *datash);
int get_num_len(int n);
char *int_to_string(int n);
int parseint(char *s);
char *strcat_cd_error(data_shell *, char *, char *, char *);
char *get_cd_error(data_shell *datash);
char *error_notFound(data_shell *datash);
char *exit_shell_error(data_shell *datash);
char *error_get_alias(char **args);
char *env_error(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *path_126_err(data_shell *datash);
int geterror_(data_shell *datash, int eval);
void handle_signal(int sig);
void env_help(void);
void setenv_help(void);
void unsetenv_help(void);
void general_help(void);
void custom_exit_help(void);
void _help(void);
void alias_help(void);
void cd_help(void);
int gethelp_(data_shell *datash);

#endif
