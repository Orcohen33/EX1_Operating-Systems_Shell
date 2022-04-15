
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#define clear() printf("\033[H\033[J")
#define SA struct sockaddr

void delete(char *filename);
void copy(char *src_name, char *dest_name);
void func(int sockfd);

/* using printf()*/
void printDir(){
    char dir_name[1024];
    getcwd(dir_name, sizeof(dir_name));
    printf("\n%s>", dir_name);
}

/* using printf*/
void echo(char **s){
    int i;
    for(i=0; s[i]!=NULL; i++){
        printf("%s ", s[i]);
    }
    printf("\n");
}

/* using DIR*/
void dir(){
    DIR *dir;
    struct dirent *sd;
    dir = opendir(".");
    if(dir == NULL){
        printf("error");
        exit(1);
    }
    while( (sd=readdir(dir)) != NULL){
        printf("%s  ", sd->d_name);
    }
    closedir(dir);
}

/* using chdir()
    chdir is a system call that changes the current working directory.
    It takes a pathname as an argument and changes the current working directory to that pathname.
    If the pathname is not an absolute pathname, the pathname is interpreted relative to the current working directory.
    If the pathname is not a valid pathname, the current working directory is not changed.
    If the pathname is a symbolic link, the symbolic link is followed.
    If the pathname is a relative pathname, it is interpreted relative to the current working directory.

    The chdir() function returns 0 on success, or -1 on error.
    The errno variable is set to indicate the error.

    The chdir() function is not available on Windows.

*/
void cd (char *dict){
    if(chdir(dict) == -1){
        printf("error");
        exit(1);
    }
}

/* connect to tcp server */
void tcp_port(){
    int sockfd;
    struct sockaddr_in servaddr;
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8080);
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        return;
    }
    else
        printf("connected to the server..\n");
    // function for chat
    func(sockfd);
    // close the socket
    close(sockfd);
}

void func(int sockfd){
    char buff[80];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf(">>>");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        // bzero(buff, sizeof(buff));
        if ((strncmp(buff, "LOCAL", 5)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}



//        ------------------------------------------------ USING SYSTEM --------------------------------------------------------------------
// /* Print dir using system call */
/* using system function to print dir */
void sys_printDir(){
    char dir_name[1000];
    getcwd(dir_name, sizeof(dir_name));
    char command[1024];
    sprintf(command, "echo %s", dir_name);
    system(command);
    printf(">");
}

/* using system function to echo double pointer input */
void sys_echo(char **buff){
    // Enter all strings from buff into one single char array with for loop
    // the first string will be 'echo' and then all the strings from buff will be concatenated
    char *str = malloc(sizeof(char) * 256);
    strcpy(str, "echo ");
    int i;
    for(i=0; buff[i]!=NULL; i++){
        strcat(str, buff[i]);
        strcat(str, " ");
    }
    // Execute the command
    system(str);
    free(str);
}

/* using system function to create connection with local host via TCP
 connect to local host with tcp connection on port 8080*/
void sys_tcp_port(){
    char *str = malloc(sizeof(char) * 256);
    strcpy(str, "telnet 127.0.0.1 8080");
    system(str);
    free(str);
}

/* using system*/
void sys_dir(){
    system("dir");
}

/* using system() commend to change directory like chdir()*/
void sys_cd(char *dict){
    // Enter string dict into char array and start with 'cd '
    // And then execute the command with system() function
    char *str = malloc(sizeof(char) * 256);
    strcpy(str, "cd ");
    strcat(str, dict);
    printf("%s\n", str);
    system(str);
    free(str);
}

//        ------------------------------------------------ FINISH SYSTEM --------------------------------------------------------------------

//        ----------------------------------------------- USING FORK AND EXEC ---------------------------------------------------------------

/*
    using fork() and exec()
    fork() creates a child process.
    The child process is a copy of the parent process.
    The child process returns a value of 0 to the parent process.
    The parent process returns a value of the child process ID to the calling process.
    The child process ID is used to identify the child process.
    The child process ID is also used to identify the parent process.

    exec() is used to execute a program.
    The exec() function is used to execute a program.
*/
/* this function print the currect directory path to stdout using fork and exec()*/
void fork_printDir(){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        // child process
        char *argv[] = {"pwd", NULL};
        execv("/bin/pwd", argv);
    }
    else{
        // parent process
        wait(NULL);
    }
}

/* this function print all strings come after the word 'echo' to stdout using fork and exec()*/
void fork_echo(char **buff){
    int i;
    pid_t pid;
    pid = fork();
    if(pid == 0){
        // child process
        char *argv[256];
        for(i=0; buff[i]!=NULL; i++){
            argv[i] = buff[i];
        }
        argv[i] = NULL;
        execv("/bin/echo", argv);
    }
    else{
        // parent process
        wait(NULL);
    }
}

/* this function all the files in the working directory to stdout using fork and exec()*/
void fork_dir(){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        // child process
        char *argv[] = {"dir", NULL};
        execv("/bin/dir", argv);
    }
    else{
        // parent process
        wait(NULL);
    }
}

/*this function change the currect directory to the directory specified by the user using fork and exec()*/
void fork_cd(char *dict){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        // child process
        char *argv[] = {"cd", dict, NULL};
        execv("/bin/cd", argv);
    }
    else{
        // parent process
        wait(NULL);
    }
}

/* this function is to create tcp connection with local host via TCP connection */
void fork_tcp_port(){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        // child process
        char *argv[] = {"telnet", "127.0.0.1", "8080", NULL};
        execv("/bin/telnet", argv);
    }
    else{
        // parent process
        wait(NULL);
    }
}
//        ----------------------------------------------- FINISH FORK AND EXEC ---------------------------------------------------------------


