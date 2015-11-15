#ifndef RIOT_MAP
#define RIOT_MAP

#include "riotExec.h"

#define NAME_LEN 35
#define PATH_MAX 4096
#define LINE_MAX 72
#define MAP_SIZE 1545
#define MAX_LEVELS 10
#define INMATE_TYPES 10
#define DELIMITER ";"
#define TEXT_OFFSET 7
#define REGEX_EXT "(\\.)?[0-9](.riot)$"


/* Data Types */

struct Map {/*

 Map stores the game landscape as a 2D array, along with a linked list
 containing the path.*/

    char name[NAME_LEN];
    int levelNo;
    bool hidden;
    bool beaten;
    char overlay[MAP_ROWS][MAP_COLS]; //walls, scenery, etc.
    char inmates[INMATE_TYPES];
    int panicMax;
    int repMax;
};


struct MapList {
    struct Map level[MAX_LEVELS];
    int count;
};


struct Path {/*

 Path stores the game path as a list of TileNodes.*/

    struct TileNode *first;
    unsigned int count;
};


struct TileNode {/*

 TileNode contains the location of the map on the board, along with a the
 character representation of the tile.*/

    int location;
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
