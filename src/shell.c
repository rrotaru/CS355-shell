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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "functions.h"
#include "batch.h"

int main(int ac, char *av[]) {
	signal(SIGINT, SIG_IGN);
	int shell_execute = 1, i;
	char user_input[200];

    /* Arguments passed to the shell are treated/executed as batch
     * script files, then the shell exits */
    if (ac > 1) {
        /* run batch script */
        for (i = 2; i < ac; i++) {
            batch_execute(av[i]);
        }
    } else {

        /* If no arguments, run interactively */
        while(shell_execute) {
            print_shell_prompt();		
            
            get_user_input(user_input, sizeof(user_input));

            if( strcmp(user_input, "exit") == 0) {
                shell_execute = 0;
            }

            printf("%s\n", user_input);
        }
    }
	
	return EXIT_SUCCESS;
}
