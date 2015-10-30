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

void checkArgs(int argc, char **argv);

#endif