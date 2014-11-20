/* Functions header file
*	Author: Bryan Bigelow
*/

//Prints the shell command of style "[shell]@[system]:[directory] $ "
//TODO: Get system
void print_shell_prompt();

//Gets string of userinput for parsing
//TODO: Move input size to defined constant
void get_user_input(char s[], int size);
