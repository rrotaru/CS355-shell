/* Internal command execution support
 * 
 * Author: Robert Rotaru
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "functions.h"
#include "robslibs.h"

int internal(char **args, int *returnptr) {
    int returnval = 0;

    if (strcmp(args[0], "exit") == 0) {
        returnval = cleanup();
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        returnval = 1;
        *returnptr = chdir(args[1]);
    } else if (strcmp(args[0], "set") == 0) {
        list_vars();
        returnval = 1;
        *returnptr = 0;
    } else if (strcmp(args[0], "unset") == 0) {
        if (args[1] != NULL) {
            *returnptr = store_var(args[1], "");
            if (*returnptr != 1) {
                returnval = 1;
            }
        }
    } else if (strchr(args[0], '=') != NULL) {
        char *name = strtok(args[0], "="), *value = strtok(NULL, "=");
        //TODO: Check if name is legal variable (e.g. first char is not a digit, etc.
        *returnptr = store_var(name, value);
        if (*returnptr != 1) {
            returnval = 1;
        }
    } else if (strcmp(args[0], "export") == 0) {
        if (args[1] != NULL /*TODO: check if name is legal as above */) {
            *returnptr = export_var(args[1]);
        } else {
            *returnptr = 1;
        }
        returnval = 1;
    } else if (strcmp(args[0], "read") == 0) {
        if (args[1] != NULL) {
            char* var = get_var(args[1]);
            printf("%s\n", var);
            free(var);
            *returnptr = 0;
        } else {
            *returnptr = 1;
        }
        returnval = 1;
    }
    return returnval;
    free(args[0]);
}

int cleanup(void) {
    
    // free allocated environment variables
    free_vars();
    return 1;
}
