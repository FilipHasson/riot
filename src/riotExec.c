#include "riotExec.h"
#include "riotUI.h"

int main(int argc, char **argv) {
    struct MapList *mapList;
    enum GameMode gameMode;
    struct Interface gameInterface;
    mapList = parseMap(argv[1] ? argv[1] : NULL);
    int levelSelect;
    uiSet(INIT, &gameInterface);

    /* Begin body game loop */
    do {
        uiSet(MENU, &gameInterface);
        gameMode = menuMain(&gameInterface);
        uiSet(gameMode, &gameInterface);

        switch (gameMode) {
            case NEW:
                play(gameInterface,mapList->level[0]);
                break;
            case CONTINUE:
                levelSelect = menuContinue(&gameInterface, mapList);
                play(gameInterface,mapList->level[levelSelect]);
                break;
            default:
                break;
        }
    } while (gameMode != EXIT);

    quit("Thanks for playing.\n");

    return 0;
}

void play(struct Interface gameInterface,struct Map map){
    struct UnitList *inmates;
    struct UnitList *guards;
    struct Path *path;

    inmates = createList();

    drawIntroText(&gameInterface, &map);
    guards = getGuardList(map);
    drawInmateSelection(&gameInterface,&map, inmates, guards);

//    path = getPath(map);
//    runSimulation(&gameInterface, guards,inmates,path);

}

void quit(char *message) {
    if (stdscr) endwin();
    printf("%s. Exiting.", message);
    exit(1);
}
