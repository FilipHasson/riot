#ifndef RIOT_UI
#define RIOT_UI

#include "riotExec.h"
#include "riotMap.h"
#include "riotUnits.h"

/* Data Types */

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

DESCRIPTION: menuMain() will present the user with the body menu.

ARGUMENTS: the Interface struct containing the targer ncurses WINDOWs.*/


int menuContinue(struct Interface *gameInterface, struct MapList *mapList);


void inmateUpdate(enum Colour, char inmateType, int from, int to);


void inmateRemove(int position);


void guardUpdate(bool isAttacking, int position);


void drawMap (WINDOW *bod, struct Map*map);


char * getLevelName (int level);


void updateHeader (WINDOW *header, struct Map *map);


void drawIntroText (struct Interface *win, struct Map *map);


void drawOutroText (struct Interface *win, struct Map *map);


void drawQueue (WINDOW *body);


void updateQueue (WINDOW *body, struct UnitList *list, int numAdded);/*




DESCRIPTION: Gets name of level

ARGUMENTS: integer value of what level (0-7)*/


void redrawUnit(struct Interface *win, struct Inmate *inmate, struct Path *path, int oldPosition);
/*

DESCRIPTION: Function to redraw units on the screen

ARGUMENTS: A pointer to the interface window, unit to be drawn, integer health value, curreent position and position to be mmoved to

POSTCONDITION: Ensures that the unit given is drawn at the given newPostiion*/


void drawUnit(struct Interface * win, char unitType,int health, int position);/*

DESCRIPTION: Draws a unit to a given position on the screen

ARGUMENTS: A pointer to the interface window, unit to be drawn, integer health value, integer value to draw at

POSTCONDITION:*/


void eraseUnit(struct Interface * win, int position);/*

DESCRIPTION: Erases a unit off the screen and restores tile

ARGUMENTS: Pointer to the interface window and position as an integer value

POSTCONDITION: Ensures the given position displays an aseterisk */


void drawTile(struct Interface * win, char type, int position);/*

DESCRIPTION: Draws a tile to the screen 
 
ARGUMENTS: take pointer to interface window, haracter to be drawn, and a position as an integer value

POSTCONDITION: Ensures the character given is displayed at the position given */


int * getCoordinate(int position);/*

DESCRIPTION: Takes the position and converts it into a 2 dimensional coordinate

ARGUMENTS: a position as a single integer value */

void drawInmateSelection (struct Interface *win, struct Map *map, struct UnitList *imates);
 
void drawLevel(struct Interface *win, struct Map* map);

void drawFooterInmates(struct Interface * win, char * inmates);

void startHeadFoot(struct Interface *win, struct Map *map);

char * getInmateName(char ch);
/*
void drawBorders (struct Interface * win);
*/
#endif //RIOT_UI
