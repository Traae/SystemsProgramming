#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define TRUE 1

struct Tokens {
	int num_tokens;
	char **tokens;
};

void execute(struct Tokens tokens) {
  // Get command. Arguments are in tokens.tokens[1...]
  char* cmd = tokens.tokens[0];

  // TODO: handle shell commands
  if (strcmp(cmd, "cd") == 0) {
    printf("cd\n");
  } else if (strcmp(cmd, "pwd") == 0) {
    printf("pwd\n");
  } else if (strcmp(cmd, "cat") == 0) {
    printf("cat\n");
  } else if (strcmp(cmd, "ls") == 0) {
    printf("ls\n");
  } else if (strcmp(cmd, "exit") == 0) {
    printf("exit\n");
  } else {
    printf("Unknown command\n");
  }
  
  // All done, free heap memory
  free(tokens.tokens);
}

void main() {
  // Shell loop. Press ctrl+c to exit shell.
  while (TRUE) {
    printf("> ");
    struct Tokens tokens;
    // Get input
    char* line = NULL;
    size_t n = 0;
    getline(&line, &n, stdin);

    int token_count = 1;
    char* strptr = line;
    while (*strptr != '\0') {
	if (*strptr == ' ')
	    token_count++;
	if (*strptr == '\n')
	    *strptr = '\0';
	strptr++;
    }
    tokens.num_tokens = token_count;
    tokens.tokens = malloc(token_count * sizeof(char*));
    tokens.tokens[0] = strtok(line, " ");
    for (int i = 1; i < token_count; i++) {
	tokens.tokens[i] = strtok(NULL, " ");
    }
    // Handle the command 
    execute(tokens);
  }
}
