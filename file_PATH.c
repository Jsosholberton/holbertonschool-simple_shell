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
	char *token;
	char file_path[1024];
	char *result;

	if (path == NULL)
	{
		return (NULL);
	}
	path_copy = strdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		snprintf(file_path, sizeof(file_path), "%s/%s", token, command);
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
