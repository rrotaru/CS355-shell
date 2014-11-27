/* Functions header file
*	Author: Bryan Bigelow
*/

//Prints the shell command of style "[shell]@[system]:[directory] $ "
//TODO: Get system
void print_shell_prompt();

//Gets string of userinput for parsing
//TODO: Move input size to defined constant
void get_user_input(char s[], int size);

//Copies user input into list of strings based on delimiter
void parse_user_input(char s[], char *spaced[], char *delim);

//Forks a program and its arguments to execvp in a child process. Returns -1 if unsuccessful. 
int fork_existing_program(char *av[]);
