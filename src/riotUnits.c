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

struct UnitNode *enqueue(struct List *queue, void *unit) {

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


struct UnitNode *dequeue(struct List *queue) {

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

struct UnitNode *pop(struct List *stack) {

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


void printGuards(struct List *list) {

    int i;
    struct UnitNode *node = list->head;
    struct Inmate *inmate;

    for (i = 0; i < list->count; i++) {

        inmate = node->unit;
        printf("Inmate #%d\n", i + 1);
        printf("type: %c\n", inmate->type);
        printf("pos: %d\n", inmate->position);
        printf("curHealth: %d\n", inmate->health[0]);
        printf("maxHealth: %d\n", inmate->health[1]);
        printf("speed: %d\n", inmate->speed);
        printf("rep: %d\n", inmate->rep);
        printf("panic: %d\n", inmate->panic);
        printf("\n");
    }

    return;
}

void printInmates(struct List *list) {

    int i;
    struct UnitNode *node = list->head;
    struct Guard *guard;

    for (i = 0; i < list->count; i++) {

        guard = node->unit;
        printf("Guard #%d\n", i + 1);
        printf("type: %c\n", guard->type);
        printf("pos: %d\n", guard->position);
        printf("damage: %d\n", guard->damage);
        printf("range: %d\n", guard->range);
        printf("cooldown: %d\n", guard->cooldown);
        printf("ai: %d\n", guard->ai);
        printf("\n");
    }

    return;
}

//
//
//void inmateRm(struct UnitNode *inmateList, int position) {
//    struct UnitNode *nextInmate;
//    struct UnitNode *temp;
//    int i;
//
//    nextInmate = inmateList;
//    for (i = 0; i < position - 1; i++) {
//        nextInmate = nextInmate->next;
//    }
//
//    //undrawUnit(nextInmate->next->pos);
//
//    temp = nextInmate->next;
//    nextInmate->next = nextInmate->next->next;
//    //destroy(temp);
//}
//

struct Inmate *addInmate(enum InmateType type) {

    struct Inmate *unit = malloc(sizeof(struct Inmate));

    unit->type = type;
    unit->position = -1;

    switch (type) {

        case PROTAGONIST:
            unit->health[0] = unit->health[1] = 5;
            unit->speed = 2;
            unit->rep = 0;
            unit->panic = 0;
            break;

        case HOMEBOY:
            unit->health[0] = unit->health[1] = 10;
            unit->speed = 4;
            unit->rep = 5;
            unit->panic = 2;
            break;

        case BRUISER:
            unit->health[0] = unit->health[1] = 16;
            unit->speed = 4;
            unit->rep = 15;
            unit->panic = 6;
            break;

        case LUNATIC:
            unit->health[0] = unit->health[1] = 16;
            unit->speed = 6;
            unit->rep = 10;
            unit->panic = 8;
            break;

        case FATTY:
            unit->health[0] = unit->health[1] = 40;
            unit->speed = 2;
            unit->rep = 10;
            unit->panic = 4;
            break;

        case SPEEDY:
            unit->health[0] = unit->health[1] = 10;
            unit->speed = 8;
            unit->rep = 20;
            unit->panic = 2;
            break;

        case CUTIE:
            unit->health[0] = unit->health[1] = 20;
            unit->speed = 4;
            unit->rep = 20;
            unit->panic = 1;
            break;

        case ATTORNEY:
            unit->health[0] = unit->health[1] = 10;
            unit->speed = 5;
            unit->rep = 40;
            unit->panic = 2;
            break;

        case DOCTOR:
            unit->health[0] = unit->health[1] = 0;
            unit->speed = 0;
            unit->rep = 0;
            unit->panic = 0;
            break;

        default:
            quit("Creating unsupported unit type.");
            break;
    }

    return unit;
}


struct Guard *addGuard(enum GuardType type) {

    struct Guard *unit = malloc(sizeof(struct Guard));

    unit->type = type;
    unit->position = -1;

    switch (type) {

        case GUARD:
            unit->damage = 5;
            unit->range = 2;
            unit->cooldown = 4;
            unit->ai = PROX;
            break;

        case DOGS:
            unit->damage = 4;
            unit->range = 4;
            unit->cooldown = 6;
            unit->ai = AOE;
            break;

        case LUNCH:
            unit->damage = 0;
            unit->range = 6;
            unit->cooldown = 12;
            unit->ai = AOE;
            break;

        case PSYCH:
            unit->damage = 0;
            unit->range = 6;
            unit->cooldown = 12;
            unit->ai = PROX;
            break;

        case SHARP:
            unit->damage = 6;
            unit->range = 10;
            unit->cooldown = 8;
            unit->ai = END;
            break;

        case WARDEN:
            unit->damage = 100;
            unit->range = 8;
            unit->cooldown = 2;
            unit->ai = PROX;
            break;

        case CYBORG:
            unit->damage = 12;
            unit->range = 8;
            unit->cooldown = 2;
            unit->ai = PROX;
            break;

        default:
            quit("Creating unsupported unit type.");
            break;
    }

    return unit;
}

///*Move inmate every turn by its speed*/
//void inmateMove(struct UnitNode *inmate) {
//    int prevPos;
//    struct InmateNode * nextInmate;
//
//    nextInmate = inmate;
//    while(nextInmate->next != NULL) {
//        prevPos = inmate->pos;
//        /*The idea here is that the position changes every turn
//          by a fraction of the maximum speed, meaning a unit with
//          speed 8 (highest speed) will move one unit every turn
//          and a unit with speed 4 will move one unit every 2 turns
//          ,the position is typecasted to an int that way the
//           decimal place is truncated, meaning the position will
//          be redrawn if a units position changes by a whole unit*/
//        inmate->pos = inmate->pos + inmate->speed/8;
//        /* inmateRedraw(int previousPosition, int currentPosition, char type) is
//           a function which should be located inside the UI source file*/
//
//        //inmateRedraw(prevPos,(int)inmate->pos,inmate->type);
//        nextInmate = nextInmate->next;
//    }
//}
///*Compare the positions of every inmate, and the positions of attack of every guard
//  if the units pos matches the area of attack of the guard than subtract its
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
//                if (nextGuard->range[i] == nextInmate->pos) {
//                    nextInmate->hpCur = nextInmate->hpCur - nextGuard->damage;
//                }
//            }
//            nextInmate = nextInmate->next;
//        }
//        nextGuard = nextGuard->next;
//    }
//}
