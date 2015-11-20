#ifndef RIOT_MAP
#define RIOT_MAP

#include "riotExec.h"
#include <locale.h>
#include <wchar.h>

#define PATH_MAX 4096
#define LINE_MAX 72
#define MAP_SIZE 1545
#define MAX_LEVELS 10
#define MAX_TEXT 500
#define INMATE_TYPES 10
#define REGEX_EXT "(\\.)?[0-9](.riot)$"


/* Data Types */

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
    struct TileNode *next;
};


/* Function Prototypes */

void parseMap(char *loadDir, struct MapList* mapList, struct Dialog dialog[]);/*

DESCRIPTION: parseMap() will parse level files and store their contents into
 the structures used by the rest of the system.

ARGUMENTS: either a custom path containing the desired map files, or NULL in
 which case the default map directory will be sourced.

POSTCONDITIONS: A Map struct is returned containing the map elements and
 tower placements.*/



void getPath(struct Path* path, struct Map map);/*

DESCRIPTION: Retreieves information from the given map and stores this data into a path structure.
             Returns said path structure.

ARGUMENTS: The map that will be parsed.*/





void addToPath(struct Path *path, int location, char type);/*

DESCRIPTION: Adds an additional tile to the path

ARGUMENTS: The path which the tile is being added to
           The location(position) of where the tile will be located
           The type of tile that is going to be added*/


void getGuards(struct UnitList *guards, struct Map map);/*

DESCRIPTION: Retrieves the guard data from the given map and stores the guards into a linked list UnitList structure.

ARGUMENTS: The map that will be parsed */


bool isPathCharacter(char tileChar);/*

DESCRIPTION: Returns a boolean based on whether the character is a path character.

ARGUMENTS: Character to be checked.
*/


struct TileNode * createTileNode(int location, char type);/*

DESCRIPTION: Creates a tile node and initializes it.

ARGUMENTS: Location of the tile node (int location).
           Character type of the tile node (char type).
*/


void destroyPath(struct Path * path);/*

DESCRIPTION: Destroys the path and all the contents of the path.

ARGUMENTS: Path to be destroyed (struct Path *path).
*/


void pushToPath(struct TileNode* insertNode, struct Path* path);/*

DESCRIPTION: Pushes a tile node to the back of the path list.

ARGUMENTS: Tile Node to be pushes (struct TileNode* insertNode).
           Path that the tile node is pushed into (struct Path* path).
*/


struct Path *pathSolve(struct Map map,struct Path *path,int prevChecked[],int count,int currentPosition);/*

DESCRIPTION: Recursive function which creates an ordered path struct.

ARGUMENTS: Map struct to be searched (struct Map map).
           Path struct to be created(struct Path *path).
           Previously checked positions(int prevChecked[]).
           Number of the tile that has been added to the path(int count).
           Current position being searched in the map struct(int currentPosition).

*/


bool beenChecked(int prevChecked[],int position);/*

DESCRIPTION: Checks whether the position exists in the previously checked array.

ARGUMENTS: Array of all positions previously checked (int prevChecked[]).
           Position to be compared against the previously checked positions.
*/

#endif //RIOT_MAP
