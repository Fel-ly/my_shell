#include "sshell.h"

/**
* checkbuild - checks if the command is build-in command
*
* @arg: array of arguments
*
* Return: pointer to function that takes arg and returns void
*/

void(*checkbuild(char **arg))(char **arg)
{
	int i, j;
	mybuild F[] = {
		{"exit", exit_shell},
		{"env", env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	for (i = 0; F[i].name; i++)
	{
		j = 0;
		if (F[i].name[j] == arg[0][j])
		{
			for (j = 0; arg[0][j]; j++)
			{
				if (F[i].name[j] != arg[0][j])
					break;
			}
			if (!arg[0][j])
				return (F[i].func);
		}
	}
	return (0);
}
