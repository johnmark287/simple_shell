#include "shell.h"

/* global variable for ^C handling */
unsigned int sig_flag;

/**
 * sig_handler - it handles the ^C signal interupt.
 * @uuv: unused variable - for signal function prototype
 *
 * Return: nothing.
 */
static void sig_handler(int uuv)
{
	(void) uuv;
	if (sig_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * main - Entry point of shell program (main function for the shell).
 * @argc: count of arguments passed to main
 * @argv: array of arguments(string of strings) passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int isPipe = 0, i;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = make_environment(environment);
	signal(SIGINT, sig_handler);
	if (!isatty(STDIN_FILENO))
		isPipe = 1;
	if (isPipe == 0)
		_puts("$ ");
	sig_flag = 0;
	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		sig_flag = 1;
		vars.count++;
		vars.commands = tokenizer(vars.buffer, ";");
		for (i = 0; vars.commands && vars.commands[i]; i++)
		{
			vars.av = tokenizer(vars.commands[i], "\n \t\r");
			if (vars.av && vars.av[0])
				if (check_builtins(&vars))
					look_for_path(&vars);
		free(vars.av);
		}
		free(vars.buffer);
		free(vars.commands);
		sig_flag = 0;
		if (isPipe == 0)
			_puts("$ ");
		vars.buffer = NULL;
	}
	if (isPipe == 0)
		_puts("\n");
	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
