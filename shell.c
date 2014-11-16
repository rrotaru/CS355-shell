/**	shell.c - The main file for running the CS355 Shell Project
*	
*	Authors: Bryan, Robert, Joe
*
*	Creates and runs a shell with the following attributes:
*		1.) Runs executables - including standard commands and existing user programs.
*		2.) Keyboard Signals - Passes signals to children processes
*		3.) Batch Scripts -
*			a.) Script stored in plain text
*			b.) Each line a single command with/without parameters
*			c.) Each line may contain several commands separated by a semicolan
*			d.) Commands executed one by one until end of file
*			e.) Lines starting with # are ignored
*		4.) Control Structures -
*			a.) Supports if/then/fi
*			b.) Supports if/then/else/fi
*		5.) Support cd built-in command
*		6.) Support pwd built-in command
*		7.) Local variables -
*			a.) Assign: var = value
*			b.) Reference: $var
*			c.) Delete: unset var;
*			d.) stdin input: read var;
*			e.) List variables: set;
*			f.) Make global: export var
*		8.) Redirection - For stdin, stdout, stderr, and between built in commands
*			a.) <, >, <<, and >>
*		9.) Channeling (pipes) - Between build in commands
*		10.) Exit command terminates
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

int main(int ac, char *av[])
{
	int shell_execute = 1;
	char user_input[200];

	while(shell_execute)
	{
		print_shell_prompt();		
		
		get_user_input(user_input, sizeof(user_input));

		if( strcmp(user_input, "exit") == 0)
		{
			shell_execute = 0;
		}

		printf("%s\n", user_input);
	}
	
	return 0;
}
