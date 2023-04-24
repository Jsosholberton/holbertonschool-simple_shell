#ifndef shell_h
#define shell_h
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int tokenize_command(char *str_command, char **arr_token);
int execute_command(char **arr_token, char *argv[]);
ssize_t get_input(char **str_command, size_t *len);
int main(int argc, char *argv[]);


#endif
