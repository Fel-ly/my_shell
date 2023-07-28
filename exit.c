#include "shell.h"

/**
 * exit - exits the shell
 * @data: data ,status and arguments
 *
 * Return: 0 on success.
 */
int exit(data_shell *data)
{
	int status, num, len, is_digit;
	char *error;

	if (data->args[1] != NULL)
	{
		status = _atoi(data->args[1]);
		num = _isdigit(data->args[1]);
		len =len(data->args[1]);
		if (!num || len > 10)
		{
			error = "Error |Wrong argument type|\n";
			write(STDERR_FILENO, error, len(error));
			data->status = 2;
			return (1);
		}

		data->status = (status % 256);
	}
	return (0);
}
