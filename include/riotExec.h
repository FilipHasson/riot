#ifndef RIOT_EXEC
#define RIOT_EXEC
#define _DEBUG

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Macro Constants */

#define MAX_COLS 80
#define MAX_ROWS 24
#define MAP_COLS 72
#define MAP_ROWS 16
#define HEADER 3
#define FOOTER 4
#define MAIN 17

#define MAX_TEXT 500
#define INMATE_TYPES 10
#define LINE_MAX 72


/* Data Types */

struct Windows {
    WINDOW *menu;
    WINDOW *body;
    WINDOW *header;
    WINDOW *footer;
};


struct Dialog{
    char textIntro[MAX_TEXT];
    char textWin[MAX_TEXT];
    char textLose[MAX_TEXT];
};


struct Map {/*

 Map stores the game landscape as a 2D array, along with a linked list
 containing the path.*/

    char name[LINE_MAX];
    int levelNo;
    char overlay[MAP_ROWS][MAP_COLS+1]; //+1 for null char
    char inmates[INMATE_TYPES];
    int panicMax;
    int repMax;
    struct Dialog dialog;
};


enum InmateType {/*

 InmateType is a mnemonic which can be used to equivocate inmate types with
 the associated keypresses used to spawn them.*/

    PROTAGONIST,
    HOMEBOY = 'h',
    BRUISER = 'b',
    LUNATIC = 'l',
    FATTY = 'f',
    SPEEDY = 's',
    CUTIE = 'c',
    ATTORNEY = 'a',
    DOCTOR = 'd'
};


enum GuardType {/*

 GuardType provides a mnemonic for guard unit types.*/

    GUARD = 'G',
    DOGS = 'D',
    LUNCH = 'L', //lunch lady
    PSYCH = 'P', //psychiatrist
    SHARP = 'S', //sharpshooter
    WARDEN = 'W',
    CYBORG = 'C'
};


enum AI {/*

 AI provides a mnemonic for guard AI profiles.*/

    PROX, //proximity
    AOE, //area of effect
    END, //closest to end
};


enum Colour {/*

 Colour provides a mnemonic for the colours used to convey health values.*/

    GREEN = 10,
    YELLOW = 11,
    RED = 9,
    PURPLE = 5,
};


enum GameMode {/*

 GameMode is a mnemonic which can be used to equivocate game modes with the
 associated keypresses used to inititate them.*/

    INIT,
    MENU,
    PLAY,
    NEW = 'n',
    CONTINUE = 'c',
    EXIT = 'e',
    _GAME_MODE_LIMIT,
};


/* Function Prototypes */

void quit(char *message);/*

DESCRIPTION: quit() is called as a method for the program to gracefully return
 to the command prompt when facing undefined behaviour or user input. Will
 exit curses mode if it is activated and provide the user with a message as
 to the nature of the error.

ARGUMENTS: A string with the message to be printed to stdout.

POSTCONDITIONS: Program termination.*/


void checkArgs(int argc, char **argv);/*

DESCRIPTION: checkArgs() can be used to validate the command-line arguments
 passed by the user.

ARGUMENTS: argc, represents the number of command line paramers passed to the
 program at runtime and argv is an array containing the character strings
 representing those parameters.

POSTCONDITIONS: May call quit() to terminate program operation if the user
 has provided an invalid map file path.*/


void play(struct Windows *gameInterface,struct Map* map);/*

DESCRIPTION: play() calls all functions that involve player unit selection, and game simulation.

ARGUMENTS: Game interface struct that holds neccessary windows (struct Windows gameInterface).
           Map struct which holds neccessary map information (struct Map map). 

*/

#endif //RIOT_EXEC
