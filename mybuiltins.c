#include "shell.h"

/**
 * checkForBuiltins - checks if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*checkForBuiltins(var_t *myvars))(var_t *myvars)
{
	unsigned int i;
	builtins_t checker[] = {
		{"exit", newExit},
		{"env", _envs},
		{"setenv", newSetenv},
		{"unsetenv", newUnsetenv},
		{NULL, NULL}
	};

	for (i = 0; checker[i].f != NULL; i++)
	{
		if (_Strcmpr(myvars->av[0], checker[i].name) == 0)
			break;
	}
	if (checker[i].f != NULL)
		checker[i].f(myvars);
	return (checker[i].f);
}

/**
 * newExit - exit program
 * @vars: variables
 * Return: void
 */
void newExit(var_t *myvars)
{
	int status;

	if (_Strcmpr(myvars->av[0], "exit") == 0 && myvars->av[1] != NULL)
	{
		status = _atois(myvars->av[1]);
		if (status == -1)
		{
			myvars->status = 2;
			printError(myvars, ": Illegal number: ");
			_Puts2(myvars->av[1]);
			_Puts2("\n");
			free(myvars->commands);
			myvars->commands = NULL;
			return;
		}
		myvars->status = status;
	}
	free(myvars->buffer);
	free(myvars->av);
	free(myvars->commands);
	freeEnv(myvars->env);
	exit(myvars->status);
}

/**
 * _envs - prints the current environment
 * @vars: struct of variables
 * Return: void.
 */
void _envs(var_t *myvars)
{
	unsigned int i;

	for (i = 0; myvars->env[i]; i++)
	{
		_Puts(myvars->env[i]);
		_Puts("\n");
	}
	myvars->status = 0;
}

/**
 * newSetenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void newSetenv(var_t *myvars)
{
	char **mykey;
	char *myvar;

	if (myvars->av[1] == NULL || myvars->av[2] == NULL)
	{
		printError(myvars, ": Incorrect number of arguments\n");
		myvars->status = 2;
		return;
	}
	mykey = findKey(myvars->env, myvars->av[1]);
	if (mykey == NULL)
		addKey(myvars);
	else
	{
		myvar = addValue(myvars->av[1], myvars->av[2]);
		if (myvar == NULL)
		{
			printError(myvars, NULL);
			free(myvars->buffer);
			free(myvars->commands);
			free(myvars->av);
			freeEnv(myvars->env);
			exit(127);
		}
		free(*mykey);
		*mykey = myvar;
	}
	myvars->status = 0;
}

/**
 * newUnsetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void newUnsetenv(var_t *myvars)
{
	char **mykey, **newenv;

	unsigned int i, j;

	if (myvars->av[1] == NULL)
	{
		printError(myvars, ": Incorrect number of arguments\n");
		myvars->status = 2;
		return;
	}
	mykey = findKey(myvars->env, myvars->av[1]);
	if (mykey == NULL)
	{
		printError(myvars, ": No variable to unset");
		return;
	}
	for (i = 0; myvars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * i);
	if (newenv == NULL)
	{
		printError(myvars, NULL);
		myvars->status = 127;
		newExit(myvars);
	}
	for (i = 0; myvars->env[i] != *mykey; i++)
		newenv[i] = myvars->env[i];
	for (j = i + 1; myvars->env[j] != NULL; j++, i++)
		newenv[i] = myvars->env[j];
	newenv[i] = NULL;
	free(*mykey);
	free(myvars->env);
	myvars->env = newenv;
	myvars->status = 0;
}
