#include "shell.h"

/**
 * tokenize - tokenizes the  buffer using a
 * delimiter passed to the function.
 * @delimiter: delimiter to tokenize along
 * @buffer: the buffer to tokenize
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **tokenize(char *buffer, char *delimiter)
{
	size_t i = 0, counts = 10;
	char **tokens = NULL;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * counts);
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((tokens[i] = new_strtok(buffer, delimiter)))
	{
		i++;
		if (i == counts)
		{
			tokens = _realloc(tokens, &counts);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
