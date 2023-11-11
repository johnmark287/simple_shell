#include "shell.h"

/**
 * check_builtins - checks if the command is a builtin command or not
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*check_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; check[i].f; i++)
	{
		if (_string_cmp(vars->av[0], check[i].name) == 0)
			break;
	}
	if (check[i].f)
		check[i].f(vars);
	return (check[i].f);
}

/**
 * new_exit - exit the program
 * @vars: these are variables
 * Return: nothing
 */
void new_exit(vars_t *vars)
{
	int status;

	if (_string_cmp(vars->av[0], "exit") == 0 && vars->av[1])
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			puts_two(vars->av[1]);
			puts_two("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}

/**
 * _env - prints the current environment
 * @vars: this is struct of variables
 * Return: nothing.
 */
void _env(vars_t *vars)
{
	unsigned int i;

	for (i = 0; vars->env[i]; i++)
	{
		_puts(vars->env[i]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * new_setenv - create a new environment variable,
 * or edit an already existing variable
 * @vars: pointer to struct of variables
 *
 * Return: nothing.
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;

	if (!vars->av[1] || !vars->av[2])
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (!key)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (!var)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * new_unsetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;

	unsigned int i, j;

	if (!vars->av[1])
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (!key)
	{
		print_error(vars, ": No variable to unset");
		return;
	}
	for (i = 0; vars->env[i]; i++)
		;
	newenv = malloc(sizeof(char *) * i);
	if (!newenv)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (i = 0; vars->env[i] != *key; i++)
		newenv[i] = vars->env[i];
	for (j = i + 1; vars->env[j]; j++, i++)
		newenv[i] = vars->env[j];
	newenv[i] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}
