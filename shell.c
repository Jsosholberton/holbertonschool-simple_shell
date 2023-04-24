#include "shell.h"

/**
 * tokenize_command - Tokenizes the input command.
 * @str_command: The input command to tokenize.
 * @arr_token: The array to store the tokens.
 *
 * Return: Number of tokens in the command.
 */
int tokenize_command(char *str_command, char **arr_token)
{
	int num_tokens = 0;
	char *token;

	token = strtok(str_command, " '`\\*&#\t");
	while (token != NULL)
	{
		arr_token[num_tokens++] = token;
		token = strtok(NULL, " \t");
	}
	arr_token[num_tokens] = NULL;
	return (num_tokens);
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
		free(arr_token);
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

	printf("$ ");
	read = getline(str_command, len, stdin);
	if (read == -1)
	{
		printf("\n");
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
	int num_tokens;
	char **arr_token;

	while (1)
	{
		read = get_input(&str_command, &len);
		if (read == -1)
			break;

		arr_token = (char **)malloc(sizeof(char *) * 2);
		if (arr_token == NULL)
		{
			perror("Error malloc: ");
			return (1);
		}
		num_tokens = tokenize_command(str_command, arr_token);
		if (num_tokens == 0)
		{
			printf("Error: Token\n");
			free(arr_token);
			continue;
		}
		if (execute_command(arr_token, argv) == 1)
		{
			free(arr_token);
			continue;
		}
	}
	free(str_command);
	return (0);
}
