#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128
#define MAX_PATH 4096

//help: geeksforgeeks.org/making-linux-shell-c/ and youtube.com/watch?v=z4LEuxMGGs8


char prompt[] = " > ";
char delimiters[] = " \t\r\n";
char cwd[MAX_PATH];
char *dir_ptr;
bool background = false;
extern char **environ;

void exitProg(int sig){

  printf("Control C is invalid\n");
  fflush(stdout);
}

char **toParse(char* input_cmd){

  char **new_cmd = malloc(8 * sizeof(char *));
  char *this_arg;
  char *that_arg;
  char *space_here = " ";
  int i = 0;

  this_arg = strtok(input_cmd, space_here);

  while (this_arg != NULL){
    new_cmd[i] = this_arg;
    that_arg = new_cmd[i];

    if (strchr(that_arg, '$') != NULL){
      memmove(that_arg, that_arg+1, strlen(that_arg));
      new_cmd[i] = getenv(that_arg);
    }
    i++;
    this_arg = strtok(NULL, space_here);
  }
  if (strcmp(new_cmd[i-1], "&") == 0){

    background = true;
  }

  new_cmd[i] = NULL;
  return new_cmd;
}

static void run_getenv(const char* name){
  char* value;
  value = getenv(name);
  if(!value){
    printf("'%s' isn't set\n", name);
  }
  else{
    printf("%s = %s\n", name, value);
  }
}

int *status; // this is for the parent process


int main() {
  
  // Stores the string typed into the command line.
  char command_line[MAX_COMMAND_LINE_LEN];
  char cmd_bak[MAX_COMMAND_LINE_LEN];
  char *input_ptr = input_cmd;
  
  // Stores the tokenized command line input.
  char *arguments[MAX_COMMAND_LINE_ARGS];
  char **command;

  while (true) {
    
    do{ 
      signal(SIGINT, exit_program);
      background = false;

      // Print the shell prompt.
      dir_ptr = getcwd(cwd, sizeof(cwd));
      printf("%s%s", dir_ptr, prompt);
      fflush(stdout);

      // Read input from stdin and store it in command_line. If there's an
      // error, exit immediately. (If you want to learn more about this line,
      // you can Google "man fgets")
      
      if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
        fprintf(stderr, "fgets error");
        exit(0);
      }

    input_ptr = strsep(&input_ptr, "\n");
    command = toParse(input_ptr);

    if(strcmp(command[0], "exit") == 0){
      exit(0);
    }
    else if(strcmp(command[0], "pwd") == 0){
      dir_ptr = getcwd
    }



      
    }while(command_line[0] == 0x0A);  // while just ENTER pressed
    
    // If the user input was EOF (ctrl+d), exit the shell.
    if (feof(stdin)) {
      printf("\n");
      fflush(stdout);
      fflush(stderr);
      return 0;
    }
    // TODO:
    // 

    // 0. Modify the prompt to print the current working directory
			  
			
    // 1. Tokenize the command line input (split it on whitespace)
      
    // 2. Implement Built-In Commands
 
    // 3. Create a child process which will execute the command line input
  
    // 4. The parent process should wait for the child to complete unless its a background process

      
  // Hints (put these into Google):
  // man fork
  // man execvp
  // man wait
  // man strtok
  // man environ
  // man signals
        
  // Extra Credit
  // man dup2
  // man open
  // man pipes
  }
  // This should never be reached.
}