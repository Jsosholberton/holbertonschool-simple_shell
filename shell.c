#include "shell.h"

int status = 127;

/**
 * tokenize_command - Tokenizes the input command.
 * @str_command: The input command to tokenize.
 *
 * Return: Number of tokens in the command.
 */
char **tokenize_command(char *str_command)
{
	int num_tokens = 0, capacity = 16;
	char **tokens = NULL;
	char *token = NULL;

	tokens = malloc(capacity * sizeof(char *));
	if (!tokens)
	{
		perror("Malloc tokens");
		exit(1);
	}
	token = strtok(str_command, " \t\r\n");
	if(token == NULL)
		return (NULL);
	while (token != NULL)
	{
		if (num_tokens >= capacity)
		{
			capacity = (int) (capacity * 1.5);
			tokens = realloc(tokens, capacity * sizeof(char *));
			if (tokens == NULL)
			{
				perror("Realloc tokens");
				free(tokens);
				return (NULL);
			}
		}
		tokens[num_tokens++] = token;
		token = strtok(NULL, " \t\r\n");
	}
	tokens[num_tokens] = NULL;
	free(token);
	return (tokens);
}

/**
 * execute_command - Executes a command in a child process.
 * @arr_token: The array of tokens representing the command.
 * @argv: The array of arguments to the program.
 *
 * Return: 0 on success, 1 on failure.
 */
int execute_command(char **arr_token, char *argv[])
{
	pid_t sub_process;
	int error = 1;
	char *first_argument;

	if(arr_token[0] == NULL)
	{
		return (error);
	}
	first_argument = found_path(arr_token[0]);
	if (first_argument == NULL && arr_token == NULL)
	{
		return (error);
	}
	if (access(arr_token[0], X_OK) == -1 && first_argument == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv[0], error,
			arr_token[0]);
		return (error);
	}
	sub_process = fork();
	if (sub_process == -1)
	{
		perror("Error fork: ");
		return (error);
	}
	else if (sub_process == 0)
	{
		if (first_argument != NULL)
		{
			execve(first_argument, arr_token, environ);
		}
		else
		{
       		execve(arr_token[0], arr_token, environ);
		}
                perror(argv[0]);
		status = 2;
		free(arr_token);
                exit(EXIT_FAILURE);
        }
	else
	{
		wait(&status);
	}
	free(first_argument);
	return (0);
}

/**
 * get_input - Get input from user.
 * @str_command: Pointer to the input string.
 * @len: Pointer to the length of the input string.
 *
 * Return: Number of characters read.
 */
ssize_t get_input(char **str_command, size_t *len)
{
	ssize_t read;
	int i;

	read = getline(str_command, len, stdin);
	if (read == -1)
	{
		return (-1);
	}
	else
	{
		for (i = 0; i < read; i++)
		{
			if ((*str_command)[i] == '\n')
			{
				(*str_command)[i] = '\0';
				break;
			}
		}
	}
	return (read);
}

/**
 * main - Main entry point of the shell.
 * @argc: The number of arguments to the program.
 * @argv: The array of arguments to the program.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	char *str_command = NULL;
	size_t len = 0;
	ssize_t read;
	char **arr_token;
	int i = 0;

	while (1)
	{
		no_interactive(argv);
		printf("#cisfun$ ");
		read = get_input(&str_command, &len);
		if (read == -1)
		{
			printf("\n");
			exit(status);
		}

		arr_token = tokenize_command(str_command);
		if (arr_token == NULL)
			continue;
		if (execute_command(arr_token, argv) == 1)
		{
			free(arr_token);
			continue;
		}
		free(arr_token);
		i++;
	}
	if (read != -1)
		free(str_command);
	if(read == -1 && i > 0)
	{
		free(str_command);
	}
	return (0);
}
