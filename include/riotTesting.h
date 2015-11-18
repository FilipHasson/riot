#ifndef RIOT_TESTING
#define RIOT_TESTING

#include "riotExec.h"
#include "riotMap.h"
#include "riotUnits.h"
#include "riotUI.h"

#define TRIALS 10
#define MAPSIZE 100

void printInmates(struct UnitList *list);/*

DESCRIPTION: Prints the inmate list

ARGUMENTS: The inmate list
*/

void printGuards(struct UnitList *list);/*

DESCRIPTION: Prints the guard list

ARGUMENTS: The guard list
*/


void unitsMove(char *loadDir);/*

DESCRIPTION: Testing the movement of the units

ARGUMENTS: The location of the directory
*/


void unitsTest(void);/*

DESCRIPTION: Testing the guard range and attacking

ARGUMENTS:
*/

void unitsPlay(char *argument);

void mapTest(char *loadDir);/*

DESCRIPTION: Tests the map

ARGUMENTS: The location of the directory
*/

void testingHelp();

#endif //RIOT_TESTING
