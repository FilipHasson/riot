#ifndef RIOT_COMMON
#define RIOT_COMMON

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Macro Constants */

#define SIZE_X 80
#define SIZE_Y 24
#define HEADER 3
#define FOOTER 4
#define MAIN 16


/* Data Types */

enum InmateType {/*

 InmateType is a mnemonic which can be used to equivocate inmate types with
 the associated keypresses used to spawn them.*/

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
    END //closest to end
};


enum Colour {/*

 Colour provides a mnemonic for the colours used to convey health values.*/

    GREEN,
    YELLOW,
    ORANGE,
    RED
};


enum GameMode {/*

 GameMode is a mnemonic which can be used to equivocate game modes with
 the associated keypresses used to inititate them.*/

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



#endif //RIOT_COMMON
