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
For phases five and six, we implemented the redirection functionalities by checking what type of redirection command was trying to be performed. Depending on the type of redirection, it would then go through a function to open and close the necessary ports using dup2().

**Phase 7**
For phase seven, we implemented our piping commands by keeping track of the commands needed for the processes, the current process we are on, and the number of pipes that need to occur. Once we have all the information, we use a recursive do_pipe() function. We built our function so that if we are in the last process, we check to see if there is a redirection command needed to be performed if not then we execute the last process. If we are in any of the other pipe phases, we pipe and fork, creating parent and child processes. If we are in the parent process, we open and close the appropriate file descriptors and check if once again if there is a redirection, if not then executes the appropriate command. If we are in the child process, we open and close the needed file descriptors and recursively call on this function again.


**Phase 8**
