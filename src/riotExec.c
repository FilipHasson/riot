#include "riotUI.h"

int main(int argc, char **argv) {
    struct MapList *mapList;
    enum GameMode gameMode;
    struct Interface gameInterface;
    mapList = parseMap(argv[1] ? argv[1] : NULL);
    short levelSelect;

    uiSet(INIT, &gameInterface);

    /* Begin body game loop */
    do {

        uiSet(MENU, &gameInterface);
        gameMode = menuMain(&gameInterface);
        uiSet(gameMode, &gameInterface);

        switch (gameMode) {
            case NEW:

                drawLevel(&gameInterface, mapList,12,100, levelSelect);
                break;

            case CONTINUE:
                levelSelect = menuContinue(&gameInterface, mapList);
                drawLevel(&gameInterface, mapList,12,100, levelSelect);
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
