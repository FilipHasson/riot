#ifndef RIOT_UNITS
#define RIOT_UNITS

#include "riotExec.h"


/* Data Types */

struct UnitList {/*

 UnitList stores the head, tail, and count of a doubly linked list of
 UnitNodes.*/

    struct UnitNode *head;
    struct UnitNode *tail;
    short count;
};


struct UnitNode {/*

UnitNode stores the information related to inmate units.*/

    void *unit;
    struct UnitNode *next;
    struct UnitNode *prev;
};


struct Inmate {/*

 Inmate stores the stats related to inmate units.*/

    char type;
    short position;
    unsigned short currentHealth;
    unsigned short maxHealth;
    unsigned short speed;
    unsigned short rep;
    unsigned short panic;
};


struct Guard {/*

 Inmate stores the stats related to guard units.*/

    char type;
    short position;
    unsigned short damage;
    unsigned short range;
    unsigned short cooldown;
    enum AI ai;

};


/* Linked UnitList Operations */

struct UnitList *createList(void);/*

DESCRIPTION: createList() is used to allocate memory for a UnitList struct.
 Initializes values to NULL or 0.

POSTCONDITIONS: Memory is allocated for a UnitList, the address for which is
 returned by the function.*/


void destroyList(struct UnitList *);/*

DESCRIPTION: destroyList() is used to deallocate memory for a UnitList struct.

ARGUMENTS: A Pointer to the UnitList to be destroyed.

POSTCONDITIONS: Each node listed within the UnitList is destroyed and the
 memory used for it is returned to the calling OS.*/


short getLength(struct UnitList *);/*

DESCRIPTION: getLength() is used to get the number of nodes containted within
 a UnitList.

ARGUMENTS: The UnitList to be examined.

POSTCONDITIONS: Will return a short value corresponding to the number of
 UnitNodes contained withing the UnitList*/


bool isEmpty(struct UnitList *);/*

DESCRIPTION: isEmpty() is used to determine whether a UnitList has been
 initialized and is capable of storing UnitNodes.

ARGUMENTS: The UnitList to be examined.

PRECONDITIONS: The position is within the size of the list.

POSTCONDITIONS: Will return TRUE is empty, otherwide FALSE.*/


struct UnitNode *getHead(struct UnitList *);/*

DESCRIPTION: getHead() is used to get a pointer to the first UnitNode stored
 within the UnitList.

ARGUMENTS: The UnitList to be querried.

POSTCONDITIONS: Will return a pointer to the UnitNode, else NULL.*/


struct UnitNode *getTail(struct UnitList *);/*

DESCRIPTION: getTail() is used to get a pointer to the last UnitNode stored
 within the UnitList.

ARGUMENTS: The UnitList to be querried.

POSTCONDITIONS: Will return a pointer to the UnitNode, else NULL.*/


/* Linked UnitList Interfaces */

struct UnitNode *enqueue(struct UnitList *queue, void *unit);/*

DESCRIPTION: enqueue() will store any data type (presumably either an Inmate
 or Guard type) at the back of a UnitList.

ARGUMENTS: The list to be extended and a pointer to the data to be added.

POSTCONDITIONS: Will store either the newly created UnitStore cointaing the
 unit within it's data member or NULL if not possible.*/


struct UnitNode *dequeue(struct UnitList *queue);/*

DESCRIPTION: dequeue() will remove the front UnitNode of the passed UnitList.
 Memory is not freed by this funtion-- either its returned UnitNode will need
 to be freed by rmUnit or enqueued in a seperate UnitList which can later be
 destroyed.

ARGUMENTS: The list to be modified.

POSTCONDITIONS: The front UnitNode is either removed from the passed UnitList
 and its pointer is returned, else NULL is returned.*/


struct UnitNode *pop(struct UnitList *stack);/*

DESCRIPTION: pop() will remove the back UnitNode of the passed UnitList.
 Memory is not freed by this funtion-- either its returned UnitNode will need
 to be freed by rmUnit or enqueued in a seperate UnitList which can later be
 destroyed.

ARGUMENTS: The list to be modified.

POSTCONDITIONS: The back UnitNode is either removed from the passed UnitList
 and its pointer is returned, else NULL is returned.*/


/* Function Prototypes */

struct Inmate *createInmate(enum InmateType type);

struct Guard *createGuard(enum GuardType type);


void rmUnit(struct UnitNode* target);/*

DESCRIPTION: inmateRm() is used to remove a unit from the game.

ARGUMENTS: struct UnitNode *inmateList is the list of inmates present in
the game, this argument should be changed to a header node once one is
present.

PRECONDITIONS: The position is within the size of the list.

POSTCONDITIONS: The inmate at position has been removed.*/


struct Inmate *createInmate(enum InmateType type);/*

DESCRIPTION: createInmate() is used initialize a new inmate with its
 associated base stats.

ARGUMENTS: an InmateType enum associated with the Inmate to be initiated.

PRECONDITIONS: The enum value is a valid inmate type.

POSTCONDITIONS: Memory is allocated for a new Inmate struct.*/


void inmateMove(struct UnitNode *inmate);/*

 DESCRIPTION: Move inmate every turn by its speed.*/


void guardAttack(struct UnitList * guardList, struct UnitList *inmateList);/*

 DESCRIPTION: Compares the positions of every inmate, and the positions of
 attack of every guard if the units position matches the area of attack of
 the guard than subtract its health by the guards damage*/

bool inRange(int rowSize,struct UnitNode *inmate,struct UnitNode *guard);

void dealDamage(struct UnitNode * inmateNode,struct UnitNode * guardNode);

void removeHealth(struct Inmate *inmate,int damage,int rowSize);
#endif //RIOT_UNITS
