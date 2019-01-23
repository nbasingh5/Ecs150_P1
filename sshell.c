#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct UsersInput{
    char *input;
    char *arguments[16];
}UsersInput;

void RemoveWhiteSpace(UsersInput *temp) {
  char *buffer = temp->arguments[1];
  int i,count=0;
  for (size_t i = 0; buffer[i]; i++) {
    if (buffer[i] != ' ') {
      buffer[count] = buffer[i];
      count++;
    }
  }
  buffer[count] = '\0';
}

void SpaceTok(UsersInput *Tokinput, char* delim) {
  int count = 1;

  //printf("Funtion: %s\n", Tokinput->input);

  char *parsedInput = strtok(Tokinput->input, delim);
  Tokinput->arguments[0] = parsedInput;

  //store all arguments in cmd struct
  while (parsedInput != NULL) {
    if (count < 16) {
      //printf("parsedInput:%s\n",parsedInput );
      parsedInput = strtok(NULL, delim);
      Tokinput->arguments[count] = parsedInput;
      count++;
    }
  }
}


void redirection(UsersInput *redirect, char *direction) {
  char delim[] = " ";
  int FileCheck = 0;
  SpaceTok(redirect,direction);
  struct UsersInput Commands;
  Commands.input = (char *) malloc(1 + strlen(redirect->arguments[0]));
  strcpy(Commands.input,redirect->arguments[0]);
  SpaceTok(&Commands, delim);
  RemoveWhiteSpace(redirect);

  if (strcmp(direction, "<") == 0) {
    FileCheck = open(redirect->arguments[1], O_RDONLY, 0644);
  }
  else if (strcmp(direction, ">") == 0) {
    FileCheck = open(redirect->arguments[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
  }
  if(FileCheck < 0){
    perror("Error");
  }
  if (strcmp(direction, "<") == 0) {
    dup2(FileCheck, 0);
  }
  else if (strcmp(direction, ">") == 0) {
    dup2(FileCheck, 1);
  }

  close(FileCheck);
  //char *args[] = {"grep","toto", NULL };
  execvp(Commands.arguments[0], Commands.arguments);
  perror("execvp error");
}

int main(int argc, char *argv[])
{
  struct UsersInput entered;
  struct UsersInput IRstruct;
  size_t bufsize = 32;
  int status;
  pid_t pid;
  char delim[] = " ";
  char IRdelim[] = "<";
  char ORdelim[] = ">";
  char *inputCpy,*IRtok;
  int bul = 0;

  while (1) {
    bul = 0;
    entered.input = (char *)malloc(bufsize * sizeof(char));
    entered.input = NULL;
    printf("sshell$ ");
    getline(&entered.input,&bufsize,stdin);
    if (!isatty(STDIN_FILENO)) {
        printf("%s", entered.input);
        fflush(stdout);
    }
    // for (int i = 0; i < strlen(entered.input); i++)
    // {
    //   if ( entered.input[i] == '\n')
    //   {
    //     //entered.input[i] = ' ';
    //     printf("Nothiing:[%c]\n",entered.input[i]);
    //   }
    // }
    if (entered.input[0] == '\n') {
      continue;
    }
    else{
      char *spot;
      if ((spot=strchr(entered.input, '\n')) != NULL)
        *spot = '\0';
    }

    //allocate space for a copy userInput
    inputCpy = (char *) malloc(1 + strlen(entered.input));
    IRstruct.input = (char *) malloc(1 + strlen(entered.input));
    //copy userInput in 'inputCpy'
    strcpy(inputCpy,entered.input);
    //printf("inputCpy: %s\n",inputCpy);
    strcpy(IRstruct.input,entered.input);
    SpaceTok(&entered, delim);

    // int i = 0;
    // while (entered.arguments[i] != NULL) {
    //   if (i < sizeof(entered.arguments))
    //       printf("Parts: %s\n", entered.arguments[i]);
    //       i++;
    // }

    //check to see if command is 'cd'
    if (strcmp("cd",entered.arguments[0]) == 0){
      chdir(entered.arguments[1]);
      bul = 1;
      fprintf(stderr, "+ completed '%s' [%d]\n",inputCpy,WEXITSTATUS(status));
    }
    //check to see if command is 'exit'
    if (strcmp("exit",entered.arguments[0]) == 0){
      fprintf(stderr, "Bye...\n");
      exit(0);
    }
    //-------------------shell skeleton-------------------
    //fork a process (create parent and child)
    pid = fork();
    //parent
    if (pid > 0) {
      waitpid(-1, &status, 0);
      fprintf(stderr, "+ completed '%s' [%d]\n",inputCpy,WEXITSTATUS(status));
    }
    //child
    else if (pid == 0) {
      if (strcmp(entered.input,"\n") == 0 || bul == 1) {
          continue;
      }
      else{
        if (strstr(inputCpy, "<") != NULL) {/////////////////////////////////////////////////////////////////
          redirection(&IRstruct,IRdelim);

        }
        else
        if (strstr(inputCpy, ">") != NULL) {
          redirection(&IRstruct,ORdelim);
        }
        else{
        execvp(entered.arguments[0],entered.arguments);
        perror("execvp");
        }
      }
    }
    //fork failed
    else
    {
      printf("Fork Failed\n");
      exit(1);
    }
  }
}
