#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <fcntl.h>

struct cmdByuser
{
    char *FirstCmd;
    char *arguments[16];
};
struct InuputR {
    char *left;
    char *right;
};

int main(int argc, char *argv[])
{
  char *userInput;
  size_t bufsize = 32;
  int status;
  pid_t pid;
  char delim[] = "<";
  char IRdelim[] = "<";
  int count = 1;
  char *SaveInput,*IRtok;
  char *cdCall;
  int bul = 0;

while (1) {
  userInput = (char *)malloc(bufsize * sizeof(char));
  // if( userInput == NULL)delim
  // {
  //   perror("Unable to allocate buffer");
  //   exit(1);
  // }
    printf("sshell$ ");
    //get command from user
    getline(&userInput,&bufsize,stdin);
    //printf("userInput: [%s]\n",userInput );
    if( userInput == "\n" || userInput == "\r" || userInput == "")
    {
      perror("Unable to allocate buffer");
      exit(1);
    }

    //allocate space tfirst.arguments[count]o copy userInput
    SaveInput = (char *) malloc(1 + strlen(userInput));
    IRtok = (char *) malloc(1 + strlen(userInput));
    //do not save "return keystruc"
    for (int i = 0; i < strlen(userInput); i++)
    {
      if ( userInput[i] == '\n' || userInput[i] == '\r' )
        userInput[i] = '\0';
    }
    //save a copy of userInput in 'SaveInput'
    strcpy(SaveInput,userInput);
    strcpy(IRtok,userInput);
    //create a struct used to save commands
    struct cmdByuser first;
    struct InuputR sample;

    //--------------------------------------------------------------------------------------------------
    char* IRInput = strtok(IRtok, IRdelim);
    sample.left = IRInput;
    while (IRInput != NULL) {
      if (count < 2) {
        printf("IRInput Left:%s\n",IRInput);
        IRInput = strtok(NULL, delim);
        printf("IRInput Right:%s\n",IRInput);
        sample.right = IRInput;
        count++;
      }
      count = 1;
    }
    int IRfile = open(sample.right,O_RDONLY);
    char buf[256] = "";
    read(IRfile, buf, sizeof(buf));
    printf("Buff:");
    for (size_t z = 0; z < sizeof(buf); z++) {
      printf("1%c", buf[z]);
      /* code */
    }

    //--------------------------------------------------------------------------------------------------
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
        printf("Firstinput:%s\n",Firstinput );
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
      if (userInput == "") {
          printf("userInput: [%s]\n",userInput );
      }
      else{
        execvp(first.FirstCmd,first.arguments);
        perror("execvp");
      }
    }
    else
    {
      printf("Fork Failed\n");
      exit(1);
    }
    count = 1;
  }
}
