#ifndef RIOT_UNITS
#define RIOT_UNITS

#include "riotExec.h"


/* Data Types */

struct List {
    struct UnitNode *head;
    struct UnitNode *tail;
    short count;
};

struct UnitNode {
    void *unit;
    struct UnitNode *next;
    struct UnitNode *prev;
};

struct Inmate {
    /*
     Inmate stores the information related to inmate units.*/

    char type;
    short speed;
    short healthMax;
    short healthCur;
    char repCost;
    short position;

} Inmate;


struct Guard {
    /*
     Inmate stores the information related to guard units.*/

    char type;
    enum AI ai;
    short damage;
    short range;
} Guard;


/* Linked List Operations */

struct List *createList(void);

void destroyList(struct List *);

short getLength(struct List *);

bool isEmpty(struct List *);

struct UnitNode *getHead(struct List *);

struct UnitNode *getTail(struct List *);

void printGuards(struct List *);

void printInmates(struct List *);


/* Linked List Interfaces */

struct UnitNode *enqueue(struct List *queue, void *unit);

struct UnitNode *dequeue(struct List *queue);

struct UnitNode *pop(struct List *stack);



/* Function Prototypes */


void inmateDestroy(struct UnitNode *inmateList, int position);/*

DESCRIPTION: inmateDestroy() is used to remove a unit from the game.

ARGUMENTS: struct UnitNode *inmateList is the list of inmates present in
the game, this argument should be changed to a header node once one is
present.

int position is the position that the inmate should be removed from.

PRECONDITIONS: The position is within the size of the list.

POSTCONDITIONS: The inmate at position has been removed.*/


bool unitAdd(char inmateType);

/*

DESCRIPTION: unitAdd() is used to add an inmate to the game.

ARGUMENTS: The character pressed by the user which corresponds to an
 associated unit type.

PRECONDITIONS: The character provided corresponds with an inmate type
 specified within the InmateNode enum.

POSTCONDITIONS: A UnitNode is added to the List.*/


void inmateMove(struct UnitNode *inmate);

/*

 DESCRIPTION: Move inmate every turn by its speed.*/


void guardAttack(struct UnitNode *guard, struct UnitNode *inmate);/*

 DESCRIPTION: Compares the positions of every inmate, and the positions of
 attack of every guard if the units position matches the area of attack of
 the guard than subtract its health by the guards damage*/


#endif //RIOT_UNITS
