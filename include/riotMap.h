#ifndef RIOT_MAP
#define RIOT_MAP

#include "riotExec.h"


/* Data Types */

struct Map {
    /*

     Map stores the game landscape as a 2D array, along with a linked list
     containing the pathh.*/

    char overlay[SIZE_Y][SIZE_X]; //walls, scenery, etc.
    struct Path *path; //a list containing the path tiles
};


struct Path {
    /*

     Path stores the game path as a list of TileNodes.*/

    struct TileNode *first;
    unsigned short count;
};


struct TileNode {
    /*

     TileNode contains the location of the map on the board, along with a the
     character representation of the tile.*/

    short location;
    char type;
    struct Tile *next;
};


/* Function Prototypes */

struct Map *parseMap(char *loadDir);/*

DESCRIPTION: parseMap() will parse level files and store their contents into
 the structures used by the rest of the system.

ARGUMENTS: either a custom path containing the desired map files, or NULL in
 which case the default map directory will be sourced.

POSTCONDITIONS: A Map struct is returned containing the map elements and
 tower placements.*/

#endif //RIOT_MAP
