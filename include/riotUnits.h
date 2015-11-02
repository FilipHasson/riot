#ifndef RIOT_UNITS
#define RIOT_UNITS

#include "riotCommon.h"

/* Data Types */

typedef struct Inmate {
    char type;
    double position;
    short speed;
    short healthMax;
    short healthCur;
    char repCost;
    struct Inmate *next;
}Inmate;

typedef struct Guard {
    char type;
    enum AI ai;
    short damage;
    short positionRange[10]; 
    struct Guard *next;
}Guard;


/* Function Prototypes */

_Bool unitAdd(char InmateType);

#endif
