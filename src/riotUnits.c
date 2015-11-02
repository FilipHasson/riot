#include "riotUnits.h"

/*Move inmate every turn by its speed*/
void inmateMove(Inmate *inmate){
	int prevPos;
	Inmate * nextInmate;

	nextInmate = inmate;
	while(nextInmate->next != NULL){
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
		inmateRedraw(prevPos,(int)inmate->position,inmate->type);
		nextInmate = nextInmate->next;
	}
}
/*Compare the positions of every inmate, and the positions of attack of every guard
  if the units position matches the area of attack of the guard than subtract its 
  health by the guards damage*/	
void guardAttack(Guard * guard,Inmate *inmate){
	int i;
	int range;
	Inmate * nextInmate;
	Guard * nextGuard;
	
	nextGuard = guard;
	nextInmate = inmate;
	while(nextGuard->next != NULL){
		/*Get the unit range*/
		range = sizeof(nextGuard->positionRange)/sizeof(short);
		while(nextInmate->next != NULL){
			for (i=0;i<range;i++){
				if (nextGuard->positionRange[i] == nextInmate->position){
					nextInmate->healthCur = nextInmate->healthCur - nextGuard->damage;
				}
			}
			nextInmate = nextInmate->next;
		}
		nextGuard = nextGuard->next;	
	}	
}
