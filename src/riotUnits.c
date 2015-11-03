#include "riotUnits.h"



struct UnitList *createList(void) {

    struct UnitList *newList = malloc(sizeof(struct UnitList));

    newList->count = 0;
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}


void destroyList(struct UnitList *listIn) {

    while (listIn->count)
        deleteFront(listIn);
    free(listIn);

    return;
}


bool isEmpty(struct UnitList *listIn) {

    bool eval = TRUE;

    if (listIn) {
        if (listIn->count)
            eval = FALSE;
    }

    return eval;

}


struct UnitNode * getHead(struct UnitList *listIn) {
    return listIn ? listIn->head : NULL;
}


struct UnitNode * getTail(struct UnitList *listIn) {
    return listIn? listIn->tail: NULL;
}



short getLength(struct UnitList *listIn) {
    return listIn ? listIn->count : (short)-1;
}



void insertFront(struct UnitList *listIn, struct UnitNode *unit) {

        struct UnitNode *newNode = NULL;

        newNode = malloc(sizeof(struct UnitNode));

        if (listIn->count) {
            newNode->next = listIn->head;
            newNode->prev = NULL;
            listIn->head = newNode;
            listIn->head->next->prev = newNode;

        } else {
            listIn->head = newNode;
            listIn->tail = newNode;
            newNode->next = NULL;
            newNode->prev = NULL;
        }

        listIn->count++;

        return;
    }


void insertBack(struct UnitList *listIn, struct UnitNode *unit) {

        struct UnitNode *newNode = malloc(sizeof(struct UnitNode));

        if (listIn->count) {
            listIn->tail->next = newNode;
            newNode->prev = listIn->tail;
            newNode->next = NULL;
            listIn->tail = newNode;
            listIn->tail->prev->next = newNode;

        } else {
            listIn->head = newNode;
            listIn->tail = newNode;
            newNode->next = NULL;
            newNode->prev = NULL;
        }

        listIn->count++;

        return;
    }


void deleteFront(struct UnitList *listIn) {

        struct UnitNode *tempNode;

        if (listIn->count) {
            tempNode = listIn->head->next;
            free(listIn->head);
            listIn->count--;
            listIn->head = tempNode;
        }

        if (listIn->head)
            listIn->head->prev = NULL;

        return;
    }



void deleteBack(struct UnitList *listIn) {

        struct UnitNode *tempNode;

        if (listIn->count) {
            tempNode = listIn->tail->prev;
            free(listIn->tail);
            listIn->count--;
            listIn->tail = tempNode;
        }

        if (listIn->head)
            listIn->tail->next = NULL;

        return;
    }


void printList(struct UnitList* list) {

    int i;
    struct UnitNode *node = list->head;

    for (i = 0; i < list->count; i++) {

        //printf...
        node = node->next;
    }

    return;
}


void inmateDestroy(struct UnitNode *inmateList, int position) {
    struct UnitNode * nextInmate;
    struct UnitNode * temp;
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


//bool unitAdd(char Inmatetype) {
//    struct UnitNode * nextInmate;
//    struct UnitNode * inmateToAdd;
//
//    inmateToAdd = (struct UnitNode *)malloc(sizeof(struct UnitNode));
//    inmateToAdd->type = Inmatetype;
//
//    while(nextInmate->next != NULL) {
//        nextInmate = nextInmate->next;
//    }
//    nextInmate->next = inmateToAdd;
//
//    //inmateDraw(inmateToAdd->position,inmateToAdd->type);
//
//    return true;
//}

///*Move inmate every turn by its speed*/
//void inmateMove(struct UnitNode *inmate) {
//    int prevPos;
//    struct InmateNode * nextInmate;
//
//    nextInmate = inmate;
//    while(nextInmate->next != NULL) {
//        prevPos = inmate->position;
//        /*The idea here is that the position changes every turn
//          by a fraction of the maximum speed, meaning a unit with
//          speed 8 (highest speed) will move one unit every turn
//          and a unit with speed 4 will move one unit every 2 turns
//          ,the position is typecasted to an int that way the
//           decimal place is truncated, meaning the position will
//          be redrawn if a units position changes by a whole unit*/
//        inmate->position = inmate->position + inmate->speed/8;
//        /* inmateRedraw(int previousPosition, int currentPosition, char type) is
//           a function which should be located inside the UI source file*/
//
//        //inmateRedraw(prevPos,(int)inmate->position,inmate->type);
//        nextInmate = nextInmate->next;
//    }
//}
///*Compare the positions of every inmate, and the positions of attack of every guard
//  if the units position matches the area of attack of the guard than subtract its
//  health by the guards damage*/
//void guardAttack(struct UnitNode *guard, struct UnitNode *inmate) {
//    int i;
//    int range;
//    struct InmateNode * nextInmate;
//    struct GuardNode * nextGuard;
//
//    nextGuard = guard;
//    nextInmate = inmate;
//    while(nextGuard->next != NULL) {
//        /*Get the unit range*/
//        range = sizeof(nextGuard->range)/sizeof(short);
//        while(nextInmate->next != NULL) {
//            for (i=0; i<range; i++) {
//                if (nextGuard->range[i] == nextInmate->position) {
//                    nextInmate->healthCur = nextInmate->healthCur - nextGuard->damage;
//                }
//            }
//            nextInmate = nextInmate->next;
//        }
//        nextGuard = nextGuard->next;
//    }
//}
