#include <riotUI.h>
#include "riotExec.h"
#include "riotMap.h"

int main(int argc, char **argv) {

//    struct Map *map;
    enum GameMode gameMode;
    struct GameInterface gameInterface;
    checkArgs(argc, argv);

    checkDisplay();
//    map = parseMap(argv[1] ? argv[1] : NULL);

    gameMode = INIT;

    do {
        uiSet(gameMode, &gameInterface);
        gameMode = menuMain(&gameInterface);
    }while (gameMode != EXIT);

    done("Thanks for playing.");

    return 0;
}


void checkArgs(int argc, char **argv) {

    /* Assess passed directory */

    if (argc > 2) done("Too Many arguments");

    if (argc == 2) {
        //check passed dir
        //if invalid, abort
    }

    return;
}

void done(char *message) {
    if(stdscr) endwin();;
    printf("%s. Exiting.", message);
    exit(-1);
}
