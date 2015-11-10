#include "riotUnits.h"
//Rowsize needs to be adjusted based on the rowsize(X size) of the map
#define ROWSIZE 10

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


short getLength(struct UnitList *listIn) {
    return listIn ? listIn->count : (short) -1;
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

    if (queue->head) {
        queue->head->prev = NULL;
    }

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

    if (stack->head) {
        stack->head->prev = NULL;
    }

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
            break;

        case HOMEBOY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 4;
            unit->rep = 5;
            unit->panic = 2;
            break;

        case BRUISER:
            unit->currentHealth = unit->maxHealth = 16;
            unit->speed = 4;
            unit->rep = 15;
            unit->panic = 6;
            break;

        case LUNATIC:
            unit->currentHealth = unit->maxHealth = 16;
            unit->speed = 6;
            unit->rep = 10;
            unit->panic = 8;
            break;

        case FATTY:
            unit->currentHealth = unit->maxHealth = 40;
            unit->speed = 2;
            unit->rep = 10;
            unit->panic = 4;
            break;

        case SPEEDY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 8;
            unit->rep = 20;
            unit->panic = 2;
            break;	

        case CUTIE:
            unit->currentHealth = unit->maxHealth = 20;
            unit->speed = 4;
            unit->rep = 20;
            unit->panic = 1;
            break;

        case ATTORNEY:
            unit->currentHealth = unit->maxHealth = 30;
            unit->speed = 5;
            unit->rep = 30;
            unit->panic = 2;
            break;

        case DOCTOR:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 5;
            unit->rep = 40;
            unit->panic = 2;
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

// /*Move inmate every turn by its speed*/
// void inmateMove(struct UnitNode *inmate) {

//    int prevPos;
//    struct UnitNode * nextInmate = inmate;
//    while(nextInmate->next != NULL) {
//        prevPos = inmate->unit->position;
//        inmate->position = inmate->pos + inmate->speed/8;
//        /* inmateRedraw(int previousPosition, int currentPosition, char type) is
//           a function which should be located inside the UI source file*/

//        //inmateRedraw(prevPos,(int)inmate->pos,inmate->type);
//        nextInmate = nextInmate->next;
//    }
// }
/*Compare the positions of every inmate, and the positions of attack of every guard
 if the units pos matches the area of attack of the guard than subtract its
 health by the guards damage*/
void guardAttack(struct UnitList *guardList, struct UnitList *inmateList) {
   struct UnitNode * nextInmate;
   struct UnitNode * nextGuard;

   nextGuard = getHead(guardList);
   nextInmate = getHead(inmateList);

   printf("Guard Attack has begun.\n\n");

    do{
       do {
           if (inRange(ROWSIZE,nextInmate,nextGuard)) {
             dealDamage(nextInmate,nextGuard);
           }
           nextInmate = getNext(nextInmate);
       } while(getNext(nextInmate) != NULL);
       nextGuard = getNext(nextGuard);
   } while(getNext(nextGuard) != NULL);
}

void dealDamage(struct UnitNode * inmateNode,struct UnitNode * guardNode){
    printf("#####Inmate attacked#####\n");
    printf("Inmate Position: %d\n",((struct Inmate*)inmateNode->unit)->position);
    printf("Guard Position: %d\n",((struct Guard*)guardNode->unit)->position);
    printf("Health before attack: %d\n",((struct Inmate*)inmateNode->unit)->currentHealth);
    printf("Damage dealt by guard: %d\n",((struct Guard*)guardNode->unit)->damage);
	((struct Inmate*)inmateNode->unit)->currentHealth = ((struct Inmate*)inmateNode->unit)->currentHealth - ((struct Guard*)guardNode->unit)->damage;

    printf("Health after attack: %d\n",((struct Inmate*)inmateNode->unit)->currentHealth);
    printf("########################\n");
    printf("\n");
}
bool inRange(int rowSize,struct UnitNode *inmate,struct UnitNode *guard){
    int inmatePosition;
    int guardPosition;
    int range;
	int xDifference;
	int yDifference;
	int totalDifference; 

    inmatePosition = ((struct Inmate*)inmate->unit)->position;
    guardPosition = ((struct Guard*)guard->unit)->position;
    range = ((struct Guard*)guard->unit)->range;

	yDifference = (((inmatePosition-1)/rowSize)+1)-(((guardPosition-1)/rowSize)+1);
	xDifference = (guardPosition+(yDifference*rowSize))-inmatePosition;
    yDifference = abs(yDifference);
    xDifference = abs(xDifference);
    totalDifference = xDifference+yDifference;
    printf("#####Calculating Range#####\n");
    printf("Unit position: %d\n",inmatePosition);
    printf("Guard position: %d\n",guardPosition);
    printf("Y Difference: %d\n",yDifference);
    printf("X Difference: %d\n",xDifference);
    printf("Total Difference: %d\n",totalDifference);
    printf("Range of the Guard: %d\n",range);
    printf("############################\n");
    printf("\n");

	return range >= totalDifference;
}