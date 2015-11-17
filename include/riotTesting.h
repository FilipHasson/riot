#ifndef RIOT_TESTING
#define RIOT_TESTING

#include "riotExec.h"
#include "riotMap.h"
#include "riotUnits.h"
#include "riotUI.h"

#define TRIALS 10
#define MAPSIZE 100

void printInmates(struct UnitList *list);


void printGuards(struct UnitList *list);


void unitsMove(char *loadDir);


void unitsTest(void);


void mapTest(char *loadDir);


void testingHelp();

#endif //RIOT_TESTING
