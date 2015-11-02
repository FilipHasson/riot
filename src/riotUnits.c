//Units move
	//Move unit speed/8 units every turn
//Guard Attack
	//Every turn decrement unit health by damage of the guard
	//if the unit is within range
void inmateMove(Inmate *inmate){
	int i;
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
		inmate->position = inmate->position + inmate.speed/8;
		/* inmateRedraw(int previousPosition, int currentPosition, char type) is
		   a function which should be located inside the UI source file*/
		inmateRedraw(prevPos,(int)inmate->position,inmate->type);
		nextInmate = nextInmate->next;
	}
}
void guardAttack(Guard * guard,Inmate *inmate){
	int i;
	Inmate * nextInmate;
	Guard * nextGuard;
	
	nextGuard = guard;
	nextInmate = inmate;

	while(nextGuard->next != NULL){
		while(nextInmate->next != NULL){
			//Pseudo code for checking if inmate within range
			//For i=0 to i<Guard.proximityArraySize
			//if proximityArray[i] == nextInmate.position
			//nextInmate->healthCur = nextInmate->healthCut-Guard->damage 
			nextInmate = nextInmate->next;
		}
		nextGuard = nextGuard->next;	
	}	
}

