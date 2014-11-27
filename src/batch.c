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
int file_read(char* filename, char* buffer) {
    FILE *file;
    int filesize;

    if ( (file = fopen(filename, "r")) != NULL ) {
        if (fseek(file, 0, SEEK_END) == 0) {
            filesize = ftell(file);
            if (filesize != -1) {
                buffer = malloc (sizeof(char) * filesize);
                if (fseek(file, 0, SEEK_SET) != 0) {
                    if (fread(buffer, sizeof(char), filesize, file) != 0) {
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

/* execute a number of commands form a string buffer */
void batch_execute(char* str) {
    char *command, *trimmedcommand;
    size_t len;

    while ( (command = strtok(str, ";\n")) != NULL) {
        len = trimwhitespace(trimmedcommand, strlen(command), command);

        /* if not a comment and not an empty string */
        if (len > 0 && trimmedcommand[0] != '#') {
            /* TODO: execute command */
            printf("I should execute: %s", trimmedcommand);//replace this
        }

        /* get next command */
        command = strtok(NULL, ";\n");
    }


    return;
}
