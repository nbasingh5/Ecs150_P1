#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char *cmd = "/bin/";
  char *userInput;
  size_t bufsize = 32;
  size_t characters;
  int status;
  pid_t pid;
  char *combinedCmd;

while (1) {
  userInput = (char *)malloc(bufsize * sizeof(char));
  if( userInput == NULL)
  {
    perror("Unable to allocate buffer");
    exit(1);
  }
    printf("sshell$ ");
    characters = getline(&userInput,&bufsize,stdin);

    //concatenate userInput and cmd
    for (int i = 0; i < strlen(userInput); i++)
    {
      if ( userInput[i] == '\n' || userInput[i] == '\r' )
        userInput[i] = '\0';
    }
    combinedCmd = (char *) malloc(1 + strlen(cmd)+ strlen(userInput) );
    strcpy(combinedCmd,cmd);
    strcat(combinedCmd,userInput);
    char *args[] = {combinedCmd, "-u", NULL };

    //shell skeleton
    pid = fork();
    if (pid > 0) {
      waitpid(-1, &status, 0);
      fprintf(stderr, "+ completed '/bin/date -u' [%d]\n", WEXITSTATUS(status));
    }
    else if (pid == 0) {
      execvp(combinedCmd,args);
      perror("execvp");
    }
  }
}
