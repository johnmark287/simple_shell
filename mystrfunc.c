#include "shell.h"

/**
 * _Puts - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t _Puts(char *mystr)
{
	ssize_t mynum, mylen;

	mynum = _Strlen(mystr);
	mylen = write(STDOUT_FILENO, mystr, mynum);
	if (mylen != mynum)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (mylen);
}

/**
 * _Strdup - returns pointer to new mem alloc space which contains copy
 * @strtodup: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *_Strdup(char *mystrtodup)
{
	char *mycopy;

		int len, i;

	if (mystrtodup == 0)
		return (NULL);

	for (len = 0; mystrtodup[len]; len++)
		;
	mycopy = malloc((len + 1) * sizeof(char));

	for (i = 0; i <= len; i++)
		mycopy[i] = mystrtodup[i];

	return (mycopy);
}

/**
 * _Strcmpr - compares two strings
 * @strcmp1: first string, of two, to be compared in length
 * @strcmp2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int _Strcmpr(char *mystrcmp1, char *mystrcmp2)
{
	int i;

	i = 0;
	while (mystrcmp1[i] == mystrcmp2[i])
	{
		if (mystrcmp1[i] == '\0')
			return (0);
		i++;
	}
	return (mystrcmp1[i] - mystrcmp2[i]);
}

/**
 * _Strcat - concatenates two strings
 * @mystrc1: first string
 * @strc2: second string
 * Return: pointer
 */
char *_Strcat(char *mystrc1, char *mystrc2)
{
	char *mynewstring;
	unsigned int mylen1, mylen2, newlen, i, j;

	mylen1 = 0;
	mylen2 = 0;
	if (mystrc1 == NULL)
		mylen1 = 0;
	else
	{
		for (mylen1 = 0; mystrc1[mylen1]; mylen1++)
			;
	}
	if (mystrc2 == NULL)
		mylen2 = 0;
	else
	{
		for (mylen2 = 0; mystrc2[mylen2]; mylen2++)
			;
	}
	newlen = mylen1 + mylen2 + 2;
	mynewstring = malloc(newlen * sizeof(char));
	if (mynewstring == NULL)
		return (NULL);
	for (i = 0; i < mylen1; i++)
		mynewstring[i] = mystrc1[i];
	mynewstring[i] = '/';
	for (j = 0; j < mylen2; j++)
		mynewstring[i + 1 + j] = mystrc2[j];
	mynewstring[mylen1 + mylen2 + 1] = '\0';
	return (mynewstring);
}

/**
 * _Strlen - returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int _Strlen(char *mystr)
{
	unsigned int mylen;

	mylen = 0;

	for (mylen = 0; mystr[mylen]; mylen++)
		;
	return (mylen);
}
