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

/* InmateType will allow for a bidirectional equivalence between unit types and
   their associated char values.*/
enum InmateType {
    HOMEBOY = 'h',
    BRUISER = 'b',
    LUNATIC = 'l',
    FATTY = 'f',
    SPEEDY = 's',
    CUTIE = 'c',
    ATTORNEY = 'a',
    DOCTOR = 'd'
};

enum GuardType {
    GUARD,
    DOGS,
    LUNCH, //lunch lady
    PSYCH, //psychiatrist
    SHARP, //sharpshooter
    WARDEN,
    CYBORG
};

enum AI {
    PROX, //proximity
    AOE, //area of effect
    END //closest to end
};

enum Colour {
    GREEN,
    YELLOW,
    ORANGE,
    RED
};

enum GameMode {
    INIT,
    MENU,
    NEW = 'n',
    CONTINUE = 'c',
    PLAY,
    EXIT = 'e'
};


/* Function Prototypes */

void quit(char *message);

#endif
