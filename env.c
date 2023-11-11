#include "shell.h"

/**
 * make_environment - make the shell environment
 * from the environment passed to main
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **make_environment(char **env)
{
	char **new_env = NULL;
	size_t i;

	for (i = 0; env[i]; i++)
		;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (new_env == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; env[i]; i++)
		new_env[i] = _string_dup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}

/**
 * free_env - free the shell's environment.
 * @env: shell's environment.
 *
 * Return: nothing.
 */
void free_env(char **env)
{
	unsigned int i;

	for (i = 0; env[i]; i++)
		free(env[i]);
	free(env);
}
