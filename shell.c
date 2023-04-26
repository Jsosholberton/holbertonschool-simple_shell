#include "shell.h"

/**
 * tokenize_command - Tokenizes the input command.
 * @str_command: The input command to tokenize.
 *
 * Return: Number of tokens in the command.
 */
char **tokenize_command(char *str_command)
{
	int num_tokens = 0;
	int capacity = 16;
	char **tokens;
	char *token;

	tokens = malloc(capacity * sizeof(char *));
	if (!tokens)
	{
		perror("Malloc tokens");
		exit(1);
	}
	token = strtok(str_command, " \t\r\n");
	while (token != NULL)
	{
		tokens[num_tokens] = token;
		num_tokens++;
		if (num_tokens >= capacity)
		{
			capacity = (int) (capacity * 1.5);
			tokens = realloc(tokens, capacity * sizeof(char *));
			if (tokens == NULL)
			{
				perror("error realloc");
				exit(1);
			}
		}
		token = strtok(NULL, " \t\r\n");
	}
	if (num_tokens == 0)
	{
		free(tokens);
		return (NULL);
	}
	if (found_path(tokens[0]) != NULL)
	{
		tokens[0] = found_path(tokens[0]);
	}
	tokens[num_tokens] = NULL;
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
	int status;

	sub_process = fork();
	if (sub_process == -1)
	{
		perror("Error fork: ");
		return (1);
	}
	else if (sub_process == 0)
	{
		execve(arr_token[0], arr_token, NULL);
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
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

	while (1)
	{
		no_interactive(argv);
		printf("#cisfun$ ");
		read = get_input(&str_command, &len);
		if (read == -1)
		{
			printf("\n");
			break;
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
	}
	free(str_command);
	return (0);
}
