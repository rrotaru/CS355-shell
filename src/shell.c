/** shell.c - The main file for running the CS355 Shell Project
*   
*   Authors: Bryan, Robert, Joe
*
*   Creates and runs a shell with the following attributes:
*       1.) Runs executables - including standard commands and existing user programs.
*       2.) Keyboard Signals - Passes signals to children processes
*       3.) Batch Scripts -
*           a.) Script stored in plain text
*           b.) Each line a single command with/without parameters
*           c.) Each line may contain several commands separated by a semicolan
*           d.) Commands executed one by one until end of file
*           e.) Lines starting with # are ignored
*       4.) Control Structures -
*           a.) Supports if/then/fi
*           b.) Supports if/then/else/fi
*       5.) Support cd built-in command
*       6.) Support pwd built-in command
*       7.) Local variables -
*           a.) Assign: var = value
*           b.) Reference: $var
*           c.) Delete: unset var;
*           d.) stdin input: read var;
*           e.) List variables: set;
*           f.) Make global: export var
*       8.) Redirection - For stdin, stdout, stderr, and between built in commands
*           a.) <, >, <<, and >>
*       9.) Channeling (pipes) - Between build in commands
*       10.) Exit command terminates
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "functions.h"
#include "robslibs.h"

#define MAX_SIZE    1024

int main(int ac, char *av[], char **envp) {
    signal(SIGINT, SIG_IGN);
    int shell_execute = 1, return_val, i;
    char user_input[MAX_SIZE];

    /* Arguments passed to the shell are treated/executed as batch
     * script files, then the shell exits */
    if (ac > 1) {
        /* run batch script */
        for (i = 1; i < ac; i++) {
            batch_execute(av[i]);
        }
    } else {

        init_msg();

        /* If no arguments, run interactively */
        while(shell_execute) {
            print_shell_prompt();       
            
            get_user_input(user_input, sizeof(user_input));

            //Parse and check input for existing program in PATH
            //TODO: Also check for existing program in project/bin/ directory (lab programs)
            char *spaced_input[MAX_SIZE];
            parse_user_input(user_input, spaced_input, " ");

            if( strcmp(user_input, "exit") == 0)
            {
                shell_execute = 0;
            }
            else if( strcmp(spaced_input[0], "cd") == 0)
            {
                chdir(spaced_input[1]);
            }
            else
            {
                // Why do we want to ignore signals here???
                //ignore_signals();
                return_val = process(spaced_input);
                //reset_signals();
            }

        }
    }
    
    return EXIT_SUCCESS;
}
