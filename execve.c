#include "sshell.h"


/**
 * splitstring - splits a string to make it an array of words
 *
 * @str: string to be split
 * @delim: delimiter
 *
 * Return: array of pointers to words
 */

char **splitstring(char *str, const char *delim)
{
	int i, n;
	char **array;
	char *tokn;
	char *cpy;

	cpy = malloc(_strlen(str) + 1);
	if (cpy == NULL)
	{
		perror(_getenv("_"));
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';

	tokn = strtok(cpy, delim);
	array = malloc((sizeof(char *) * 2));
	array[0] = _strdup(tokn);

	i = 1;
	n = 3;
	while (tokn)
	{
		tokn = strtok(NULL, delim);
		array = _realloc(array, (sizeof(char *) * (n - 1)), (sizeof(char *) * n));
		array[i] = _strdup(tokn);
		i++;
		n++;
	}
	free(cpy);
	return (array);
}

/**
 * execute - executes a command
 * @argv: array of arguments
 */

void execute(char **argv)
{

	int d, status;

	if (!argv || !argv[0])
		return;
	d = fork();
	if (d == -1)
	{
		perror(_getenv("_"));
	}
	if (d == 0)
	{
		execve(argv[0], argv, environ);
			perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	wait(&status);
}

/**
 * _realloc - Reallocates memory block
 *
 * @ptr: previous pointer
 * @old_size: old size of previous pointer
 * @new_size: new size for our pointer
 *
 * Return: New resized Pointer
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;
	char *old;

	unsigned int i;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new = malloc(new_size);
	old = ptr;
	if (new == NULL)
		return (NULL);

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new[i] = old[i];
		free(ptr);
		for (i = old_size; i < new_size; i++)
			new[i] = '\0';
	}
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			new[i] = old[i];
		free(ptr);
	}
	return (new);
}

/**
 * freearr - frees the array of pointers arr
 *
 *@arr: array of pointers
 */

void freearr(char **arr)
{
	int i;

	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}
