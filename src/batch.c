/* Batch file execution support,
 * file to string operations
 * additional features
 * 
 * Author: Robert Rotaru
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

/* read file into string buffer. returns number of chars read
 * REMEMBER to free() buffer after finishing */
long file_read(char* filename, char** buffer) {
    FILE *file;
    long filesize = -1;

    if ( (file = fopen(filename, "r")) != NULL ) {
        if (fseek(file, 0L, SEEK_END) == 0) {
            filesize = ftell(file);
            if (filesize != -1) {
                *buffer = malloc(sizeof(char) * filesize);
                if (fseek(file, 0L, SEEK_SET) == 0) {
                    if (fread(*buffer, sizeof(char), filesize, file) != 0) {
                        /* good */
                    }
                    if (feof(file)) { fprintf(stderr, "END OF FILE %s", filename); }
                }
            }
        }
        fclose(file);
    }

    return filesize;
}

/* trim whitespace around a string and return a copy of the string */
size_t trimwhitespace(char *out, size_t len, const char *str) {

  const char *end;
  size_t out_size;

  if(len == 0) {
      return 0;
  }

  // Trim leading space
  while(isspace(*str)) { 
      str++; 
  }

  if(*str == 0) {
    *out = 0;
    return 1;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) { 
      end--;
  }
  end++;

  // Set output size to minimum of trimmed string length and buffer size minus 1
  out_size = (end - str) < len-1 ? (end - str) : len-1;

  // Copy trimmed string and add null terminator
  memcpy(out, str, out_size);
  out[out_size] = 0;

  return out_size;
}

/* execute a number of commands from a file */
void batch_execute(char* filename) {
    char *str, *command, *trimmedcommand;
    size_t size;

    if ((file_read(filename, &str)) > 0) {
        command = strtok(str, ";\n");
        while (command != NULL) {
            size = strlen(command) + 1;
            trimmedcommand = malloc(sizeof(char) * size);
            size = trimwhitespace(trimmedcommand, size, command);

            /* if not a comment and not an empty string */
            if (size > 1 && trimmedcommand[0] != '#') {
                /* TODO: execute command */
                printf("COMMAND: %s (todo: execute this)\n", trimmedcommand); //replace this
            } else { printf("COMMENT: %s (todo: ignore)\n", trimmedcommand); }
            
            /* get next command */
            free(trimmedcommand);
            command = strtok(NULL, ";\n");
        }
    }
    free(str);
    return;
}
