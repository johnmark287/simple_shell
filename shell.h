#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: number of commands entered
 * @argv: arguments when opening the shell
 * @status: exit status value
 * @commands: commands to execute
 */
typedef struct variables
{
	char *buffer;
	char **av;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of the builtin command
 * @f: function for each builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

char **make_environment(char **env);
void free_env(char **env);

char **tokenizer(char *buffer, char *delim);
char **_realloc(char **ptr, size_t *size);
char *string_token(char *str, const char *delim);

ssize_t _puts(char *str);
unsigned int _string_len(char *str);
char *_string_dup(char *strtodup);
char *_string_cat(char *strc_one, char *strc_two);
int _string_cmp(char *strcmp_one, char *strcmp_two);


void new_unsetenv(vars_t *vars);
void (*check_builtins(vars_t *vars))(vars_t *vars);
void _env(vars_t *vars);
void new_exit(vars_t *vars);
void new_setenv(vars_t *vars);

void look_for_path(vars_t *vars);
int execute_cwd(vars_t *vars);
int path_exec(char *command, vars_t *vars);
int check_for_dir(char *str);
char *find_path(char **env);

void add_key(vars_t *vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);


void print_error(vars_t *vars, char *message);
char *_uitoa(unsigned int count);
void puts_two(char *str);

#endif /* _SHELL_H_ */
