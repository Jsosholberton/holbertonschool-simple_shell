# Simple Shell

## Introduction
This is a C command-line program that implements a basic version of the Unix shell. It allows running simple commands, commands with arguments, and commands with options. It also supports running commands in interactive and non-interactive modes.

## Requirements
This program can be run on any operating system that has a C compiler and a command interpreter. It has been tested on Linux.

## Installation
To compile this program, run the following command in the terminal:

    *gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

This will generate an executable file called hsh in the current directory.

## Usage
Interactive Mode
To run the program in interactive mode, simply run the following command in the terminal:

```./hsh```

This will display a prompt on the screen, where you can enter the commands you wish to execute. For example:
```
$ ./hsh
#cisfun ls
README.md  file_PATH.c  hsh  no_interactive.c  shell.c  shell.h
#cisfun$ pwd
/home/user
#cisfun$ exit
```

## Non-Interactive Mode
To run the program in non-interactive mode, you can use the following syntax:

```echo "command" | ./hsh```

For example:

```
$ echo "ls" | ./hsh
README.md  file_PATH.c  hsh  no_interactive.c  shell.c  shell.h
$ echo "ls -l" | ./hsh
total 16
-rw-r--r-- 1 root root    15 Apr 24 20:14 README.md
-rw-r--r-- 1 root root   842 Apr 27 14:16 file_PATH.c
-rwxr-xr-x 1 root root 17944 Apr 27 19:52 hsh
-rw-r--r-- 1 root root   863 Apr 27 19:38 no_interactive.c
-rw-r--r-- 1 root root  3280 Apr 27 19:34 shell.c
-rw-r--r-- 1 root root   468 Apr 27 19:35 shell.h
$ echo "pwd" | ./hsh
/home/user
$
```

## List of files
```
1. file_PATH
2. no_interactive
3. shell.c
4. shell.h
```

Credits
This program was developed by Johnatan Steven Ortiz Salazar.
