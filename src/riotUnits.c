#include "riotUnits.h"

void inmateDestroy(struct Inmate *inmateList, int position) {
    struct Inmate * nextInmate;
    struct Inmate * temp;
    int i;

    nextInmate = inmateList;
    for (i=0; i<position-1; i++) {
        nextInmate = nextInmate->next;
    }

    //undrawUnit(nextInmate->next->position);

    temp = nextInmate->next;
    nextInmate->next = nextInmate->next->next;
    //destroy(temp);

}
_Bool unitAdd(char Inmatetype) {
    struct Inmate * nextInmate;
    struct Inmate * inmateToAdd;

    inmateToAdd = (struct Inmate*)malloc(sizeof(struct Inmate));
    inmateToAdd->type = Inmatetype;

    while(nextInmate->next != NULL) {
        nextInmate = nextInmate->next;
    }
    nextInmate->next = inmateToAdd;

    //inmateDraw(inmateToAdd->position,inmateToAdd->type);

    return true;
}
/*Move inmate every turn by its speed*/
void inmateMove(struct Inmate *inmate) {
    int prevPos;
    struct Inmate * nextInmate;

    nextInmate = inmate;
    while(nextInmate->next != NULL) {
        prevPos = inmate->position;
        /*The idea here is that the position changes every turn
          by a fraction of the maximum speed, meaning a unit with
          speed 8 (highest speed) will move one unit every turn
          and a unit with speed 4 will move one unit every 2 turns
          ,the position is typecasted to an int that way the
           decimal place is truncated, meaning the position will
          be redrawn if a units position changes by a whole unit*/
        inmate->position = inmate->position + inmate->speed/8;
        /* inmateRedraw(int previousPosition, int currentPosition, char type) is
           a function which should be located inside the UI source file*/

        //inmateRedraw(prevPos,(int)inmate->position,inmate->type);
        nextInmate = nextInmate->next;
    }
}
/*Compare the positions of every inmate, and the positions of attack of every guard
  if the units position matches the area of attack of the guard than subtract its
  health by the guards damage*/
void guardAttack(struct Guard * guard,struct Inmate *inmate) {
    int i;
    int range;
    struct Inmate * nextInmate;
    struct Guard * nextGuard;

    nextGuard = guard;
    nextInmate = inmate;
    while(nextGuard->next != NULL) {
        /*Get the unit range*/
        range = sizeof(nextGuard->range)/sizeof(short);
        while(nextInmate->next != NULL) {
            for (i=0; i<range; i++) {
                if (nextGuard->range[i] == nextInmate->position) {
                    nextInmate->healthCur = nextInmate->healthCur - nextGuard->damage;
                }
            }
            nextInmate = nextInmate->next;
        }
        nextGuard = nextGuard->next;
    }
}
