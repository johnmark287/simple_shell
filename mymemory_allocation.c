#include "shell.h"

/**
 * _Realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */
char **_Realloc(char **myptr, size_t *mysize)
{
	char **mynew;
	size_t i;

	mynew = malloc(sizeof(char *) * ((*mysize) + 10));
	if (mynew == NULL)
	{
		free(myptr);
		return (NULL);
	}
	for (i = 0; i < (*mysize); i++)
	{
		mynew[i] = myptr[i];
	}
	*mysize += 10;
	free(myptr);
	return (mynew);
}
