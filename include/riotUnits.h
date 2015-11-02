#ifndef RIOT_UNITS
#define RIOT_UNITS

#include "riotCommon.h"


/* Data Types */

struct Inmate {/*

 Inmate stores the information related to inmate units.*/

    char type;
    double position;
    short speed;
    short healthMax;
    short healthCur;
    char repCost;
    struct Inmate *next;
}Inmate;


struct Guard {/*

 Inmate stores the information related to guard units.*/

    char type;
    enum AI ai;
    short damage;
    short positionRange[10]; 
    struct Guard *next;
}Guard;


/* Function Prototypes */

_Bool unitAdd(char InmateType);/*

DESCRIPTION: unitAdd() is used to add an inmate to the game.

ARGUMENTS: The character pressed by the user which corresponds to an
 associated unit type.

PRECONDITIONS: The character provided corresponds with an inmate type
 specified within the Inmate enum.

POSTCONDITIONS: An Inmate is added to the Inmate list.*/

#endif //RIOT_UNITS
