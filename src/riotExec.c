#include <riotUI.h>
#include "riotExec.h"
#include "riotMap.h"

int main(int argc, char **argv) {

//    struct Map *map;
    enum GameMode gameMode;
    struct GameInterface *gameInterface = NULL;
    checkArgs(argc, argv);

//    checkDisplay();
//    map = parseMap(argv[1] ? argv[1] : NULL);

    gameMode = INIT;

    while (gameMode != EXIT)
        uiSet(gameMode,gameInterface);
        gameMode = menuMain(gameInterface);
    return 0;
}


void checkArgs(int argc, char **argv) {

    /* Assess passed directory */

    if (argc > 2) error("Too Many arguments");

    if (argc == 2) {
        //check passed dir
        //if invalid, abort
    }

    return;
}

void error(char *message) {
    printf("Error: %s. Exiting.", message);
    exit(-1);
}
