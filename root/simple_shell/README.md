# This is an ALX Simple Shell Team Project

> This is a collaborative ALX project on Simple_Shell. The task is to create a simple_shell that mimics the Bash shell.

## The project was completed using

- Shell
- Betty
- C language

## General Requirement

1.  All files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
2.  All files should end with a new line
3.  A README.md file, at the root of the folder of the project is mandatory
4.  Use Betty style. All files must be checked using betty-style.pl and betty-doc.pl
5.  Shell should not have any memory leaks
6.  There should not be more than 5 functions per file
7.  All header files should be include guarded
8.  Write a README with the description of the project


## Description ##

This project is a simple UNIX command language interpreter that will read commands from either a file or standard input and then executes them.

### Wworking Format
1. Prints a prompt and waits for a command from the user
2. Creates a child process in which the command is checked
3. Checks for in-builts, aliases in the PATH, and local executable programs
4. The child process will be replaced by the command, that accepts arguments
5. When the command is given, the program returns to the parent process and prints the prompt
6. The program is ready to intiate new command
7. To exit: press Ctrl-D or enter "exit" (with or without a status)
8. It can work in non interactive mode. 

### Compilation

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`
