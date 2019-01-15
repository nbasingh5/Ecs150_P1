#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
 #include <sys/wait.h>
 #include <unistd.h>

int main(int argc, char *argv[])
{
	char *cmd = "/bin/date";
	char *args[] = { cmd, "-u", NULL };
	int status;

	pid_t pid;
	pid = fork();
	if (pid > 0) {
		waitpid(-1, &status, 0);
		printf("+ completed '/bin/date -u' [%d]\n", WEXITSTATUS(status));
	}
	else if (pid == 0) {
		execv(cmd,args);
		perror("execve");
	}
}
