#include "riotExec.h"
#include "riotUI.h"

int main(int argc, char **argv) {
    enum GameMode gameMode;
    struct Windows windows;
    struct MapList mapList;
    struct Map *map;
    struct Dialog dialog[MAX_LEVELS];
    struct UnitList inmates, guards;
    struct UnitNode *unitNode;
    struct Path path;
    int levelSelect;
    bool playerProgress[MAX_LEVELS];

    /* Parse map files */
    parseMap(argv[1], &mapList, dialog);

    /* Create nCurses WINDOWs */
    uiInit(&windows);

    /* Present user with main meno */
    gameMode = menuMain(&windows);

    if (gameMode != EXIT) {

        /* New game starts on level 0 (tutorial) */
        if (gameMode == NEW) levelSelect = 0;

            /* Continue loads continue meno */
        else levelSelect = menuContinue(&windows, &mapList, playerProgress);

        /* Exit frees system resources, terminates program operation */
        while (levelSelect != EXIT) {

            /* Select currect map */
            map = &(mapList).level[levelSelect];

            /* Display intro text */
            drawText(&windows, dialog);

            /* Initialize game elements */
            getGuards(&guards, *map);
            getPath(&path, *map);
            inmates.count = 0;
            inmates.head = NULL;
            inmates.tail = NULL;

            /* Draw level */
            drawLevel(&windows, map, &guards);

            /* Prompt for unit selection */
            drawInmateSelection(&windows, map, &inmates, &guards);

            unitNode = getHead(&inmates);
            for (int i = 0; i < inmates.count; i++) {
                ((struct Inmate *) unitNode->unit)->position = path.first->location;
                unitNode = unitNode->next;
            }

            runSimulation(&windows, &guards, &inmates, &path);
        }
    }

    uiFree(&windows);
    quit("Thanks for playing.\n");

    return 0;
}


void quit(char *message) {
    if (stdscr) endwin();
    printf("%s. Exiting.", message);
    exit(1);
}
