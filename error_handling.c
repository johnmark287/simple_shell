#include "shell.h"

/**
 * print_error - prints error messages to standard error stream.
 * @vars: pointer to struct of variables.
 * @message: message to print to stderr stream.
 *
 * Return: nothing.
 */
void print_error(vars_t *vars, char *message)
{
	char *count;

	puts_two(vars->argv[0]);
	puts_two(": ");
	count = _uitoa(vars->count);
	puts_two(count);
	free(count);
	puts_two(": ");
	puts_two(vars->av[0]);
	if (message)
	{
		puts_two(message);
	}
	else
		perror("");
}

/**
 * puts_two - prints a string to standard error stream.
 * @str: string to print to stderr stream
 *
 * Return: nothing.
 */
void puts_two(char *str)
{
	ssize_t num, len;

	num = _string_len(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - converts an unsigned int value to a string.
 * @count: unsigned int value to convert.
 *
 * Return: pointer to the converted string.
 */
char *_uitoa(unsigned int count)
{
	char *num_str;
	unsigned int temp, digits;

	temp = count;
	for (digits = 0; temp != 0; digits++)
		temp /= 10;
	num_str = malloc(sizeof(char) * (digits + 1));
	if (num_str == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	num_str[digits] = '\0';
	for (--digits; count; --digits)
	{
		num_str[digits] = (count % 10) + '0';
		count /= 10;
	}
	return (num_str);
}
