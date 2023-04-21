//Traae Bloxham
//Michael McGregor
//CS1337
//4/16/2020

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define TRUE 1

// prototype of functions
void pwdCommand();
void lsCommand(char* dirName);
void catCommand(char* fileName);

struct Tokens {
	int num_tokens;
	char **tokens;   // double pointer because array of strings? yeah that sounds right.
};

void execute(struct Tokens tokens) {
  // Get command. Arguments are in tokens.tokens[1...]
   char* cmd = tokens.tokens[0];
  
  // TODO: handle shell commands
  
  // CD
  if (strcmp(cmd, "cd") == 0) {
    char *newPath; 
    if (tokens.num_tokens == 1) { newPath = getenv("HOME");} // use the home path if no param
    else { newPath  = tokens.tokens[1];}                      // use param 2
    chdir(newPath);
  } 
  
  // PWD 
  else if (strcmp(cmd, "pwd") == 0) {
    printf("Working Directory: ");
    pwdCommand();     // go to func that does the work
    printf("\n");
  } 
  
  // cat 
  else if (strcmp(cmd, "cat") == 0) {
    char* fileName = tokens.tokens[1]; // grab the file name
    catCommand(fileName);              // pass it to cat
  } 
  
  // ls
  else if (strcmp(cmd, "ls") == 0) {
    if (tokens.num_tokens > 1) {          // get the path
       char *dirName = tokens.tokens[1];
       lsCommand(dirName);
    }
    else {                              // no path, use current directory
      char dirName[1000];
      getcwd(dirName, 1000);
      lsCommand(dirName);
    }
} 
  
  // exit
  else if (strcmp(cmd, "exit") == 0) { 
    if (tokens.num_tokens > 1){
      char *status = tokens.tokens[1];
      int statCode = atoi(status);
      exit(statCode);
    }
    else { exit(0); }
  } 
  
  // retry
  else { printf("Unknown command\n"); }
  
  free(tokens.tokens);
}

int main() {
  // Shell loop. Press ctrl+c to exit shell.
  while (TRUE) {
    // call my pwdCommand to pimp my PS1 var
    pwdCommand();
    printf("> ");
    struct Tokens tokens;
    
    // Get input
    char* line = NULL;
    size_t n = 0;
    getline(&line, &n, stdin);
    
    // establish counting variable to tokenization
    int token_count = 1;
    char* strptr = line;  // string pointer
    
    // count the tokens
    while (*strptr != '\0') {
      if (*strptr == ' ') {token_count++;}
      if (*strptr == '\n') {*strptr = '\0';}
      strptr++;
    }
    
    //set the struct variables
    tokens.num_tokens = token_count;
    tokens.tokens = malloc(token_count * sizeof(char*));
    tokens.tokens[0] = strtok(line, " ");
    
    // do... something.
    for (int i = 1; i < token_count; i++) {
      tokens.tokens[i] = strtok(NULL, " ");
    }
    

    execute(tokens);
  }
  return 0;
}


void pwdCommand(){ 
  char currentDir[1000];   // make a buffer var. need a way to solve the size problem. ?PATH_MAX?  
  getcwd(currentDir, 1000); // returns string on buff max of size provided
  printf("%s", currentDir); // print the thing 
}

void catCommand(char* fileName){           
  int toRead = open(fileName, O_RDONLY);  // grad the file descriptor, read only
  char buffer[1000];                      // creat my buff
  int bufCheck;                                 
  do{
    bufCheck = read(toRead, buffer, 100);   // read and print until
    printf("%s", buffer);
    
  }while (bufCheck != 0);                 // until nothing returns
    close(toRead);
}

void lsCommand(char *dirName){
  DIR *dirPTR = opendir(dirName);
  
  char *fileName = readdir(dirPTR)->d_name;  // grab the file names
  do{
    printf("%s \n", fileName);           // print and repeat
    fileName = readdir(dirPTR)->d_name;
  }while (readdir(dirPTR) != NULL);  
  
  closedir(dirPTR);
}
