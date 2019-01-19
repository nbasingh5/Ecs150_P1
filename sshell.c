#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct cmdByuser {
    char *FirstCmd;
    char *arguments[16];
};

int main(int argc, char *argv[])
{
  char *userInput;
  size_t bufsize = 32;
  int status;
  pid_t pid;
  char delim[] = " ";
  int count = 1;
  char *SaveInput;
  char *cdCall;

while (1) {
  userInput = (char *)malloc(bufsize * sizeof(char));
  if( userInput == NULL)
  {
    perror("Unable to allocate buffer");
    exit(1);
  }
    printf("sshell$ ");
    //get command from user
    getline(&userInput,&bufsize,stdin);
    //allocate space to copy userInput
    SaveInput = (char *) malloc(1 + strlen(userInput));
    //do not save "return key"
    for (int i = 0; i < strlen(userInput); i++)
    {
      if ( userInput[i] == '\n' || userInput[i] == '\r' )
        userInput[i] = '\0';
    }
    //save a copy of userInput in 'SaveInput'
    strcpy(SaveInput,userInput);
    //create a struct used to save commands
    struct cmdByuser first;
    //tokenize input and save in string
    char *Firstinput = strtok(userInput, delim);
    //check to see if command is 'cd'
    if (strcmp("cd",Firstinput) == 0){
      Firstinput = strtok(NULL, delim);
      cdCall = (char *) malloc(1 + strlen(Firstinput));
      cdCall = Firstinput;
      chdir(cdCall);
      Firstinput = "";
    }
    //else can be any other command
    else{
    first.FirstCmd = Firstinput;
    //check to see if command is 'exit'
    if (strcmp("exit",first.FirstCmd) == 0){
      printf("Bye...\n");
      exit(0);
    }
    first.arguments[0] = first.FirstCmd;
    //store arguemtns in cmd struct
    while (Firstinput != NULL) {
      if (count < 16) {
        Firstinput = strtok(NULL, delim);
        first.arguments[count] = Firstinput;
        count++;
      }
    }
  }

    //shell skeleton
    pid = fork();
    if (pid > 0) {
      waitpid(-1, &status, 0);
      fprintf(stderr, "+ completed '%s' [%d]\n",SaveInput,WEXITSTATUS(status));
    }
    else if (pid == 0) {
      execvp(first.FirstCmd,first.arguments);
      perror("execvp");
    }
    else
    {
      printf("Fork Failed\n");
      exit(1);
    }
    count = 1;
  }
}
