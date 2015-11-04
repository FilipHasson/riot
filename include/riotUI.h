#ifndef RIOT_UI
#define RIOT_UI

#include "riotExec.h"


/* Data Types */

struct GameInterface {
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

void uiSet(enum GameMode gameMode, struct GameInterface *gameInterface);/*

DESCRIPTION: uiSet() will initialize the various ncurses windows used
 throughout gameplay.

ARGUMENTS: a GameMode enum corresponding with the required game mode and a
 GameInterface struct which contains pointers to the target ncurses WINDOWs.

POSTCONDITIONS: Memory may either be allocated or deallocated for ncurses
 windows depending on the passed gameMode.*/


enum GameMode menuMain(struct GameInterface *);/*

DESCRIPTION: menuMain() will present the user with the main menu.

ARGUMENTS: the GameInterface struct containing the targer ncurses WINDOWs.*/


void inmateUpdate(enum Colour, char inmateType, short from, short to);

void inmateRemove(short position);

void guardUpdate(bool isAttacking, short position);

#endif //RIOT_UI
