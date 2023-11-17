#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: commands to execute
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} var_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(var_t *);
} builtins_t;

char **makeEnv(char **myenv);
void freeEnv(char **myenv);

ssize_t _Puts(char *mystr);
char *_Strdup(char *mystrtodup);
int _Strcmpr(char *mystrcmp1, char *mystrcmp2);
char *_Strcat(char *mystrc1, char *mystrc2);
unsigned int _Strlen(char *mystr);

char **mytokenize(char *mybuffer, char *mydelimiter);
char **_Realloc(char **myptr, size_t *mysize);
char *newStrtok(char *mystr, const char *mydelim);

void (*checkForBuiltins(var_t *myvars))(var_t *myvars);
void newExit(var_t *myvars);
void _envs(var_t *myvars);
void newSetenv(var_t *myvars);
void newUnsetenv(var_t *myvars);

void addKey(var_t *myvars);
char **findKey(char **myenv, char *mykey);
char *addValue(char *mykey, char *myvalue);
int _atois(char *mystr)
;

void checkForPath(var_t *myvars);
int pathExecute(char *mycommand, var_t *myvars);
char *findPath(char **myenv);
int executeCwd(var_t *myvars);
int checkForDir(char *mystr);

void printError(var_t *myvars, char *mymsg);
void _Puts2(char *mystr);
char *_Uitoa(unsigned int mycount);

unsigned int checkMatch(char c, const char *mystr);

#endif /* _SHELL_H_ */