/* using fopen(), fread(), fwrite() fclose()*/
void copy(char *src_name, char *dest_name){
    FILE *src, *dest;
    char data;
    src = fopen(src_name, "rb");
    if( src == NULL){
        printf("Error");
        exit(1);
    }
    dest = fopen(dest_name, "wb");
    if( dest == NULL){
        printf("Error");
        exit(1);
    }
    // Char by char
    while(fread(&data, 1, 1, src) == 1){
        fwrite(&data, 1, 1, dest);
    }
    fclose(src);
    fclose(dest);
}

/* using unlink()*/
void delete(char *filename){
    if(unlink(filename)){
        printf("Error");
        exit(1);
    }
}


/* ------------------------------ METHODS FOR COMMAND LINE INTERFACE --------------------------------------------------*/

void built_in_methods(char *commands[], char cmd[], char *splitted[]){
        if(strcmp(commands[0], cmd) == 0){          // EXIT command
        clear();
        exit(0);
    }
    else if (strcmp(commands[1], cmd) == 0){    // ECHO command
        echo(splitted);
    }
    else if (strcmp(commands[2], cmd) == 0){    // DIR command
        dir();
    }
    else if (strcmp(commands[3], cmd) == 0){    // TCP PORT command
        if(strcmp(commands[9],splitted[0])){
            tcp_port();
        }
    }
    else if (strcmp(commands[5], cmd) == 0){    // CD command
        cd(splitted[0]);
    }
    else if (strcmp(commands[6], cmd) == 0){    // COPY command
        copy(splitted[0], splitted[1]);
    }
    else if (strcmp(commands[7], cmd) == 0){    // DELETE command
        delete(splitted[0]);
    }
    else if (strcmp(commands[8], cmd) == 0){    // clear command
        clear();
    }
}

void system_commands(char *commands[], char cmd[], char *splitted[]){
    if(strcmp(commands[0], cmd) == 0){
        clear();
        system("exit");
        exit(0);
    }
    else if(strcmp(commands[1], cmd)==0){
        sys_echo(splitted);
    }
    else if(strcmp(commands[2], cmd)==0){
        sys_dir();
    }
    else if(strcmp(commands[3], cmd)==0){
        if(strcmp(commands[9],splitted[0])){
            printf("\nTCP PORT: \n");
            sys_tcp_port();
        }
    }
    else if(strcmp(commands[5], cmd)==0){
        sys_cd(splitted[0]);
    }
    else if(strcmp(commands[6], cmd)==0){
        copy(splitted[0], splitted[1]);
    }
    else if(strcmp(commands[7], cmd)==0){
        delete(splitted[0]);
    }
    else if(strcmp(commands[8], cmd)==0){
        clear();
    }
}

void fork_and_exec_commands(char *commands[], char cmd[], char *splitted[]){
    if(strcmp(commands[0], cmd) == 0){
        // exit terminal using fork and exec
        exit(0);
    }
    else if(strcmp(commands[1], cmd) == 0){
        fork_echo(splitted);
    }
    else if(strcmp(commands[2], cmd) == 0){
        fork_dir();
    }
    else if(strcmp(commands[3], cmd) == 0){
        if(strcmp(commands[9],splitted[0])){
            fork_tcp_port();
        }
    }
    else if(strcmp(commands[5], cmd) == 0){
        fork_cd(splitted[0]);
    }
    else if(strcmp(commands[6], cmd) == 0){
        copy(splitted[0], splitted[1]);
    }
    else if(strcmp(commands[7], cmd) == 0){
        delete(splitted[0]);
    }
    else if(strcmp(commands[8], cmd) == 0){
        clear();
    }
}

/* --------------------------------------------------------------------------------------------------------------------*/
void splitStr(char* str, char** splitted){
    char *ptr = strtok(str, " ");
    int i = 0;
    while(ptr!=NULL){
        ptr = strtok(NULL, " ");
        splitted[i++] = ptr;
    }
}
void handle_cmd(){
    char cmd[1024];
    char *splitted[512];
    memset(splitted, 0, sizeof(splitted));
    memset(cmd, 0, sizeof(cmd));
    char *commands[10];
        commands[0] = "EXIT";
        commands[1] = "ECHO";
        commands[2] = "DIR";
        commands[3] = "TCP";
        commands[9] = "PORT";
        commands[4] = "LOCAL";
        commands[5] = "CD";
        commands[6] = "COPY";
        commands[7] = "DELETE";
        commands[8] = "clear";

    fgets(cmd, sizeof(cmd), stdin);
    cmd[strlen(cmd)-1]='\0';   // replace \n with \0
    splitStr(cmd, splitted);

    /*To use any of the methods, you must put in the comment the other methods that you do not want to use.*/

    built_in_methods(commands, cmd, splitted);
    // system_commands(commands, cmd, splitted);
    // fork_and_exec_commands(commands, cmd, splitted);
}

/*
    --------------------------------- Answers ---------------------------------

    Section 7 : The chdir command is a library function (system call) which is used to change the current directory

    Section 8 : "system" is SYSTEM function, because when we use it, the data we write inside
                this function command is written directly to the main shell.
    
    Section 10 : "COPY SRC DST" function uses the library function,
                because we use in "fread", "fwrite", "fclose".

    Section 11 : "DELETE" function is system function,
                because we use in "unlink".
    
*/

int main(){
    while(1){
        // printf("Yes master\n"); /* Section 1*/
        printDir();
        handle_cmd();
    }
    return 0;
}