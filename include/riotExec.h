#ifndef RIOT_EXEC
#define RIOT_EXEC

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


/* Macro Constants */
#define MAX_COLS 80
#define MAX_ROWS 24
#define MAP_COLS 73
#define MAP_ROWS 15
#define HEADER 3
#define FOOTER 4
#define MAIN 17


/* Data Types */

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

    GUARD,
    DOGS,
    LUNCH, //lunch lady
    PSYCH, //psychiatrist
    SHARP, //sharpshooter
    WARDEN,
    CYBORG
};


enum AI {/*

 AI provides a mnemonic for guard AI profiles.*/

            PROX, //proximity
    AOE, //area of effect
    END, //closest to end
};


enum Colour {/*

 Colour provides a mnemonic for the colours used to convey health values.*/

    GREEN,
    YELLOW,
    ORANGE,
    RED,
};


enum GameMode {/*

 GameMode is a mnemonic which can be used to equivocate game modes with the
 associated keypresses used to inititate them.*/

    INIT,
    MENU,
    NEW = 'n',
    CONTINUE = 'c',
    PLAY,
    EXIT = 'e'
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

#endif //RIOT_EXEC
