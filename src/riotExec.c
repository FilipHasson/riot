#include "riotExec.h"
#include "riotUI.h"

int main(int argc, char **argv) {
    struct MapList *mapList;
    enum GameMode gameMode;
    struct Interface gameInterface;
    mapList = parseMap(argv[1] ? argv[1] : NULL);
    int levelSelect;
    struct UnitList *inmates;

    inmates = createList();

    uiSet(INIT, &gameInterface);



    /* Begin body game loop */
    do {
        uiSet(MENU, &gameInterface);
        gameMode = menuMain(&gameInterface);
        uiSet(gameMode, &gameInterface);

        switch (gameMode) {
            case NEW:
                drawIntroText(&gameInterface, &mapList->level[0]);
                drawInmateSelection(&gameInterface, &mapList->level[0], inmates);
                break;
            case CONTINUE:
                levelSelect = menuContinue(&gameInterface, mapList);
                drawIntroText(&gameInterface, &mapList->level[levelSelect]);
                drawInmateSelection(&gameInterface, &mapList->level[levelSelect], inmates);
                break;
            default:
                break;
        }
    } while (gameMode != EXIT);

    quit("Thanks for playing.\n");

    return 0;
}


void quit(char *message) {
    if (stdscr) endwin();
    printf("%s. Exiting.", message);
    exit(1);
}
