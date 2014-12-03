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
        if (!internal(args, &return_val)) {
            return_val = execute(args);
        }
    }
    return return_val;
}

int is_ok(void) {
    int return_val = 1;
    if (if_state == WANT_THEN) {
        if_state = ENTER_IF;
        fprintf(stderr, "control structure syntax error: missing then\n");
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
            fprintf(stderr, "control structure syntax error: unexpected if\n");
            return_val = -1;
        } else {
            int i = 1;
            char *subexpr[MAX_SIZE];
            /* separate and evalute the entire expression between if and then */
            while (strcmp(args[i], "then") != 0) {
                if (is_control(args[i])) {
                    return_val = syntax_error("nested or incorrect control sequence");
                }
                subexpr[i-1] = args[i];
                i++;
            }
            subexpr[i-1] = NULL;
            result = process(subexpr);
            if_result = (result == 0? SUCCESS : FAIL);
            if_state = WANT_THEN;
            return_val = process(args+i);
        }
    /* if we're in the 'THEN' block */
    } else if (strcmp(cmd, "then") == 0) {
        if (if_state != WANT_THEN) {
            return_val = syntax_error("unexpected then");
        } else {
            int i = 1;
            char *subexpr[MAX_SIZE];
            /* separate and evalute the entire expression between then and either fi or else */
            while ((strcmp(args[i], "fi") != 0) && (strcmp(args[i], "else") != 0)) {
                if (is_control(args[i])) {
                    return_val = syntax_error("nested or incorrect control sequence");
                }
                subexpr[i-1] = args[i];
                i++;
            }
            subexpr[i-1] = NULL;
            if_state = THEN_BLOCK;
            process(subexpr);
            return_val = process(args+i);
        }
    /* if we're in the 'ELSE' block */
    } else if (strcmp(cmd, "else") == 0) {
        if (if_state != THEN_BLOCK) {
            return_val = syntax_error("unexpected else");
        } else {
            int i = 1;
            char *subexpr[MAX_SIZE];
            /* separate and evalute the entire expression between else and fi */
            while (strcmp(args[i], "fi") != 0) {
                if (is_control(args[i])) {
                    return_val = syntax_error("nested or incorrect control sequence");
                }
                subexpr[i-1] = args[i];
                i++;
            }
            subexpr[i-1] = NULL;
            if_state = ELSE_BLOCK;
            process(subexpr);
            return_val = process(args+i);
        }
    /* if we're in the 'FI' block */
    } else if (strcmp(cmd, "fi") == 0) {
        if (if_state != THEN_BLOCK && if_state != ELSE_BLOCK) {
            return_val = syntax_error("unexpected fi");
        } else {
            if_state = ENTER_IF;
            return_val = 0;
        }
    } else {
        /* TODO: fatal error */
    }

    return return_val;
}

int syntax_error(char* msg) {
    if_state = ENTER_IF;
    fprintf(stderr, "control structure syntax error: %s\n", msg);
    return -1;
}
