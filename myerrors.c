#include "shell.h"

/**
 * printError - prints error messages to standard error
 * @myvars: pointer to struct of variables
 * @mymsg: message to print
 *
 * Return: void
 */
void printError(var_t *myvars, char *mymsg)
{
	char *count;

	_Puts2(myvars->argv[0]);
	_Puts2(": ");
	count = _Uitoa(myvars->count);
	_Puts2(count);
	free(count);
	_Puts2(": ");
	_Puts2(myvars->av[0]);
	if (mymsg)
	{
		_Puts2(mymsg);
	}
	else
		perror("");
}

/**
 * _Puts2 - prints a string to standard error
 * @mystr: string to print
 *
 * Return: void
 */
void _Puts2(char *mystr)
{
	ssize_t mynum, len;

	mynum = _Strlen(mystr);
	len = write(STDERR_FILENO, mystr, mynum);
	if (len != mynum)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _Uitoa - converts an unsigned int to a string
 * @mycount: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *_Uitoa(unsigned int mycount)
{
	char *numstr;
	unsigned int temp, mydigits;

	temp = mycount;
	for (mydigits = 0; temp != 0; mydigits++)
		temp /= 10;
	numstr = malloc(sizeof(char) * (mydigits + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[mydigits] = '\0';
	for (--mydigits; mycount; --mydigits)
	{
		numstr[mydigits] = (mycount % 10) + '0';
		mycount /= 10;
	}
	return (numstr);
}
