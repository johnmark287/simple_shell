#include "shell.h"

/**
 * _puts - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t _puts(char *str)
{
	ssize_t num, len;

	num = _string_len(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}

/**
 * _string_dup - returns pointer to new mem alloc space which contains copy
 * @strtodup: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *_string_dup(char *strtodup)
{
	char *copy;

		int len, i;

	if (strtodup == 0)
		return (NULL);

	for (len = 0; strtodup[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (i = 0; i <= len; i++)
		copy[i] = strtodup[i];

	return (copy);
}

/**
 * _string_cmp - compares two strings
 * @strcmp_one: first string, of two, to be compared in length
 * @strcmp_two: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int _string_cmp(char *strcmp_one, char *strcmp_two)
{
	int i;

	i = 0;
	while (strcmp_one[i] == strcmp_two[i])
	{
		if (strcmp_one[i] == '\0')
			return (0);
		i++;
	}
	return (strcmp_one[i] - strcmp_two[i]);
}

/**
 * _string_cat - concatenates two strings
 * @strc_one: first string
 * @strc_two: second string
 * Return: pointer
 */
char *_string_cat(char *strc_one, char *strc_two)
{
	char *newstring;
	unsigned int len1, len2, newlen, i, j;

	len1 = 0;
	len2 = 0;
	if (strc_one == NULL)
		len1 = 0;
	else
	{
		for (len1 = 0; strc_one[len1]; len1++)
			;
	}
	if (strc_two == NULL)
		len2 = 0;
	else
	{
		for (len2 = 0; strc_two[len2]; len2++)
			;
	}
	newlen = len1 + len2 + 2;
	newstring = malloc(newlen * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	for (i = 0; i < len1; i++)
		newstring[i] = strc_one[i];
	newstring[i] = '/';
	for (j = 0; j < len2; j++)
		newstring[i + 1 + j] = strc_two[j];
	newstring[len1 + len2 + 1] = '\0';
	return (newstring);
}

/**
 * _string_len - returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int _string_len(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++)
		;
	return (len);
}
