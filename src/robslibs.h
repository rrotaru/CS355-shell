/* Author: Robert Rotaru 
 *
 *
 */
#define execute(args) fork_existing_program(args)
#define MAX_SIZE 1024

/* batch.c 
 *
 */

/* Reads a file into a buffer and returns the number of characters read
 * REMEMBER to free() buffer after finishing! */
long file_read(char* filename, char** buffer);

/* trims a command to remove leading/ending whitespace*/
size_t trimwhitespace(char *out, size_t len, const char *str);

/* Runs commands from a string (delimited by newlines and semicolons */
void batch_execute(char* str);

/* control.c 
 *
 */

int process(char **args);
int is_control(char *s);
int do_control(char **args);
int is_ok(void);
int syntax_error(char* msg);

/* init.c 
 *
 */

int init_msg(void);

/* internals.c 
 *
 */

int internal(char **args, int *returnval);
int cleanup(void);

/* variables.c
 *
 */

int store_var(char *name, char *val);
char* get_var(char *name);
int export_var(char *name);
void list_vars(void);
void free_vars(void);
