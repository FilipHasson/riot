#ifndef RIOT_UNITS
#define RIOT_UNITS

#include "riotExec.h"


/* Data Types */

struct UnitList {
    struct UnitNode* head;
    struct UnitNode* tail;
    short count;
};


struct UnitNode {/*

 UnitNode stores variable unit stats.*/

    enum UnitType type;
    short speed;
    short healthMax;
    short healthCur;
    short position;
    struct UnitNode *next;
    struct UnitNode *prev;
};


/* Function Prototypes */


struct UnitList* createList(void);

void destroyList(struct UnitList*);

short getLength(struct UnitList*);

bool isEmpty(struct UnitList *);

struct UnitNode* getHead(struct UnitList*);

struct UnitNode* getTail(struct UnitList*);

void insertFront(struct UnitList *listIn, struct UnitNode *unit);

void insertBack(struct UnitList *listIn, struct UnitNode *unit);

void deleteFront(struct UnitList*);

void deleteBack(struct UnitList*);

void printList(struct UnitList*);


void inmateDestroy(struct UnitNode *inmateList, int position);/*

DESCRIPTION: inmateDestroy() is used to remove a unit from the game.

ARGUMENTS: struct UnitNode *inmateList is the list of inmates present in
the game, this argument should be changed to a header node once one is
present.

int position is the position that the inmate should be removed from.

PRECONDITIONS: The position is within the size of the list.

POSTCONDITIONS: The inmate at position has been removed.*/


bool unitAdd(char inmateType);/*

DESCRIPTION: unitAdd() is used to add an inmate to the game.

ARGUMENTS: The character pressed by the user which corresponds to an
 associated unit type.

PRECONDITIONS: The character provided corresponds with an inmate type
 specified within the InmateNode enum.

POSTCONDITIONS: A UnitNode is added to the UnitList.*/


void inmateMove(struct UnitNode *inmate);/*

 DESCRIPTION: Move inmate every turn by its speed.*/


void guardAttack(struct UnitNode *guard, struct UnitNode *inmate);/*

 DESCRIPTION: Compares the positions of every inmate, and the positions of
 attack of every guard if the units position matches the area of attack of
 the guard than subtract its health by the guards damage*/


#endif //RIOT_UNITS
