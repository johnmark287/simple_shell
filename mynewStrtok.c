#include "shell.h"
/**
 * checkMatch - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */
unsigned int checkMatch(char c, const char *mystr)
{
	unsigned int i;

	for (i = 0; mystr[i] != '\0'; i++)
	{
		if (c == mystr[i])
			return (1);
	}
	return (0);
}

/**
 * newStrtok - custom strtok
 * @str: string to mytokenize
 * @delim: delimiter to mytokenize against
 *
 * Return: pointer to the next token or NULL
 */
char *newStrtok(char *mystr, const char *mydelim)
{
	static char *tokenStart;
	static char *nextToken;
	unsigned int i;

	if (mystr != NULL)
		nextToken = mystr;
	tokenStart = nextToken;
	if (tokenStart == NULL)
		return (NULL);
	for (i = 0; nextToken[i] != '\0'; i++)
	{
		if (checkMatch(nextToken[i], mydelim) == 0)
			break;
	}
	if (nextToken[i] == '\0' || nextToken[i] == '#')
	{
		nextToken = NULL;
		return (NULL);
	}
	tokenStart = nextToken + i;
	nextToken = tokenStart;
	for (i = 0; nextToken[i] != '\0'; i++)
	{
		if (checkMatch(nextToken[i], mydelim) == 1)
			break;
	}
	if (nextToken[i] == '\0')
		nextToken = NULL;
	else
	{
		nextToken[i] = '\0';
		nextToken = nextToken + i + 1;
		if (*nextToken == '\0')
			nextToken = NULL;
	}
	return (tokenStart);
}
