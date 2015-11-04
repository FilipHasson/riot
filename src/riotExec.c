#include "riotUI.h"


int main(int argc, char **argv) {

    struct MapList* mapList;
    enum GameMode gameMode;
    struct Interface gameInterface;
    mapList = parseMap(argv[1] ? argv[1] : NULL);


    uiSet(INIT, &gameInterface);


   do {

        gameMode = menuMain(&gameInterface);
        uiSet(gameMode, &gameInterface);

        switch (gameMode) {
            case NEW:
//                newGame();
                break;

            case CONTINUE:
                menuContinue(&gameInterface, mapList);
                break;

            default:
                break;
        }
    } while (gameMode != EXIT);

    quit("Thanks for playing.");

    return 0;
}


void quit(char *message) {
    if (stdscr) endwin();
    printf("%s. Exiting.", message);
    exit(1);
}
