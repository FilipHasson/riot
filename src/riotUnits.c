#include "riotUnits.h"


struct List *createList(void) {

    struct List *newList = malloc(sizeof(struct List));

    newList->count = 0;
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}


void destroyList(struct List *listIn) {

    struct UnitNode *tempNode = NULL;

    while (listIn->count) {
        tempNode = listIn->head->next;
        free(listIn->head);
        listIn->count--;
        listIn->head = tempNode;
    }
    free(listIn);

    return;
}


bool isEmpty(struct List *listIn) {

    bool eval = TRUE;

    if (listIn) {
        if (listIn->count)
            eval = FALSE;
    }

    return eval;

}


struct UnitNode *getHead(struct List *listIn) {
    return listIn ? listIn->head : NULL;
}


struct UnitNode *getTail(struct List *listIn) {
    return listIn ? listIn->tail : NULL;
}


short getLength(struct List *listIn) {
    return listIn ? listIn->count : (short) -1;
}

struct UnitNode * enqueue(struct List *queue, void *unit){

    struct UnitNode *newNode = malloc(sizeof(struct UnitNode));
    newNode->unit = unit;

    if (queue->count) {
        newNode->next = queue->head;
        newNode->prev = NULL;
        queue->head = newNode;
        queue->head->next->prev = newNode;

    } else {
        queue->head = newNode;
        queue->tail = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
    }

    queue->count++;

    return newNode;

}


struct UnitNode * dequeue(struct List *queue){

    struct UnitNode *tempNode, *request = NULL;

    if (queue->count) {
        tempNode = queue->tail->prev;
        request = queue->tail;
        queue->count--;
        queue->tail = tempNode;
    }

    if (queue->head) {
        queue->head->prev = NULL;
    }

    return request;
}

struct UnitNode * pop(struct List *stack){

    struct UnitNode *tempNode, *request = NULL;

    if (stack->count) {
        tempNode = stack->head->next;
        request = stack->head;
        stack->count--;
        stack->head = tempNode;
    }

    if (stack->head) {
        stack->head->prev = NULL;
    }

    return request;
}



void printGuards(struct List* list){

    int i;
    struct UnitNode *node = list->head;
    struct Inmate* inmate;

    for (i = 0; i < list->count; i++) {

        inmate = node->unit;
        printf("Inmate #%d\n",i+1);
        printf("type: %c\n",inmate->type);
        printf("curHealth: %d\n",inmate->healthCur);
        printf("maxHealth: %d\n",inmate->healthMax);
        printf("position: %d\n",inmate->position);
        printf("repCost: %d\n",inmate->repCost);
        printf("speed: %d\n",inmate->speed);
        printf("\n");
    }

    return;
}

void printInmates(struct List* list){

    int i;
    struct UnitNode *node = list->head;
    struct Guard* guard;

    for (i = 0; i < list->count; i++) {

        guard = node->unit;
        printf("Guard #%d\n",i+1);
        printf("type: %c\n",guard->type);
        printf("ai: %d\n",guard->ai);
        printf("damage: %d\n",guard->damage);
        printf("range: %d\n",guard->range);
        printf("\n");
    }

    return;
}

//
//
//void inmateDestroy(struct UnitNode *inmateList, int position) {
//    struct UnitNode *nextInmate;
//    struct UnitNode *temp;
//    int i;
//
//    nextInmate = inmateList;
//    for (i = 0; i < position - 1; i++) {
//        nextInmate = nextInmate->next;
//    }
//
//    //undrawUnit(nextInmate->next->position);
//
//    temp = nextInmate->next;
//    nextInmate->next = nextInmate->next->next;
//    //destroy(temp);
//}
//

bool createUnit(enum UnitType type) {

    struct UnitNode * unit;

    /* If adding guard unit */
    if (type > _GUARDS) {

        switch(type){

            case GUARD:

                break;

            case DOGS:
                break;

            case LUNCH:
                break;

            case PSYCH:
                break;

            case SHARP:
                break;

            case WARDEN:
                break;

            case CYBORG:
                break;

            default:
                quit("Creating unsupported unit type.");
                break;

        }

    /* If adding inmate unit */
    } else {


    }
    return true;
}

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
