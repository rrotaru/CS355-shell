/* piping support
*  allows a set of processes to be chained
*
*
* Author: Joseph Boling
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/wait.h>
#include "functions.h"
#include "robslibs.h"

// reads all output of the pipeline
void read_all(int src, int dst) {
    char buffer[BUFSIZ];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(src, buffer, BUFSIZ)) > 0) {
        bytes_written = 0;
        while (bytes_written < bytes_read)
            bytes_written += write(dst, buffer + bytes_written, bytes_read - bytes_written);
    }

}

void piping(int num, char** cmds){
	
	//create pipes for in, out, and err
	int pipe_in[2];
	int pipe_out[2];
	int pipe_err[2];
	pipe(pipe_in);
	pipe(pipe_out);
	pipe(pipe_err);
	
	if(fork() == 0) {
		
		//close in's write end and the read ends of out and err
		close(pipe_in[1]);
		close(pipe_out[0]);
		close(pipe_err[0]);
		
		//put the child's in, out, and err to use the pipeline
		dup2(pipe_in[0], STDIN_FILENO);
        dup2(pipe_out[1], STDOUT_FILENO);
        dup2(pipe_err[1], STDERR_FILENO);
		
		//execute the program
        int i = 0;
        while (cmds[i] != NULL) {
            process(cmds);
            //if (execvp(cmds[1], cmds+1) == -1) {
            //    perror("failed to start subprocess");
            // }
        }
    }
	
	//close the read of in and write of out and err
	close(pipe_in[0]);
    close(pipe_out[1]);
    close(pipe_err[1]);
	
	//pass input to the child process
	read_all(STDIN_FILENO, pipe_in[1]);
    close(pipe_in[1]);
	
	wait(NULL);
	
	//reads stdout and stderr
	puts("\nchild's stdout:");
    fflush(stdout);
    read_all(pipe_out[0], STDOUT_FILENO);
    close(pipe_out[0]);
    puts("\nchild's stderr:");
    fflush(stdout);
    read_all(pipe_err[0], STDOUT_FILENO);
    close(pipe_err[0]);
}
	
