/* Functions implementation file
*	Author: Bryan Bigelow
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>

void print_shell_prompt()
{
	char wrk[1024];
	printf("%s@%s:%s $ ", "nova", "ubuntu", getcwd(wrk, sizeof(wrk)));

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
