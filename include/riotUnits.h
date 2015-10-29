#ifndef RIOT_UNITS
#define RIOT_UNITS

#include "riotCommon.h"

/* Data Types */

struct Inmate {
    char type;
    short healthMax;
    short healthCur;
    char repCost;
    struct Inmate *next;
};

struct Guard {
    char type;
    enum AI ai;
    struct Guard *next;
};


/* Function Prototypes */

_Bool unitAdd(char InmateType);

#endif
