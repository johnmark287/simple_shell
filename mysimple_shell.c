#include "shell.h"

/* global variable for ^C handling */
unsigned int sig_flag;

/**
 * sigHandler - handles ^C signal interupt
 * @uuv: unused variable (required for signal function prototype)
 *
 * Return: void
 */
static void sigHandler(int myuuv)
{
	(void) myuuv;
	if (sig_flag == 0)
		_Puts("\n$ ");
	else
		_Puts("\n");
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, i;
	var_t myvars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	myvars.argv = argv;
	myvars.env = makeEnv(environment);
	signal(SIGINT, sigHandler);
	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		_Puts("$ ");
	sig_flag = 0;
	while (getline(&(myvars.buffer), &len_buffer, stdin) != -1)
	{
		sig_flag = 1;
		myvars.count++;
		myvars.commands = mytokenize(myvars.buffer, ";");
		for (i = 0; myvars.commands && myvars.commands[i] != NULL; i++)
		{
			myvars.av = mytokenize(myvars.commands[i], "\n \t\r");
			if (myvars.av && myvars.av[0])
				if (checkForBuiltins(&myvars) == NULL)
					checkForPath(&myvars);
		free(myvars.av);
		}
		free(myvars.buffer);
		free(myvars.commands);
		sig_flag = 0;
		if (is_pipe == 0)
			_Puts("$ ");
		myvars.buffer = NULL;
	}
	if (is_pipe == 0)
		_Puts("\n");
	freeEnv(myvars.env);
	free(myvars.buffer);
	exit(myvars.status);
}
