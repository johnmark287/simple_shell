#include "shell.h"
/**
 * check_match - checks if a character matches any character in a string.
 * @c: the character to check.
 * @str: the pointer to a string to check.
 *
 * Return: 1 if there is a match, 0 if there isn't.
 */
unsigned int check_match(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (c == str[i])
		{
			return (1);
		}
	}
	return (0);
}

/**
 * string_token - works like strtok function.
 * @str: string to tokenizer.
 * @delim: delimiter to tokenize against the string provided.
 *
 * Return: pointer to the next token or NULL
 * if it reaches end of string
 */
char *string_token(char *str, const char *delim)
{
	static char *starting_token;
	static char *next_token;
	unsigned int i;

	if (str)
		next_token = str;
	starting_token = next_token;
	if (!starting_token)
		return (NULL);
	for (i = 0; next_token[i]; i++)
	{
		if (check_match(next_token[i], delim) == 0)
			break;
	}
	if (!next_token[i] || next_token[i] == '#')
	{
		next_token = NULL;
		return (NULL);
	}
	starting_token = next_token + i;
	next_token = starting_token;
	for (i = 0; next_token[i]; i++)
	{
		if (check_match(next_token[i], delim) == 1)
			break;
	}
	if (!next_token[i])
		next_token = NULL;
	else
	{
		next_token[i] = '\0';
		next_token = next_token + i + 1;
		if (*next_token == '\0')
			next_token = NULL;
	}
	return (starting_token);
}
