#include "riotUnits.h"

void inmateMove(struct Inmate *inmate) {

    short prevPos;
    struct Inmate *nextInmate;

    nextInmate = inmate;

    while (nextInmate->next) {
        prevPos = inmate->position; //never used?

        /*The idea here is that the position changes every turn by a fraction
          of the maximum speed, meaning a unit with speed 8 (highest speed)
          will move one unit every turn and a unit with speed 4 will move one
          unit every 2 turns ,the position is typecasted to an int that way
          the decimal place is truncated, meaning the position will be redrawn
          if a units position changes by a whole unit*/

        inmate->position += inmate->speed / 8;

        /* inmateRedraw(int previousPosition, int currentPosition, char type)
           is a function which should be located inside the UI source file*/

        // inmateRedraw(prevPos, (int) inmate->position, inmate->type); //?
        nextInmate = nextInmate->next;
    }

}


void guardAttack(struct Guard *guard, struct Inmate *inmate) {

    int i;
    int range;
    struct Inmate *nextInmate;
    struct Guard *nextGuard;

    nextGuard = guard;
    nextInmate = inmate;

    while (nextGuard->next) {

        /*Get the unit range*/
        range = sizeof(nextGuard->range) / sizeof(short);

        while (nextInmate->next) {

            for (i = 0; i < range; i++) {
                if (nextGuard->range[i] == nextInmate->position) {
                    nextInmate->healthCur =
                        nextInmate->healthCur - nextGuard->damage;
                }
            }
            nextInmate = nextInmate->next;
        }
        nextGuard = nextGuard->next;
    }

}
