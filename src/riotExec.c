#include "riotExec.h"
#include "riotUI.h"

int main(int argc, char **argv) {
    enum GameMode gameMode;
    struct Windows windows;
    struct MapList mapList, *mapListPtr;
    struct Dialog dialog[MAX_LEVELS];
    int levelSelect;
    bool playerProgress[MAX_LEVELS];

    parseMap(argv[1], &mapList, dialog);
    uiInit(&windows);

    mapListPtr = &mapList;
    gameMode = menuMain(&windows);

    if (gameMode != EXIT) {
        if (gameMode == NEW) levelSelect = 0;
        else levelSelect = menuContinue(&windows, &mapList, playerProgress);
        while (levelSelect != EXIT) {
            drawText(&windows, dialog);
            play(&windows, &(mapListPtr->level[levelSelect]));
        }
    }

    uiFree(&windows);
    quit("Thanks for playing.\n");

    return 0;
}


void play(struct Windows *windows, struct Map *map) {
    struct UnitList *inmates;
    struct UnitList *guards;
    struct UnitNode *nextInmate;
    struct Path *path;

    wclear(windows->body);
    wclear(windows->header);
    wclear(windows->footer);

    inmates = createList();
    guards = getGuardList(*map);
    path = getPath(*map);

    drawInmateSelection(windows, map, inmates, guards);

    nextInmate = getHead(inmates);
    for (int i = 0; i < inmates->count; i++) {
        ((struct Inmate *) nextInmate->unit)->position = path->first->location;
        nextInmate = nextInmate->next;
    }
    runSimulation(windows, guards, inmates, path);
}


void quit(char *message) {
    if (stdscr) endwin();
    printf("%s. Exiting.", message);
    exit(1);
}
