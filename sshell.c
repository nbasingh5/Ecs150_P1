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
	char *args[] = { cmd, "-u", NULL };
	int status;
	pid_t pid;

	pid = fork();
	if (pid > 0) {
		waitpid(-1, &status, 0);
		fprintf(stderr, "+ completed '/bin/date -u' [%d]\n", WEXITSTATUS(status));
	}
	else if (pid == 0) {
		userInput = (char *)malloc(bufsize * sizeof(char));
		if( userInput == NULL)
		 {
				 perror("Unable to allocate buffer");
				 exit(1);
		 }
		printf("sshell$ ");
		characters = getline(&userInput,&bufsize,stdin);

		char *combinedCmd = (char *) malloc(1 + strlen(cmd)+ strlen(userInput) );
		strcpy(combinedCmd,cmd);
		strcat(combinedCmd,userInput);

		printf("Line:, %s", combinedCmd);
		execv(cmd,args);
		perror("execve");
	}




}
