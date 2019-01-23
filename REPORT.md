**Phase 1-4**
For phases one through four, we decided to base off our shell skeleton on the
example provided in class. We did our parsing by tokenizing the input we
receive from the user when there is whitespace found. This allows our commands
to not be affected by multiple whitespace. We store a process into a struct and
save the command and following arguments. Before we start any of the piping and
redirection, we check to see if the command is an "exit", "cd," or "pwd"
command. If it is an exit command, we exit using exit with status zero. If
there is a "cd command" we perform this command by changing directories using
the chdir() call. If we receive the "pwd" command, we perform this command by
getting the current working directory using getcwd(). Once these commands are
performed, we fork the process and create a parent and child process. The
parent waits for the child process to be finished and then prints out the
completion statement.

**Phase 5-6**

**Phase 7**

**Phase 8**
