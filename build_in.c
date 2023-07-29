#include "sshell.h"

/**
 * exit_shell - exits the shell
 *
 * @arr: array of words
 */

void exit_shell(char **arr)
{
	int i, n;

	if (arr[1])
	{
		n = _atoi(arr[1]);
		if (n <= -1)
			n = 2;
		freearr(arr);
		exit(n);
	}
	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
	exit(0);
}

/**
 * _atoi - converts a string into an integer
 *
 *@s: pointer to a string
 *
 *Return: the integer
 */

int _atoi(char *s)
{
	int i, integer, sign = 1;

	i = 0;
	integer = 0;
	while (!((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'))
	{
		if (s[i] == '-')
		{
			sign = sign * (-1);
		}
		i++;
	}
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		integer = (integer * 10) + (sign * (s[i] - '0'));
		i++;
	}
	return (integer);
}

/**
 * env - prints the current environment
 *
 * @arg: array of arguments
 */
void env(char **arg __attribute__ ((unused)))
{

	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}

}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 * @arr: array of entered words
 */
void _setenv(char **arr)
{
	int i, j, k;

	if (!arr[1] || !arr[2])
	{
		perror(_getenv("_"));
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (arr[1][j] == environ[i][j])
		{
			while (arr[1][j])
			{
				if (arr[1][j] != environ[i][j])
					break;

				j++;
			}
			if (arr[1][j] == '\0')
			{
				k = 0;
				while (arrv[2][k])
				{
					environ[i][j + 1 + k] = arv[2][k];
					k++;
				}
				environ[i][j + 1 + k] = '\0';
				return;
			}
		}
	}
	if (!environ[i])
	{

		environ[i] = concat_all(arr[1], "=", arr[2]);
		environ[i + 1] = '\0';

	}
}

/**
 * _unsetenv - Removes an environment variable
 *
 * @arr: array of entered words
 */
void _unsetenv(char **arr)
{
	int i, j;

	if (!arr[1])
	{
		perror(_getenv("_"));
		return;
	}
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (arr[1][j] == environ[i][j])
		{
			while (arr[1][j])
			{
				if (arr[1][j] != environ[i][j])
					break;

				j++;
			}
			if (arr[1][j] == '\0')
			{
				free(environ[i]);
				environ[i] = environ[i + 1];
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				return;
			}
		}
	}
}
