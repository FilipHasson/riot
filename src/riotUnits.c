#define _DEFAULT_SOURCE

#include <ctype.h>
#include <time.h>
#include "riotUnits.h"
#include "riotUI.h"


void destroyList(struct UnitList *list) {

    struct UnitNode *tempNode = NULL;

    while (list->count) {
        tempNode = list->head->next;
        free(list->head);
        list->count--;
        list->head = tempNode;
    }
    free(list);

    return;
}


struct UnitNode *getNext(struct UnitNode *list) {
    return list ? list->next : NULL;
}


struct UnitNode *getHead(struct UnitList *listIn) {
    return listIn ? listIn->head : NULL;
}


struct UnitNode *getTail(struct UnitList *listIn) {
    return listIn ? listIn->tail : NULL;
}


int getLength(struct UnitList *listIn) {
    return listIn ? listIn->count : (int) -1;
}


struct UnitNode *enqueue(struct UnitList *queue, void *unit) {

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


struct UnitNode *dequeue(struct UnitList *queue) {

    struct UnitNode *tempNode, *request = NULL;

    if (queue->count) {
        tempNode = queue->tail->prev;
        request = queue->tail;
        queue->count--;
        queue->tail = tempNode;
    }

    if (queue->head)
        queue->head->prev = NULL;

    return request;
}


struct UnitNode *pop(struct UnitList *stack) {

    struct UnitNode *tempNode, *request = NULL;

    if (stack->count) {
        tempNode = stack->head->next;
        request = stack->head;
        stack->count--;
        stack->head = tempNode;
    }

    if (stack->head)
        stack->head->prev = NULL;

    return request;
}


void rmUnit(struct UnitNode *target) {
    free(target->unit);
    free(target);
    return;
}


struct Inmate *createInmate(enum InmateType type) {

    struct Inmate *unit = malloc(sizeof(struct Inmate));

    unit->type = type;
    unit->position = -1;

    switch (type) {

        case PROTAGONIST:
            unit->currentHealth = unit->maxHealth = 5;
            unit->speed = 2;
            unit->rep = 0;
            unit->panic = 0;
            unit->delUnit = FALSE;
            break;

        case HOMEBOY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 4;
            unit->rep = 5;
            unit->panic = 2;
            unit->delUnit = FALSE;
            break;

        case BRUISER:
            unit->currentHealth = unit->maxHealth = 16;
            unit->speed = 4;
            unit->rep = 15;
            unit->panic = 6;
            unit->delUnit = FALSE;
            break;

        case LUNATIC:
            unit->currentHealth = unit->maxHealth = 16;
            unit->speed = 6;
            unit->rep = 10;
            unit->panic = 8;
            unit->delUnit = FALSE;
            break;

        case FATTY:
            unit->currentHealth = unit->maxHealth = 40;
            unit->speed = 2;
            unit->rep = 10;
            unit->panic = 4;
            unit->delUnit = FALSE;
            break;

        case SPEEDY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 8;
            unit->rep = 20;
            unit->panic = 2;
            unit->delUnit = FALSE;
            break;

        case CUTIE:
            unit->currentHealth = unit->maxHealth = 20;
            unit->speed = 4;
            unit->rep = 20;
            unit->panic = 1;
            unit->delUnit = FALSE;
            break;

        case ATTORNEY:
            unit->currentHealth = unit->maxHealth = 30;
            unit->speed = 4;
            unit->rep = 30;
            unit->panic = 2;
            unit->delUnit = FALSE;
            break;

        case DOCTOR:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 4;
            unit->rep = 40;
            unit->panic = 2;
            unit->delUnit = FALSE;
            break;

        default:
            quit("Creating unsupported unit type.");
            break;
    }

    return unit;
}


struct Guard *createGuard(enum GuardType type) {

    struct Guard *guard = malloc(sizeof(struct Guard));

    guard->type = type;
    guard->position = -1;

    switch (type) {

        case GUARD:
            guard->damage = 5;
            guard->range = 2;
            guard->cooldown = 4;
            guard->ai = PROX;
            break;

        case DOGS:
            guard->damage = 4;
            guard->range = 4;
            guard->cooldown = 6;
            guard->ai = AOE;
            break;

        case LUNCH:
            guard->damage = 0;
            guard->range = 6;
            guard->cooldown = 12;
            guard->ai = AOE;
            break;

        case PSYCH:
            guard->damage = 0;
            guard->range = 6;
            guard->cooldown = 12;
            guard->ai = PROX;
            break;

        case SHARP:
            guard->damage = 6;
            guard->range = 10;
            guard->cooldown = 8;
            guard->ai = END;
            break;

        case WARDEN:
            guard->damage = 100;
            guard->range = 8;
            guard->cooldown = 2;
            guard->ai = PROX;
            break;

        case CYBORG:
            guard->damage = 12;
            guard->range = 8;
            guard->cooldown = 2;
            guard->ai = PROX;
            break;

        default:
            quit("Creating unsupported unit type.");
            break;
    }

