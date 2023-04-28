#ifndef shell_h
#define shell_h
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

char **tokenize_command(char *str_command);
int execute_command(char **arr_token, char *argv[]);
ssize_t get_input(char **str_command, size_t *len);
int main(int argc, char *argv[], char **environ);
void no_interactive(char *argv[], char **environ);
char *found_path(char *command);

extern int status;
extern char **environ;

#endif
