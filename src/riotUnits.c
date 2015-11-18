#include <ctype.h>
#include <unistd.h>
#include "riotUnits.h"
#include "riotUI.h"

static void writeToFile(char *message){
    FILE * file = fopen("test.txt","a");

    fprintf(file,"%s\n",message);

    fclose(file);
}

struct UnitList *createList(void) {

    struct UnitList *newList = malloc(sizeof(struct UnitList));

    newList->count = 0;
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}


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


bool isEmpty(struct UnitList *list) {

    bool eval = TRUE;

    if (list) {
        if (list->count)
            eval = FALSE;
    }

    return eval;

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

void runSimulation(struct Interface *gameInterface, struct UnitList *guardList, struct UnitList *inmateList,
    struct Path *path) {
    struct UnitNode *nextInmate;
    float simulateTime = 0;
    int prevPos[inmateList->count];
    char printstring[100];
    while (simulateTime < 30) {

    	nextInmate = getHead(inmateList);
    	for (int i=0;i<inmateList->count;i++){
            prevPos[i] = ((struct Inmate*)nextInmate->unit)->position;
            nextInmate = nextInmate->next;
        }

        inmateMove(inmateList, path);
        guardAttack(guardList, inmateList);
        
        nextInmate = getHead(inmateList);
        for (int i=0;i<inmateList->count;i++){
            redrawUnit(gameInterface->body,(struct Inmate*)nextInmate->unit,path,prevPos[i]);
            /*
            sprintf(printstring, "position %f", ((struct Inmate*)nextInmate->unit)->position);
      	    writeToFile(printstring);*/
            nextInmate = nextInmate->next;
        }
        simulateTime += .25;
        wrefresh(gameInterface->body);
        usleep(25000);
    }
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
            if (nextTile->location == (int)((struct Inmate *) nextInmate->unit)->position) {
                break;
            }
            nextTile = nextTile->next;
        }
        prevPos = ((struct Inmate *) nextInmate->unit)->position;
        ((struct Inmate *) nextInmate->unit)->position =
        ((struct Inmate *) nextInmate->unit)->position +
        (float)((struct Inmate *) nextInmate->unit)->speed / 8;
        if ((int)((struct Inmate *) nextInmate->unit)->position == prevPos + 1 /*&& nextTile->next->type == '.'*/) {
            ((struct Inmate *) nextInmate->unit)->position = nextTile->next->location;
        } else if ((int)((struct Inmate *) nextInmate->unit)->position == prevPos + 1 && nextTile->next->type == '&') {
        	((struct Inmate *) nextInmate->unit)->delUnit = TRUE;
        }
        nextInmate = getNext(nextInmate);
    } while (getNext(nextInmate) != NULL);
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
    ((struct Inmate *) inmateNode->unit)->currentHealth =((struct Inmate *) inmateNode->unit)->currentHealth -((struct Guard *) guardNode->unit)->damage;
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

struct UnitList *getGuardList(struct Map map){
    int i,j, position;
    char mapChar;
    struct Guard *insertGuard;
    struct UnitList *guardList;

    guardList = createList();

    for (i=0;i<MAP_ROWS;i++){
        for (j=0;j<MAP_COLS;j++){
            position = (i*MAP_COLS)+j;
            mapChar = toupper(map.overlay[i][j]);
            if (isalpha(mapChar)){
                insertGuard = createGuard(mapChar);
                insertGuard->position = position;
                enqueue(guardList,insertGuard);
            }
        }
    }

    return guardList;
}

struct Path *getPath(struct Map map) {
    struct Path *path = NULL;
    int i, j;
    int count=0;
    int position=0;
    int prevChecked[MAP_ROWS * MAP_COLS];

