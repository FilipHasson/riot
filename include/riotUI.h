#ifndef RIOT_UI
#define RIOT_UI

#include "riotCommon.h"
#include <ncurses.h>


/* Data Types */

struct GameInterface {
    WINDOW *main;
    WINDOW *header;
    WINDOW *footer;
};

/* Function Prototypes */
_Bool menuInit() ;
void inmateUpdate(enum Colour, char inmateType, short from, short to);
void inmateRemove(short position);
void guardUpdate(_Bool isAttacking, short position);

#endif