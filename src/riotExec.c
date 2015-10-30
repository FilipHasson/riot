#include <stdio.h>
#include <stdlib.h>

#include "riotExec.h"
#include "riotUI.h"
#include "riotMap.h"

int main(int argc, char **argv) {

    // struct Map *map;

    checkArgs(argc, argv);
    checkDisplay();

    // map = parseMap(argv[1]);
    // menuMain();
    // menuMap();
    return 0;
}


void checkArgs(int argc, char **argv) {

    /* Assess passed directory */

    if (argc > 2 ) {
        printf("Error. Too Many arguments. Exiting.");
        exit(-1);
    }

    if (argc == 2) {
        //check passed dir
        //if invalid, abort
    }

    return;
}