    for (int i = 0; i < (MAP_ROWS * MAP_COLS); i++) {
        prevChecked[i] = 0;
    }
    path = (struct Path *) malloc(sizeof(struct Path));
    path->count = 0;
    for (i = 0; i < MAP_ROWS; i++) {
        for (j = 0; j < MAP_COLS; j++) {
            if (map.overlay[i][j] == '$') {
                position = (i * MAP_COLS) + j;
                count = 0;
                prevChecked[count] = position;
                goto outer;
            }
        }
    }

    outer:
    pathSolve(map, path, prevChecked, count + 1, position);

    return path;
}


struct Path *pathSolve(struct Map map,struct Path *path,int prevChecked[],int count,int currentPosition){
    int i,j,nextPosition,beingChecked;

    i = (currentPosition-1)/MAP_COLS;
    j = currentPosition - (MAP_COLS*i);

    beingChecked = ((i+1)*MAP_COLS)+j;

    if (!beenChecked(prevChecked,beingChecked) && isPathCharacter(map.overlay[i+1][j])){
        nextPosition = currentPosition + MAP_COLS;
        prevChecked[count] = currentPosition;
        pushToPath(createTileNode(currentPosition,map.overlay[i+1][j]),path);
        pathSolve(map,path,prevChecked,count+1,nextPosition);
    }

    beingChecked = (i*MAP_COLS)+(j+1);

    if (!beenChecked(prevChecked,beingChecked) && isPathCharacter(map.overlay[i][j+1])){
        nextPosition = currentPosition + 1;
        prevChecked[count] = currentPosition;
        pushToPath(createTileNode(currentPosition,map.overlay[i][j+1]),path);
        pathSolve(map,path,prevChecked,count+1,nextPosition);
    }

    beingChecked = ((i-1)*MAP_COLS)+j;

    if (i > 0){
        if (!beenChecked(prevChecked,beingChecked) && isPathCharacter(map.overlay[i-1][j])){
            nextPosition = currentPosition - MAP_COLS;
            prevChecked[count] = currentPosition;
            pushToPath(createTileNode(currentPosition,map.overlay[i-1][j]),path);
            pathSolve(map,path,prevChecked,count+1,nextPosition);
        }
    }

    beingChecked = (i*MAP_COLS)+(j-1);

    if (j > 0){
        if (!beenChecked(prevChecked,beingChecked) && isPathCharacter(map.overlay[i][j-1])){
            nextPosition = currentPosition - 1;
            prevChecked[count] = currentPosition;
            pushToPath(createTileNode(currentPosition,map.overlay[i][j]),path);
            pathSolve(map,path,prevChecked,count+1,nextPosition);
        }
    }

    return path;
}

bool beenChecked(int prevChecked[], int position) {
    int arrayLength;

    arrayLength = MAP_COLS * MAP_ROWS;
    for (int i = 0; i < arrayLength; i++) {
        if (prevChecked[i] == position) {
            return true;
        }
    }
    return false;
}

bool isPathCharacter(char tileChar) {
    return (tileChar == '.' || tileChar == '#' || tileChar == '$' ||
        tileChar == '&' || tileChar == '%');
}

struct TileNode *createTileNode(int location, char type) {
    struct TileNode *tileNode = NULL;

    tileNode = (struct TileNode *) malloc(sizeof(struct TileNode));

    tileNode->next = NULL;
    tileNode->location = location;
    tileNode->type = type;

    return tileNode;
}

void pushToPath(struct TileNode *insertNode, struct Path *path) {
    struct TileNode *nextNode = NULL;

    if (path->count > 0) {
        nextNode = path->first;

        while (nextNode->next != NULL) {
            nextNode = nextNode->next;
        }

        nextNode->next = insertNode;
        path->count++;
    }
    else {
        path->first = insertNode;
        path->count++;
    }
}

void destroyPath(struct Path *path) {
    struct TileNode *nextNode = NULL;

    if (path->count > 0) {
        nextNode = path->first;
    }

    for (int i = 0; i < path->count; i++) {
        while (nextNode->next != NULL) {
            nextNode = nextNode->next;
            free(nextNode);
            path->count--;
        }
    }
    free(path);
}
