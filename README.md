# <a href="url"><img src="https://cdn3.iconfinder.com/data/icons/egg/500/Egg_food_cracked_whipped-512.png" align="middle" width="100" height="100"></a> simple_shell


## Table of Contents
* [Description](#description)
* [File Structure](#file-structure)
* [Requirements](#requirements)
* [Installation](#installation)
* [Usage](#usage)
* [Example of Use](#example-of-use)
* [Bugs](#bugs)
* [Authors](#authors)
* [License](#license)

## Description
Simple_shell is a command line interpreter, also known as a shell, inspired by the original Unix shell developed by Ken Thompson in 1971. This shell is deliberately designed to be minimalistic while encompassing essential features of a traditional Unix-like command line interface. It incorporates standard functions and system calls such as `access`, `execve`, `exit`, `fork`, `free`, `fstat`, `getline`, `malloc`, `perror`, `signal`, `stat`, `wait`, and `write`.

## File Structure
* [AUTHORS](AUTHORS) - List of contributors to this repository
* [man_1_simpleShell](man_1_simple_shell) - Manual page for the simple_shell
* [shell.h](shell.h) - program header file
* [mybuiltins.c](mybuiltins.c) - major builtin functions
  * `checkForBuiltins` - checks to see if the user's command matches a builtin
  * `newExit` - exits the shell with the option of a specified status
  * `_envs` - prints the shell's environment variables to the standard output
  * `newSetenv` - initializes a new environment variable, or modifies an existing one
  * `newUnsetenv` - removes an environment variable
* [mybuiltins2.c](mybuiltins2.c) - helper functions for the builtins
  * `addKey` - creates a new environment variable
  * `findKey` - finds an environment variable in the environment array
  * `addValue` - creates a new environment variable string
  * `_atois` - converts a string into a non-negative integer
* [myenvironment.c](myenvironment.c) - functions related to the environment
  * `makeEnv` - creates the shell's environment from the parent process
  * `freeEnv` - frees the shell's environment
* [myerrors.c](myerrors.c) - functions related to printing errors
  * `printError` - prints an error message to the standard error
  * `_Puts2` - prints a string to the standard error
  * `_Uitoa` - converts an unsigned integer to a string
* [mymemory_allocation.c](mymemory_allocation.c) - memory allocation functions
  * `_Realloc` - a custom realloc function for arrays of pointers
* [mynewStrtok.c](mynewStrtok.c) - custom strtok and helper functions
  * `checkMatch` - checks if a character matches any in a string
  * `newStrtok` - a custom strtok for the shell
* [mypath.c](mypath.c) - functions related to executing commands
  * `pathExecute` - executes a command in the PATH
  * `findPath` - finds the PATH environment variable
  * `checkForPath` - checks if the command is in the PATH
  * `executeCwd` - executes a command with an absolute path
  * `checkForDir` - checks if the command contains an absolute path
* [mysimple_shell.c](mysimple_shell.c) - essential functions to the shell
  * `main` - the main function of the program
  * `sigHandler` - handles SIGINT
* [mystrfunc.c](mystrfunc.c) - functions related to string manipulation
  * `_Puts` - writes a string to standart output
  * `_Strdup` - duplicates a string
  * `_Strcmpr` - compares two strings
  * `_Strcat` - concatenates two strings with a `/` in the middle
  * `_Strlen` - calculates the length of a string
* [mytokenize.c](mytokenize.c) - tokenizing function
  * `mytokenize` - creates an array of tokens from a buffer with a specified delimiter

## Requirements

simple_shell, which is designed to run in the `Ubuntu 14.04 LTS` linux environment and is to be compiled using the GNU compiler collection v. `gcc 4.8.4` with flags`-Wall, -Werror, -Wextra, and -pedantic.`

## Installation

   - Clone this repository: `git clone "https://github.com/johnmark287/simple_shell.git"`
   - Change directories into the repository: `cd simple_shell`
   - Compile: `gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`
   - Run shell in the interactive mode: `./hsh`
   - Or run the shell in non-interactive mode: example `echo "pwd" | ./hsh`

## Usage

The simple_shell is designed to execute commands in a similar manner to sh, however with more limited functionality. The development of this shell is ongoing. The below features will be checked as they become available (see man page for complete information on usage):

### Features
- [x] uses the PATH
- [x] implements builtins
- [x] handles command line arguments
- [x] custom strtok function
- [x] uses exit status
- [x] shell continues upon Crtl+C (**^C**)
- [x] handles comments (#)
- [x] handles **;**
- [ ] custom getline type function
- [ ] handles **&&** and **||**
- [ ] aliases
- [ ] variable replacement


### Builtins

- [x] exit
- [x] env
- [x] setenv
- [x] unsetenv
- [ ] cd
- [ ] help
- [ ] history

## Example of Use
Run the executable in your terminal after compiling:
```
$ ./hsh
$ # This is our rendition of the shell
$ ls -al
total 100
drwxrwxr-x  3 vagrant vagrant  4096 Jul 19 22:49 .
drwxr-xr-x 14 vagrant vagrant  4096 Jul 17 22:37 ..
-rw-rw-r--  1 vagrant vagrant   144 Jul 19 17:16 AUTHORS
-rw-rw-r--  1 vagrant vagrant  2367 Jul 19 22:33 mybuiltins2.c
-rw-rw-r--  1 vagrant vagrant  2764 Jul 19 22:14 mybuiltins.c
-rw-rw-r--  1 vagrant vagrant   710 Jul 16 01:03 myenvironment.c
-rw-rw-r--  1 vagrant vagrant  1217 Jul 16 03:24 myerrors.c
drwxrwxr-x  8 vagrant vagrant  4096 Jul 19 22:34 .git
-rwxrwxr-x  1 vagrant vagrant 32287 Jul 19 22:34 hsh
-rw-rw-r--  1 vagrant vagrant  1792 Jul 19 22:12 man_1_simple_shell
-rw-rw-r--  1 vagrant vagrant   484 Jul 15 20:09 mymemory_allocation.c
-rw-rw-r--  1 vagrant vagrant  1273 Jul 18 21:00 mynew_strtok.c
-rw-rw-r--  1 vagrant vagrant  3427 Jul 19 22:06 mypath.c
-rw-rw-r--  1 vagrant vagrant  2347 Jul 19 22:49 README.md
-rw-rw-r--  1 vagrant vagrant  1769 Jul 19 22:04 shell.h
-rw-rw-r--  1 vagrant vagrant  1480 Jul 18 21:15 simple_shell.c
-rw-rw-r--  1 vagrant vagrant  2111 Jul 16 01:10 mystrfunc.c
-rw-rw-r--  1 vagrant vagrant   719 Jul 19 21:46 mytokenize.c
```
## Bugs
At this time, there are no known bugs.

## Authors
[Johnmark Muhando](https://github.com/johnmark287)

[Moses Njau](https://github.com/MoseNjau)

## License
This is an open source project and you are free to download it.
