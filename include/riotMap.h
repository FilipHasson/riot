#ifndef RIOT_MAP
#define RIOT_MAP

#include "riotExec.h"

#define NAME_LEN 25 //needs to be revised
#define PATH_MAX 4096


/* Data Types */

struct MapList {
    struct Map *first;
    short count;
};


struct Map {/*

 Map stores the game landscape as a 2D array, along with a linked list
 containing the path.*/

    char name[NAME_LEN];
    char location[PATH_MAX];
    bool hidden;
    char overlay[SIZE_Y][SIZE_X]; //walls, scenery, etc.
    struct Path *path; //a list containing the path tiles
    struct Map *next;
};


struct Path {/*

 Path stores the game path as a list of TileNodes.*/

    struct TileNode *first;
    unsigned short count;
};


struct TileNode {/*

 TileNode contains the location of the map on the board, along with a the
 character representation of the tile.*/

    short location;
    char type;
    struct Tile *next;
};


/* Function Prototypes */

struct MapList * parseMap(char *loadDir);/*

DESCRIPTION: parseMap() will parse level files and store their contents into
 the structures used by the rest of the system.

ARGUMENTS: either a custom path containing the desired map files, or NULL in
 which case the default map directory will be sourced.

POSTCONDITIONS: A Map struct is returned containing the map elements and
 tower placements.*/

int getFilename(char *filename, char *ext);

#endif //RIOT_MAP
