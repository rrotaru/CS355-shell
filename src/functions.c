/* Functions implementation file
*	Author: Bryan Bigelow
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <libgen.h>
#include "robslibs.h"

void print_shell_prompt()
{
	char absolute_path[1024], host[1024], *dir, *user;
    user = getenv("USER");
	gethostname(host, sizeof(host));
	getcwd(absolute_path, sizeof(absolute_path));
    dir = basename(absolute_path);
	printf("%s@%s %s/ $", user, host, dir);

	return;
}

void get_user_input(char s[], int size)
{
	fgets(s, size, stdin);

	//Strip newline from fgets
	int trim_loc = strlen(s) - 1;
	if(s[trim_loc] == '\n')
	{
		s[trim_loc] = '\0';
	}

	return;
}

void parse_user_input(char s[], char *spaced[], char *delim)
{
	char *token, *tokenptr;
    token = strtok_r(s, delim, &tokenptr);

	int k = 0;

	while( token != NULL )
	{
        char* quoteptr;
        // If it is a quoted string, keep it as one long token
        if ((quoteptr = strchr(token, '"')) != NULL) {
            char *str = malloc(sizeof(char) * MAX_SIZE);
            strcat(str, token);
            token = strtok_r(NULL, delim, &tokenptr);
            while (token[strlen(token)-1] != '"') {
                strcat(str, " ");
                strcat(str, token);
                token = strtok_r(NULL, delim, &tokenptr);
            }
            strcat(str, " ");
            strcat(str,token);
            quoteptr = strchr(str, '"');
            while(*quoteptr != '\0') {
                *quoteptr = *(quoteptr+1);
                quoteptr++;
            }
            str[strlen(str)-1] = '\0';
            spaced[k] = str;
            k++;
        }
        // If it is a variable, expand it
        else if (token[0] == '$') {
            char* expanded, *expandedptr;
            expanded = get_var(token+1);
            token = strtok_r(expanded, delim, &expandedptr);
            while (token != NULL) {
                spaced[k] = token;
                k++;
                token = strtok_r(NULL, delim, &expandedptr);
            }
            free(expanded);
        // Otherwise just eat it like the other tokens 
        } else {
		    spaced[k] = token;
            k++;
        }
		token = strtok_r(NULL, delim, &tokenptr);
	}
	
	spaced[k] = NULL;

}

int fork_existing_program(char *av[])
{
	pid_t child_pid;
        int child;
        child_pid = fork();

        if(child_pid == 0)
        {
                //Child
		signal(SIGINT, SIG_DFL);
                execvp(av[0], av);
                exit(1);
        }
        else
        { 
                wait(&child);
                if(child == 0)
                {
                        return 0;
                }
                else
                {
                        return -1;
                }
                exit(0);
        }
}

void ignore_signals()
{
	signal(1, SIG_IGN);
	signal(3, SIG_IGN);
	signal(6, SIG_IGN);
	signal(8, SIG_IGN);
	signal(11, SIG_IGN);
	signal(13, SIG_IGN);
	signal(14, SIG_IGN);
	signal(15, SIG_IGN);	
}

void reset_signals()
{
	signal(1, SIG_DFL);
	signal(3, SIG_DFL);
	signal(6, SIG_DFL);
	signal(8, SIG_DFL);
	signal(11, SIG_DFL);
	signal(13, SIG_DFL);
	signal(14, SIG_DFL);
	signal(15, SIG_DFL);
}
