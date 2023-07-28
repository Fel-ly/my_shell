#include "sshell.h"
#include <unistd.h>

/**
 * main - runs the Shell
 * Return: 0 on success
 */

int main(void)
{
	ssize_t len = 0;
	char *buf = NULL, *val, *pathname, **argv;
	size_t size = 0;
	list_path *head = '\0';
	void (*f)(char **);
/*	void isatty(void);
	void EOF(int len, char *buf);*/

	while (len != EOF)
	{
		_isatty();
		len = getline(&buf, &size, stdin);
		_EOF(len, buf);
		argv = splitstring(buf, " \n");
		if (!argv || !argv[0])
			execute(argv);
		else
		{
			val = _getenv("PATH");
			head = linkpath(val);
			pathname = _path(argv[0], head);
			f = checkbuild(argv);
			if (f)
			{
				free(buf);
				f(argv);
			}
			else if (!pathname)
				execute(argv);
			else if (pathname)
			{
				free(argv[0]);
				argv[0] = pathname;
				execute(argv);
			}
		}
	}
	free_list(head);
	freearr(argv);
	free(buf);
	return (0);
}

/**
* _EOF - End of File
*
* @len: length
* @buf: buffer
*/

void _EOF(int len, char *buf)
{
	(void)buf;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buf);
		}
		exit(0);
	}
}

/**
  * _isatty - verify if fildes is associated with terminal device
  */

void _isatty(void)
{
	if (isatty(STDIN_FILENO))
		_puts("#hope:) ");
}
