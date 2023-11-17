#include "shell.h"

/**
 * mytokenize - mytokenizes the  buffer using a
 * delimiter passed to the function.
 * @mydelimiter: delimiter to mytokenize along
 * @mybuffer: the buffer to mytokenize
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **mytokenize(char *mybuffer, char *mydelimiter)
{
	size_t i = 0, mycounts = 10;
	char **mytokens = NULL;

	if (mybuffer == NULL)
		return (NULL);
	mytokens = malloc(sizeof(char *) * mycounts);
	if (mytokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((mytokens[i] = newStrtok(mybuffer, mydelimiter)))
	{
		i++;
		if (i == mycounts)
		{
			mytokens = _Realloc(mytokens, &mycounts);
			if (mytokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		mybuffer = NULL;
	}
	return (mytokens);
}
