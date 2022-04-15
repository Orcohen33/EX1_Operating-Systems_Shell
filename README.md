
# Operating system - Shell
  We were asked to build our shell program.

## Explanation of shell and code:
   #### What is shell? :
   
   A shell is a computer program which exposes an operating system's services to a human user or other programs.
   
   It is a command interpreter which is used to execute commands on a computer.
   
   Command-line shells require the user to be familiar with commands and their calling syntax, and to understand concepts about the shell-specific scripting language (for example, bash).

   #### About the code:
   We've asked to write a shell with the following features:
   - Built-in commands: EXIT, ECHO, DIR, TCP PORT, CD, COPY, DELETE.
   - System commands: exit, echo, dir, tcp port, cd, copy, delete.
   - Fork and exec commands: exit, echo, dir, tcp port, cd, copy, delete.

   Inside the function 'handle_cmd()' we have 3 methods:
   - 'built_in_methods()'
   - 'system_commands()'
   - 'fork_and_exec_commands()'
   
  To use any of the methods, you must put in the comment the other methods that you do not want to use.

        

## Conclusions from the project:
  This project is a part of the course "Operating Systems" at the University of Ariel.
  
  While we wrote this project we learned how shell works and how to use it.
  
  We also learned how to use fork and exec functions, and system call functions.

  ### We've learned how to use the following functions:
  - fopen
  - fread
  - fwrite
  - fclose
  - unlink
  - system
  - chdir
  - fork
  - exec
  - exit

## How to use:
1. Clone this repository.
2. Open terminal in the folder where you cloned this repository.
3. To compile the code , write in terminal `make main` 
4. To run the code, write in terminal `./main`
5. To compile server, write in terminal `make server`
6. To run server , write in terminal `./server`
7. When finished to run, write in terminal `make clean`

### A video that you can see how to run the code:

Note : This video captured before we renamed `shell.c` to `main.c` so instead `make shell` write `make main`

https://user-images.githubusercontent.com/92351152/163588102-8a1d5a0e-2cd8-4e16-a4a7-ca93974176c8.mp4

