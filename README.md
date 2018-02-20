# RShell
#Authors 
Neel Sethia and Brandon Lee.

#Contents
RShell is a replication of a terminal or command shell. 
It will prompt the user and read commands on a single line
being linked by connectors (&&, ||, ;). The commands that
RShell will execute are the common commands found 
in any general-use terminal (ex: cd, echo, ls,). 
Further implementation allows the user to use the test
functionality as well as parentheses for hierarchical 
inputs into the terminal. The test command makes available input
flags such as -e, -d, and -f. 

#Bugs

When using the semicolon connect (";"), there is an issue with using the test command properly on the right-hand side. 
  - Response is either a segmentation fault or general error message from within the program
  
When entering longer commands, the precedence tests will sometimes work in an incorrect order when using the "test" command.
  - Reponse is incorrect ordering of the commands entered
  
Sometimes, the user information on the left-hand side of the terminal disappears after any basic command
  - Doesn't happen often but still comes up in very rare and specific instances.
  
A segmentation fault will sometimes occur if multiple "test" commands are entered in a single line. 

If the user enters "cd PATH", the command will execute properly - however, an error message will still appear stating "No such file or directory", even if the directory/file exists. Also a OUTOFRANGE error is thrown but the program still executes fine and there is no effect on functionality.

If the user enters "cd -", the command will execute properly - however, an error message will still appear regarding OLDPWD not being set. Also an OUTOFRANGE error is thrown but the program still executes fine and there is no effect on functionality.

When using connectors, "cd PATH" will sometimes not execute properly with other commands such as ls. 
