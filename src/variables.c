/* Variable support
 * 
 * Author: Robert Rotaru
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "robslibs.h"

struct variable {
    char *name;
    char *value;
    int is_global;
};

static struct variable table[MAX_SIZE];

int store_var(char *name, char *val) {
    int i;
    char *newname, *newval;

    for (i = 0; i < MAX_SIZE && table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            newval = malloc(sizeof(char) * strlen(val));
            strcpy(newval,val);
            table[i].value = newval;
            return 0;
        }
    }
    if (i == MAX_SIZE) {
        fprintf(stderr, "Too many variables, exceeded max size: %d", MAX_SIZE);
        return 1;
    } else {
        newname = malloc(sizeof(char) * strlen(name));
        newval = malloc(sizeof(char) * strlen(val));
        strcpy(newname, name); strcpy(newval, val);
        table[i].name = newname;
        table[i].value = newval;
        return 0;
    }
}

char* get_var(char *name) {
    int i;
    char* returnvalue = malloc(sizeof(char) * MAX_SIZE);
    for (i = 0; i < MAX_SIZE && table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            strcpy(returnvalue, table[i].value);
            return returnvalue;
        }
    }
    return NULL;
}

int export_var(char *name) {
    int i;
    char *newname;

    for (i = 0; i < MAX_SIZE && table[i].name != NULL; i++) {
        if (strcmp(name, table[i].name) == 0) {
            table[i].is_global = 1;
            return 0;

        }
    }
    if (i == MAX_SIZE) {
        fprintf(stderr, "Too many variables, exceeded max size: %d", MAX_SIZE);
        return 1;
    } else {
        newname = malloc(sizeof(char) * strlen(name));
        strcpy(newname,name);
        table[i].name = newname;
        table[i].is_global = 1;
        return 0;
    }
}

void list_vars(void) {
    int i;
    for (i = 0; i < MAX_SIZE && table[i].name != NULL; i++) {
        if (table[i].is_global) {
            printf("  * %s=%s\n", table[i].name, table[i].value);
        } else {
            printf("    %s=%s\n", table[i].name, table[i].value);
        }
    }
}

void free_vars(void) {
    int i;
    for (i = 0; i < MAX_SIZE && table[i].name != NULL; i++) {
        free(table[i].name);
        free(table[i].value);
    }
}

