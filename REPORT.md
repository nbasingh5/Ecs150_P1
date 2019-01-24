# Shell Script Markdown
## Phases 1-4
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

## Phases 5-6
For phases five and six, we implemented the redirection functionalities by
checking what type of redirection command was trying to be performed. Depending
on the type of redirection, it would then go through a function to open and
close the necessary ports using dup2(). We check the type of redirection by
using the function strstr() on the command and the redirection symbols. If
there is a pointer pointing to the char matching the symbol, then we perform the
correct redirection procedures. After tokenizing based on the symbol (< or >), 
we tokenized with space to seperate each command and argument and saved the 
values in a seperate array. We are then able to use that array to implement 
execvp. The input redirection is implemented by opening a file and using the 
information from the file as input for the execvp command using dup2(). The 
output redirection is implemented by opening the file and writting the result 
of execvp into the file. If the file does not exist, a new one is created.

## Phase 7
For phase seven, we implemented our piping commands by keeping track of the
commands needed for the processes, the current process we are on, and the
number of pipes that need to occur. Once we have all the information, a while 
loop is run for the amount of process that are being piped. We built our 
function so that if we are in the last process, we check to see if there is a 
redirection command needed to be performed if not then we execute the last 
process. If we are in any of the other pipe phases, we pipe and fork, creating 
parent and child processes. If we are in the parent process, we open and close 
the appropriate file descriptors and check if once again if there is a 
redirection, if not then the program executes the appropriate command. If we 
are in the child process, we open and close the needed file descriptors and 
recursively call on this function again.

## Phase 8
We did not get to finish. :(

## Testing
For our project, we tested our different phases by using the examples provided
in the project document and then using examples we came up with on our own. For
more official testing, we used the tester that was provided by our professor
and made sure it ran those tests.We also allowed other students in ECS 150 to 
see if they were able to break our code and fixed errors as they came along. 

## Sources
We used a couple of sources when implementing our code. We used a lot of
concepts mentioned in class and the slides our professor provided. For more
specific problems, we used sources such as StackOverflow and TutorialsPoint for
questions regarding the C language and syntax. When it came to simple functions 
such as getting rid of white space we found a program on github and 
StackOverflow that helped us. We also got help from one of our tutors Brenden 
in regards to phase 7.
