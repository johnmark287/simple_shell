#include "shell.h"

/**
 * makeEnv - make the shell environment from the environment passed to main
 * @myenv: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **makeEnv(char **myenv)
{
	char **mynewenv = NULL;
	size_t i;

	for (i = 0; myenv[i] != NULL; i++)
		;
	mynewenv = malloc(sizeof(char *) * (i + 1));
	if (mynewenv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; myenv[i] != NULL; i++)
		mynewenv[i] = _Strdup(myenv[i]);
	mynewenv[i] = NULL;
	return (mynewenv);
}

/**
 * freeEnv - free the shell's environment
 * @myenv: shell's environment
 *
 * Return: void
 */
void freeEnv(char **myenv)
{
	unsigned int i;

	for (i = 0; myenv[i] != NULL; i++)
		free(myenv[i]);
	free(myenv);
}
