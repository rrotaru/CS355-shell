/* Shell initialization message and window clearing
 * 
 * Author: Robert Rotaru
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "robslibs.h"
#include "functions.h"

int init_msg(void) {

    int i;
    char *msg = "NOVAshell version 0.1a\n"
                "Built by Bryan Bigelow, Robert Rotaru, Joseph Boling\n"
                "CS355 Project at Central Connecticut State University\n"
                "This software is released as open source under the\n"
                "GNU General Public License (GPL) v3.0 and is available\n"
                "on GitHub at https://github.com/rrotaru/CS355-shell\n\n";

    printf("\033c"); // Clears/resets the terminal window
    printf("%s", msg); // Prints our init message
    return EXIT_SUCCESS;
}
