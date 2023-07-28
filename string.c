#include "sshell.h"

/**
 * _strdup - copies string to a newly allocated space in memory
 *
 * @str: string
 * Return: pointer to a string
 */

char *_strdup(char *str)
{
	int a, b;
	char *newsp;

	if (!str)
	{
		return (NULL);
	}
	for (b = 0; str[b] != '\0';)
	{
		b++;
	}
	newsp = malloc(sizeof(char) * b + 1);
	if (!newsp)
	{
		return (NULL);
	}
	for (a = 0; a < b; a++)
	{
		newsp[a] = str[a];
	}
	newsp[b] = str[b];
	return (newsp);
}

/**
 * _strlen - gives the length of a string
 *
 * @s: pointer to the string
 * Return: the length of string
 */
int _strlen(char *s)
{
	int a = 0;

	while (*(s + a) != '\0')
	{
		a++;
	}
	return (a);
}

/**
 * _putchar - writes the character c to standard output
 *
 * @c: The character to be printed
 *
 * Return: value 1.
 * On error, -1 returned and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @str: pointer to string
 */

void _puts(char *str)
{
	int a = 0;

	while (str[a])
	{
		_putchar(str[a]);
		a++;
	}
}
