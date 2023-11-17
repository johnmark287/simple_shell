#include "shell.h"

/**
 * pathExecute - executes a command in the path
 * @command: full path to the command
 * @vars: pointer to struct of variables
 *
 * Return: 0 on succcess, 1 on failure
 */
int pathExecute(char *mycommand, var_t *myvars)
{
	pid_t childPid;

	if (access(mycommand, X_OK) == 0)
	{
		childPid = fork();
		if (childPid == -1)
			printError(myvars, NULL);
		if (childPid == 0)
		{
			if (execve(mycommand, myvars->av, myvars->env) == -1)
				printError(myvars, NULL);
		}
		else
		{
			wait(&myvars->status);
			if (WIFEXITED(myvars->status))
				myvars->status = WEXITSTATUS(myvars->status);
			else if (WIFSIGNALED(myvars->status) && WTERMSIG(myvars->status) == SIGINT)
				myvars->status = 130;
			return (0);
		}
		myvars->status = 127;
		return (1);
	}
	else
	{
		printError(myvars, ": Permission denied\n");
		myvars->status = 126;
	}
	return (0);
}

/**
 * findPath - finds the PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *findPath(char **myenv)
{
	char *mypath = "PATH=";
	unsigned int i, j;

	for (i = 0; myenv[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (mypath[j] != myenv[i][j])
				break;
		if (j == 5)
			break;
	}
	return (myenv[i]);

}

/**
 * checkForPath - checks if the command is in the PATH
 * @vars: variables
 *
 * Return: void
 */
void checkForPath(var_t *myvars)
{
	char *mypath, *mypath_dup = NULL, *mycheck = NULL;
	unsigned int i = 0, r = 0;
	char **mypath_tokens;
	struct stat mybuf;

	if (checkForDir(myvars->av[0]))
		r = executeCwd(myvars);
	else
	{
		mypath = findPath(myvars->env);
		if (mypath != NULL)
		{
			mypath_dup = _Strdup(mypath + 5);
			mypath_tokens = mytokenize(mypath_dup, ":");
			for (i = 0; mypath_tokens && mypath_tokens[i]; i++, free(mycheck))
			{
				mycheck = _Strcat(mypath_tokens[i], myvars->av[0]);
				if (stat(mycheck, &mybuf) == 0)
				{
					r = pathExecute(mycheck, myvars);
					free(mycheck);
					break;
				}
			}
			free(mypath_dup);
			if (mypath_tokens == NULL)
			{
				myvars->status = 127;
				newExit(myvars);
			}
		}
		if (mypath == NULL || mypath_tokens[i] == NULL)
		{
			printError(myvars, ": not found\n");
			myvars->status = 127;
		}
		free(mypath_tokens);
	}
	if (r == 1)
		newExit(myvars);
}

/**
 * executeCwd - executes the command in the current working directory
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int executeCwd(var_t *myvars)
{
	pid_t childPid;
	struct stat mybuf;

	if (stat(myvars->av[0], &mybuf) == 0)
	{
		if (access(myvars->av[0], X_OK) == 0)
		{
			childPid = fork();
			if (childPid == -1)
				printError(myvars, NULL);
			if (childPid == 0)
			{
				if (execve(myvars->av[0], myvars->av, myvars->env) == -1)
					printError(myvars, NULL);
			}
			else
			{
				wait(&myvars->status);
				if (WIFEXITED(myvars->status))
					myvars->status = WEXITSTATUS(myvars->status);
				else if (WIFSIGNALED(myvars->status) && WTERMSIG(myvars->status) == SIGINT)
					myvars->status = 130;
				return (0);
			}
			myvars->status = 127;
			return (1);
		}
		else
		{
			printError(myvars, ": Permission denied\n");
			myvars->status = 126;
		}
			return (0);
	}
	printError(myvars, ": not found\n");
	myvars->status = 127;
	return (0);
}

/**
 * checkForDir - checks if the command is a part of a path
 * @str: command
 *
 * Return: 1 on success, 0 on failure
 */
int checkForDir(char *mystr)
{
	unsigned int i;

	for (i = 0; mystr[i]; i++)
	{
		if (mystr[i] == '/')
			return (1);
	}
	return (0);
}
