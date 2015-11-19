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

void uiInit(struct Windows *win);


void uiFree(struct Windows *win);


void drawText (struct Windows *windows, struct Dialog * dialog);


enum GameMode menuMain(struct Windows *);/*

DESCRIPTION: menuMain() will present the user with the body menu.

ARGUMENTS: the Windows struct containing the targer ncurses WINDOWs.*/


int menuContinue(struct Windows *gameInterface, struct MapList *mapList,
    bool* playerProgress);/*

DESCRIPTION: The menu that comes up when 'C' is pressed; it displays all the levels and lets
the user select ones that are unlocked

ARGUMENTS: The game interface
           The list of maps*/


void inmateRemove(int position);/*

DESCRIPTION: Removes an inmate of a certain position from the list

ARGUMENTS: The position of the inmate which will be removed
*/


void drawMap (WINDOW *bod, struct Map*map);/*

DESCRIPTION: A function that is called at the beginning of the game to
create the map (path and all the obstacles)

ARGUMENTS: The window the map will be drawn on
           The map that will be loaded   */


char * getLevelName (int level); /*

DESCRIPTION: A function that returns the name of the level given

ARGUMENTS: The level that will be used*/


void updateHeader (WINDOW *header, struct Map *map);/*

DESCRIPTION: Updates the text in the header bar

ARGUMENTS: The header window
           The map (each map has a different header description)
*/


void drawIntroText (struct Windows *win, struct Map *map);/*

DESCRIPTION: Writes the introduction text for the level specified

*/


void updateQueue (WINDOW *body, struct UnitList *list, int numAdded);/*
DESCRIPTION: Updates the units in the box drawn by drawQueue function

ArRGUMENTS: The body window
            The unit list that will be displayed
*/


void drawOutroText (struct Windows *win, struct Map *map);/*

DESCRIPTION: Write an outro text at the end of specified level

ARGUMENTS: A window interface
           The map that has been completed
*/


void drawQueue (WINDOW *body); /*

DESCRIPTION: Draws a box for where the queue will be displayed 
on the side of the body window 

ARGUMENTS: The body window*/

void redrawUnit(WINDOW *body, struct Inmate *inmate, struct Path *path, float oldPosition);


/*

DESCRIPTION: Function to redraw units on the screen

ARGUMENTS: A pointer to the interface window, unit to be drawn, integer health value, curreent position and position to be mmoved to

POSTCONDITION: Ensures that the unit given is drawn at the given newPostiion*/
void eraseUnit(struct Windows * win, int position);/*

DESCRIPTION: Erases a unit off the screen and restores tile

ARGUMENTS: Pointer to the interface window and position as an integer value

POSTCONDITION: Ensures the given position displays an aseterisk */


void drawTile(struct Windows * win, char type, int position);/*

DESCRIPTION: Draws a tile to the screen 
 
ARGUMENTS: take pointer to interface window, haracter to be drawn, and a position as an integer value

POSTCONDITION: Ensures the character given is displayed at the position given */


int * getCoordinate(int position);/*

DESCRIPTION: Takes the position and converts it into a 2 dimensional coordinate

ARGUMENTS: a position as a single integer value */


void drawInmateSelection (struct Windows *win, struct Map *map, struct UnitList *inmates, struct UnitList *guards);/*

DESCRIPTION: Draws the window of all the inmates that the player an choose from 

ARGUMENTS: The interface window
           The current map loaded
           The list of inmates
*/


void drawLevel(struct Windows *windows, struct Map* map, struct UnitList *guard); /*

DESCRIPTION: Calls drawMap and drawQueue and refreshes the body window

ARGUMENTS: The body window
           The map that will be loaded
*/


void drawFooterInmates(struct Windows * win, char * inmates); /*

DESCRIPTION: Writes out the list of available inmates into the footer

ARGUMENTS: The interface window
           The inmates
*/


void startHeadFoot(struct Windows *win, struct Map *map);/*

DESCRIPTION: Draws the boxes of the header and the footer and calls updatesHeader

ARGUMENTS: The interface window
           The loaded map
*/


char * getInmateName(char ch); /*

DESCRIPTION: Return the name of the inmate

ARGUMENTS: The abbreviation of the inmate, for example 'H' for homeboy  
*/


#endif //RIOT_UI
