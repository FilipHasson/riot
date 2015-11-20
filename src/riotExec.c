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
    bool progress[MAX_LEVELS];
    int level=0;

    /* Parse map files */
    parseMap(argv[1], &mapList, dialog);

    /* Create nCurses WINDOWs */
    uiInit(&windows);

    /* Present user with main menu */
    gameMode = menuMain(&windows);

    do{
        if(gameMode==EXIT){
            break;
        } else if (gameMode!=NEW){
            level = levelSelect(&windows, &mapList, progress);
        }

        /* Select current map */
        map = &(mapList).level[level];

        /* Display intro text */
        drawText(&windows, dialog[level], gameMode);

        /* Initialize game elements */
        getGuards(&guards, *map);
        getPath(&path, *map);
        inmates.count = 0;
        inmates.head = NULL;
        inmates.tail = NULL;

        /* Draw level */
        drawLevel(&windows, map, &guards);

        /* Prompt user for unit selection */
        drawInmateSelection(&windows, map, &inmates, &guards);

        unitNode = getHead(&inmates);
        for (int i = 0; i < inmates.count; i++) {
            ((struct Inmate *) unitNode->unit)->position = path.first->location;
            unitNode = unitNode->next;
        }

        /* Simulate unit interactions */
        progress[level] = simulate(&windows, &guards, &inmates, &path);
        if(progress[level]) gameMode=WIN;
        else gameMode=LOSE;

        /* Display outro text */
        drawText(&windows, dialog[level], gameMode);

    } while (level!=EXIT);

    uiFree(&windows);
    quit("Thanks for playing.\n");

    return 0;
}


void quit(char *message) {
    if (stdscr) endwin();
    printf("%s. Exiting.", message);
    exit(1);
}
