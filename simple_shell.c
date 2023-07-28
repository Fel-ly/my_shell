#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
* main - main program that runs shell
*
* @ac: argument count
* @av: argument vector
* @env: environment variable
*
* Return: value 0
*/

int main(int ac, char *av[], char **env)
{
	char *buf[] = NULL, *prompt = "Hello:| ";
	size_t buf_size = 0;
	ssize_t bytes;
	pid_t pid;
	int status;
	bool from_pipe = false;
	struct stat statbuf;

	while (1 && !from_pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
			from_pipe = true;
		write(STDOUT_FILENO, prompt, 8);
		bytes = getline(&buf, &buf_size, stdin);
		if (bytes == -1)
		{
			perror("Error |getline|");
			free(buf);
			exit(EXIT_FAILURE);
		}
		if (buf[bytes - 1] == '\n')
			buf[bytes - 1] = '\0';
		pid = fork();
		if (pid == -1)
		{
			perror("Error |fork|");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			execute(buf , &statbuf, env);
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error |wait|");
			exit(EXIT_FAILURE);
		}
	}
	free(buf);
	return (0);
}

/**
 * execute - execute function
 *
 * @arguments: pointer to arguments array
 * @env: environment variable
 * @statbuf: buffer status
 *
 * Return: no value
 *
 */

int execute(char *arguments[], struct stat *statbuf, char **env)
{
	int ac;
	char **av;

	for (ac = 0; arguments[ac] != NULL; ac++)
		;

	av = split_string(arguments[0], " ", &ac);

	if (!check_file_status(av[0], statbuf))
	{
		perror("Error |file status|");
		exit(EXIT_FAILURE);
	}

	execve(av[0], av, env);

	perror("Error |execve|");
	exit(EXIT_FAILURE);
}

/**
 * handle_error - handles errors in file
 *
 * @pid: process ID
 *
 */

void handle_error(pid_t pid)
{
	if (pid == -1)
	{
		printf("Error");
		exit(EXIT_FAILURE);
	}
}

/**
 * check_file_status - checks the status of a file
 *
 * @pathname: name of path taken
 * @statbuf: status of buffer
 *
 * Return: file status
 */

bool check_file_status(char *pathname, struct stat *statbuf)
{
	int stat_return;

	stat_return = stat(pathname, statbuf);

	if (stat_return == 0)
	{
		return (true);
	}

	return (false);
}
