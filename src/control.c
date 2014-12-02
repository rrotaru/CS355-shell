/* Control structure support
 * 
 * Author: Robert Rotaru
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robslibs.h"
#include "functions.h"

enum states { ENTER_IF, WANT_THEN, THEN_BLOCK, ELSE_BLOCK };
enum results { SUCCESS, FAIL };
static int if_state = ENTER_IF;
static int if_result = SUCCESS;
static int result;

int process(char **args) {
    int return_val = 0;
    
    if (args[0] == NULL) {
        return_val = 0;
    } else if (is_control(args[0])) {
        return_val = do_control(args);
    } else if (is_ok()) {
        return_val = execute(args);
    }
    return return_val;
}

int is_ok(void) {
    int return_val = 1;
    if (if_state == WANT_THEN) {
        if_state = ENTER_IF;
        fprintf(stderr, "control structure syntax error: missing then");
        return_val = 0;
    } else if (if_state == THEN_BLOCK && if_result == SUCCESS) {
        return_val = 1;
    } else if (if_state == THEN_BLOCK && if_result == FAIL) {
        return_val = 0;
    } else if (if_state == ELSE_BLOCK && if_result == FAIL) {
        return_val = 1;
    }
    return return_val;
}

int is_control(char *s) {
    return (strcmp(s, "if") == 0 || 
            strcmp(s, "then") == 0 || 
            strcmp(s, "else") == 0 || 
            strcmp(s, "fi") == 0);
}

int do_control(char **args) {
    char *cmd = args[0];
    int return_val = -1;

    /* if we're in the 'IF' block */
    if (strcmp(cmd, "if") == 0) {
        if (if_state != ENTER_IF) {
            if_state = ENTER_IF;
            fprintf(stderr, "control structure syntax error: unexpected if");
            return_val = -1;
        } else {
            result = process(args+1);
            if_result = (result == 0? SUCCESS : FAIL);
            if_state = WANT_THEN;
            return_val = 0;
        }
    /* if we're in the 'THEN' block */
    } else if (strcmp(cmd, "then") == 0) {
        if (if_state != WANT_THEN) {
            if_state = ENTER_IF;
            fprintf(stderr, "control structure syntax error: unexpected then");
            return_val = -1;
        } else {
            if_state = THEN_BLOCK;
            return_val = 0;
        }
    /* if we're in the 'ELSE' block */
    } else if (strcmp(cmd, "else") == 0) {
        if (if_state != THEN_BLOCK) {
            if_state = ENTER_IF;
            fprintf(stderr, "control structure syntax error: unexpected else");
            return_val = -1;
        } else {
            if_state = ELSE_BLOCK;
            return_val = 0;
        }
    /* if we're in the 'FI' block */
    } else if (strcmp(cmd, "fi") == 0) {
        if (if_state != THEN_BLOCK || if_state != ELSE_BLOCK) {
            if_state = ENTER_IF;
            fprintf(stderr, "control structure syntax error: unexpected fi");
            return_val = -1;
        } else {
            if_state = ENTER_IF;
            return_val = 0;
        }
    } else {
        /* TODO: fatal error */
    }
    return return_val;
}
