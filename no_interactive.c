#include "shell.h"
/**
 * no_interactive - run the program in non interactive mode
 * @argv: name of executable for the errors
 *
 */
void no_interactive(char *argv[])
{
	char *str_command = NULL;
	size_t len = 0;
	char **arr_token;
	status = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (get_input(&str_command, &len) != -1)
		{
			arr_token = tokenize_command(str_command);
			if (arr_token == NULL)
				continue;
			if (execute_command(arr_token, argv) == 1)
			{
				free(arr_token);
				continue;
			}
			free(arr_token);
		}
		free(str_command);
		exit(status);
	}
}
