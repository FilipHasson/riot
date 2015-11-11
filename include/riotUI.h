#ifndef RIOT_UI
#define RIOT_UI

#include "riotExec.h"
#include "riotMap.h"

/* Data Types */

struct Interface {
    WINDOW *menu;
    WINDOW *main;
    WINDOW *header;
    WINDOW *footer;
};

struct MenuEntry {
    char key;
    char *text;
    struct MenuEntry *next;
};


/* Function Prototypes */

void uiSet(enum GameMode gameMode, struct Interface *win);/*

DESCRIPTION: uiSet() will initialize the various ncurses windows used
 throughout gameplay.

ARGUMENTS: a GameMode enum corresponding with the required game mode and a
 Interface struct which contains pointers to the target ncurses WINDOWs.

POSTCONDITIONS: Memory may either be allocated or deallocated for ncurses
 windows depending on the passed gameMode.*/


enum GameMode menuMain(struct Interface *);/*

DESCRIPTION: menuMain() will present the user with the main menu.

ARGUMENTS: the Interface struct containing the targer ncurses WINDOWs.*/


short menuContinue(struct Interface *gameInterface, struct MapList *mapList);

void inmateUpdate(enum Colour, char inmateType, short from, short to);

void inmateRemove(short position);

void guardUpdate(bool isAttacking, short position);

/*This is Filip trying to figure out his shit, 
try not to worry about it for now :D*/
enum GameMode gameTest (struct Interface *gameInterface,struct MapList *mapList,int level);
void drawMap (WINDOW *mWin, struct Map*map);
#endif //RIOT_UI
