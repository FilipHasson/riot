#ifndef RIOT_MAP
#define RIOT_MAP

#include "riotCommon.h"

/* Data Types */

struct Map {
    char **overlay; //walls, scenerery, etc.
    struct Path *path; //a list containing the path tiles
};

struct Path {
    struct TileNode *first;
    short count;
};

struct TileNode {
    short location;
    char type;
    struct Tile *next;
};

/* Function Prototypes */

struct Map *parseMap(char *loadDir);

#endif
