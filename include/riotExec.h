#ifndef RIOT_EXEC
#define RIOT_EXEC

#include "riotCommon.h"

/* Data Types */
struct MenuEntry {
    char key;
    char *text;
    struct MenuEntry *next;
};


/* Function Prototypes */

void checkArgs(int argc, char **argv);/*

DESCRIPTION: checkArgs() can be used to validate the command-line arguments
 passed by the user.

ARGUMENTS: argc, represents the number of command line paramers passed to the
 program at runtime and argv is an array containing the character strings
 representing those parameters.

POSTCONDITIONS: May call quit() to terminate program operation if the user
 has provided an invalid map file path.*/


void checkDisplay();/*

DESCRIPTION: checkDisplay() can be used to validate that the terminal used to
 execute the program has dimensions sufficient to display the program.

POSTCONDITIONS: May call quit() to terminate program operation if determined
 terminal dimensions are insufficient.*/

#endif //RIOT_EXEC
