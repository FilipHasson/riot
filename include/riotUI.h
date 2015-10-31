#ifndef RIOT_UI
#define RIOT_UI

#include "riotCommon.h"

/* Data Types */

struct GameInterface {
    WINDOW *menu;
    WINDOW *main;
    WINDOW *header;
    WINDOW *footer;
};

/* Function Prototypes */
void uiSet(enum GameMode gameMode, struct GameInterface *gameInterface);
enum GameMode menuMain(struct GameInterface *) ;
void inmateUpdate(enum Colour, char inmateType, short from, short to);
void inmateRemove(short position);
void guardUpdate(_Bool isAttacking, short position);

#endif
