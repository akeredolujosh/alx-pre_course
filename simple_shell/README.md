/**
* Text in the README.md was coppied from ALX
* The README.md contains text of expected task
*/

0x16. C - Simple Shell
Project to be done in teams of 2 people (Akeredolu O. Joshua and Tsitsi Ndhlovu)
Background Context
Write a simple UNIX command interpreter.
Requirements
General
Allowed editors: vi, vim, emacs
All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All your files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Your shell should not have any memory leaks
No more than 5 functions per file
All your header files should be include guarded
Use system calls only when you need to (why?)
Write a README with the description of your project
You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker
Tasks
0. Betty would be proud
mandatory
Write a beautiful code that passes the Betty checks
1. Simple shell 0.1
mandatory
Write a UNIX command line interpreter.
Usage: simple_shell
Your Shell should:
Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
You don’t have to:
use the PATH
implement built-ins
handle special characters : ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments
2. Simple shell 0.2
mandatory
Simple shell 0.1 +
Handle command lines with arguments
3. Simple shell 0.3
mandatory
Simple shell 0.2 +
Handle the PATH
fork must not be called if the command doesn’t exist
4. Simple shell 0.4
mandatory
Simple shell 0.3 +
Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit
5. Simple shell 1.0
mandatory
Simple shell 0.4 +
Implement the env built-in, that prints the current environment
