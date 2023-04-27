#include "shell.h"
/**
 * found_path - find a file in a PATH to execute
 * @command: command to found in PATH
 *
 * Return: new command or NULL if not found
 */
char *found_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy;
	char *token, *result = NULL;
	char file_path[1024];
	long unsigned int len = 0;

	if (path == NULL)
	{
		return (NULL);
	}
	path_copy = strdup(path);
	if(path_copy == NULL)
		return (NULL);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		len = snprintf(file_path, sizeof(file_path), "%s/%s", token, command);
		if (len > sizeof(file_path))
		{
			break;
		}
		if (access(file_path, F_OK) == 0)
		{
			result = strdup(file_path);
			free(path_copy);
			return (result);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
