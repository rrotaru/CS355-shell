/* Functions implementation file
*	Author: Bryan Bigelow
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void print_shell_prompt()
{
	char wrk[1024];
	char host[1024];
	gethostname(host, sizeof(host));
	getcwd(wrk, sizeof(wrk));
	printf("%s@%s:%s $ ", "nova", host, wrk);

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
	char *token;
        token = strtok(s, delim);

	int k = 0;

	while( token != NULL )
	{
		spaced[k] = token;
		k = k + 1;
		token = strtok(NULL, delim);
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
