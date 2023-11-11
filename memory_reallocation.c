#include "shell.h"

/**
 * _realloc - reallocates a pointer to increase the space
 * @ptr: pointer to the old array(previous)
 * @size: pointer to number of elements in the old array(previous)
 *
 * Return: pointer to the new array(new/current)
 */
char **_realloc(char **ptr, size_t *size)
{
	char **new;
	size_t i;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (new);
}
