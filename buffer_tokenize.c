#include "shell.h"

/**
 * tokenizer - tokenizes a buffer using a delimiter
 * @buffer: buffer to tokenize
 * @delim: delimiter to tokenize the string provided
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **tokenizer(char *buffer, char *delim)
{
	char **tokens = NULL;
	size_t i = 0, count_m = 10;

	if (!buffer)
		return (NULL);
	tokens = malloc(sizeof(char *) * count_m);
	if (!tokens)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((tokens[i] = string_token(buffer, delim)))
	{
		i++;
		if (i == count_m)
		{
			tokens = _realloc(tokens, &count_m);
			if (!tokens)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
