#include "shell.h"

/**
 * addKey - create a new environment variable
 * @myvars: pointer to struct of variables
 *
 * Return: void
 */
void addKey(var_t *myvars)
{
	unsigned int i;
	char **newEnv;

	for (i = 0; myvars->env[i] != NULL; i++)
		;
	newEnv = malloc(sizeof(char *) * (i + 2));
	if (newEnv == NULL)
	{
		printError(myvars, NULL);
		myvars->status = 127;
		newExit(myvars);
	}
	for (i = 0; myvars->env[i] != NULL; i++)
		newEnv[i] = myvars->env[i];
	newEnv[i] = addValue(myvars->av[1], myvars->av[2]);
	if (newEnv[i] == NULL)
	{
		printError(myvars, NULL);
		free(myvars->buffer);
		free(myvars->commands);
		free(myvars->av);
		freeEnv(myvars->env);
		free(newEnv);
		exit(127);
	}
	newEnv[i + 1] = NULL;
	free(myvars->env);
	myvars->env = newEnv;
}

/**
 * findKey - finds an environment variable
 * @myenv: array of environment variables
 * @mykey: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **findKey(char **myenv, char *mykey)
{
	unsigned int i, j, len;

	len = _Strlen(mykey);
	for (i = 0; myenv[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
			if (mykey[j] != myenv[i][j])
				break;
		if (j == len && myenv[i][j] == '=')
			return (&myenv[i]);
	}
	return (NULL);
}

/**
 * addValue - create a new environment variable string
 * @mykey: variable name
 * @myvalue: variable value
 *
 * Return: pointer to the new string;
 */
char *addValue(char *mykey, char *myvalue)
{
	unsigned int len1, len2, i, j;
	char *mynew;

	len1 = _Strlen(mykey);
	len2 = _Strlen(myvalue);
	mynew = malloc(sizeof(char) * (len1 + len2 + 2));
	if (mynew == NULL)
		return (NULL);
	for (i = 0; mykey[i] != '\0'; i++)
		mynew[i] = mykey[i];
	mynew[i] = '=';
	for (j = 0; myvalue[j] != '\0'; j++)
		mynew[i + 1 + j] = myvalue[j];
	mynew[i + 1 + j] = '\0';
	return (mynew);
}

/**
 * _atois - converts a string into an integer
 * @mystr: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atois(char *mystr)

{
	unsigned int i, mydigits;
	int num = 0, numTest;

	numTest = INT_MAX;
	for (mydigits = 0; numTest != 0; mydigits++)
		numTest /= 10;
	for (i = 0; mystr[i] != '\0' && i < mydigits; i++)
	{
		num *= 10;
		if (mystr[i] < '0' || mystr[i] > '9')
			return (-1);
		if ((i == mydigits - 1) && (mystr[i] - '0' > INT_MAX % 10))
			return (-1);
		num += mystr[i] - '0';
		if ((i == mydigits - 2) && (mystr[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (i > mydigits)
		return (-1);
	return (num);
}