    return guard;
}


bool simulate(struct Windows *gameInterface,
    struct UnitList *guardList, struct UnitList *inmateList,
    struct Path *path) {

    struct UnitNode *nextInmate;
    float simulateTime = 0;
    int prevPos[inmateList->count];
    struct timespec delay;

    delay.tv_sec = 0;
    delay.tv_nsec = 50000000L;  // Half second in nano seconds

    while (simulateTime < 40) {

        nextInmate = getHead(inmateList);
        for (int i = 0; i < inmateList->count; i++) {
            prevPos[i] = ((struct Inmate *) nextInmate->unit)->position;
            nextInmate = nextInmate->next;
        }

        inmateMove(inmateList, path);
        //guardAttack(guardList, inmateList);
        nextInmate = getHead(inmateList);

        for (int i = 0; i < inmateList->count; i++) {
            if (((struct Inmate *) nextInmate->unit)->delUnit == FALSE)
                redrawUnit(gameInterface->body,
                    (struct Inmate *) nextInmate->unit, path, prevPos[i]);
            else {
                /*Call redraw but delete it?, or simply call eraseUnit in UI*/
                dequeue(inmateList);
            }
            nextInmate = nextInmate->next;
        }
        simulateTime += .25;
        wrefresh(gameInterface->body);
        nanosleep(&delay, NULL);
    }

    return true;  //TODO return win condition

}


/*Moves the units through the map and calls 'inmateRedraw to draw/erase the
 units*/
void inmateMove(struct UnitList *inmateList, struct Path *path) {
    struct UnitNode *nextInmate;
    struct TileNode *nextTile;
    int prevPos;

    nextInmate = getHead(inmateList);
    do {
        nextTile = path->first;
        for (int i = 0; i < path->count; i++) {
            if (nextTile->location ==
                (int) ((struct Inmate *) nextInmate->unit)->position)
                break;
            nextTile = nextTile->next;
        }
        prevPos = ((struct Inmate *) nextInmate->unit)->position;
        ((struct Inmate *) nextInmate->unit)->position =
            ((struct Inmate *) nextInmate->unit)->position +
                (float) ((struct Inmate *) nextInmate->unit)->speed / 8;
        if ((int) ((struct Inmate *) nextInmate->unit)->position ==
            prevPos + 1 && nextTile->next != NULL)
            ((struct Inmate *) nextInmate->unit)->position = nextTile->next->location;
        else if ((int) ((struct Inmate *) nextInmate->unit)->position ==
            prevPos + 1 && nextTile->next == NULL) {
            ((struct Inmate *) nextInmate->unit)->delUnit = TRUE;
            //endwin();
        }
        nextInmate = getNext(nextInmate);
    } while (getNext(nextInmate));
}


void guardAttack(struct UnitList *guardList, struct UnitList *inmateList) {
    struct UnitNode *nextInmate;
    struct UnitNode *nextGuard;

    nextGuard = getHead(guardList);
    nextInmate = getHead(inmateList);

    do {
        do {
            if (inRange(nextInmate, nextGuard))
                dealDamage(nextInmate, nextGuard);
            nextInmate = getNext(nextInmate);
        } while (getNext(nextInmate) != NULL);
        nextGuard = getNext(nextGuard);
    } while (getNext(nextGuard) != NULL);
}


void dealDamage(struct UnitNode *inmateNode, struct UnitNode *guardNode) {
    ((struct Inmate *) inmateNode->unit)->currentHealth =
        ((struct Inmate *) inmateNode->unit)->currentHealth -
            ((struct Guard *) guardNode->unit)->damage;
}


bool inRange(struct UnitNode *inmate, struct UnitNode *guard) {
    int inmatePosition;
    int guardPosition;
    int range;
    int xDifference;
    int yDifference;
    int totalDifference;

    inmatePosition = ((struct Inmate *) inmate->unit)->position;
    guardPosition = ((struct Guard *) guard->unit)->position;
    range = ((struct Guard *) guard->unit)->range;

    yDifference = (((inmatePosition - 1) / MAX_COLS) + 1) -
        -
            (((guardPosition - 1) / MAX_COLS) + 1);
    xDifference = (guardPosition + (yDifference * MAX_COLS)) - inmatePosition;
    yDifference = abs(yDifference);
    xDifference = abs(xDifference);
    totalDifference = xDifference + yDifference;

    return range >= totalDifference;
}


void getGuards(struct UnitList *guards, struct Map map) {

    struct Guard *guard;
    int i, j, position;
    char mapChar;

    /* Initialize guards list */
    guards->count = 0;
    guards->head = NULL;
    guards->tail = NULL;

    /* Get guards */
    for (i = 0; i < MAP_ROWS; i++) {
        for (j = 0; j < MAP_COLS; j++) {
            position = (i * MAP_COLS) + j;
            mapChar = toupper(map.overlay[i][j]);
            if (isalpha(mapChar)) {
                guard = createGuard(mapChar);
                guard->position = position;
                enqueue(guards, guard);
            }
        }
    }

    return;
}

