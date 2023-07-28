#include "sshell.h"

/**
 * _getenv - gets the value of the global variable
 *
 * @name: name of the global variable
 *
 * Return: string of value
 */

char *_getenv(const char *name)
{
	int i, j;
	char *val;

	if (!name)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				val = (environ[i] + j + 1);
				return (val);
			}
		}
	}
	return (0);
}


/**
 * add_node_end - adds a new node at the end of a list
 *
 * @head: double pointer to linked list
 * @str: pointer to string in previous first node
 *
 * Return: address of the new node
 */

list_path *add_node_end(list_path **head, char *str)
{

	list_path *tmp;
	list_path *new;

	new = malloc(sizeof(list_path));

	if (!new || !str)
	{
		return (NULL);
	}

	new->dir = str;

	new->p = '\0';
	if (!*head)
	{
		*head = new;
	}
	else
	{
		tmp = *head;

		while (tmp->p)
		{

			tmp = tmp->p;
		}

		tmp->p = new;
	}

	return (*head);
}


/**
 * linkpath - creates a linked list for path directories
 *
 * @path: string of path value
 *
 * Return: pointer to the created linked list
 */

list_path *linkpath(char *path)
{
	list_path *head = '\0';
	char *tokn;
	char *cpath = _strdup(path);

	tokn = strtok(cpath, ":");
	while (tokn)
	{
		head = add_node_end(&head, tokn);
		tokn = strtok(NULL, ":");
	}

	return (head);
}

/**
 * _path - finds the pathname of a filename
 *
 * @fname: name of file or command
 * @head: head of linked list of path directories
 *
 * Return: pathname of filename. NULL if no match
 */

char *_path(char *fname, list_path *head)
{
	struct stat st;
	char *string;

	list_path *tmp = head;

	while (tmp)
	{

		string = concat_all(tmp->dir, "/", fname);
		if (stat(string, &st) == 0)
		{
			return (string);
		}
		free(string);
		tmp = tmp->p;
	}

	return (NULL);
}

/**
 * free_list - frees a list_t
 *
 *@head: pointer to linked list
 */
void free_list(list_path *head)
{
	list_path *storage;

	while (head)
	{
		storage = head->p;
		free(head->dir);
		free(head);
		head = storage;
	}

}
