#include <dirent.h>
#include <unistd.h>
#include "riotTesting.h"


int main(int argc, char **argv) {

    if (argc == 1) {
        printf("No testing parameters provided. Exiting");
        exit(-1);
    }

    for (int i = 0; i < argc; i++) {

        if (!strcmp(argv[1], "-units")) unitsTest();
        else if (!strcmp(argv[1], "-map")) mapsTest(argv[2]);

    }


    printf("Testing done.\n");
    return 0;

}


void unitsTest(void) {
    struct UnitList *inmates, *guards;

    inmates = createList();
    guards = createList();


    for (int i = 0; i < TRIALS; i++) {
        enqueue(inmates, createInmate(HOMEBOY));
        printf("Adding an inmate to the list (%d)\n", inmates->count);
    }
    putchar('\n');

    while (inmates->count) {
        rmUnit(dequeue(inmates));
        printf("Removing an inmate from the list (%d)\n", inmates->count);
    }
    putchar('\n');

    destroyList(inmates);
    destroyList(guards);

    return;
}


void mapsTest(char *loadDir) {

    struct MapList *mapList;
    struct Map* current;
    DIR *directory;
    struct dirent *entry;

    mapList = malloc(sizeof(struct MapList));
    current = malloc(sizeof(struct Map));
    if(!loadDir) loadDir = getcwd(loadDir,PATH_MAX);
    directory = opendir(loadDir);

    mapList->count=0;
    current = mapList->first;
    current->next = NULL;

    if (directory) {
        while ((entry = readdir(directory))){
//            current=malloc(sizeof(struct Map));
//            sprintf(current->location,"%s/%s",loadDir,entry->d_name);
//            current=current->next;
            mapList->count++;
        }
        closedir(directory);
    }

    return;
}


void printInmate(struct Inmate *inmate) {

    switch (inmate->type) {
        case PROTAGONIST:
            printf("unit:\t Protagonist\n");
            break;

        case HOMEBOY:
            printf("unit:\t Homeboy\n");
            break;

        case BRUISER:
            printf("unit:\t Bruiser\n");
            break;

        case LUNATIC:
            printf("unit:\t Lunatic\n");
            break;

        case FATTY:
            printf("unit:\t Fatty\n");
            break;

        case SPEEDY:
            printf("unit:\t Speedy\n");
            break;

        case CUTIE:
            printf("unit:\t Cutie\n");
            break;

        case ATTORNEY:
            printf("unit:\t Attorney\n");
            break;

        case DOCTOR:
            printf("unit:\t Doctor\n");
            break;

        default:
            break;
    }

    printf("pos:\t%d\n", inmate->position);
    printf("curHP:\t%d\n", inmate->health[0]);
    printf("maxHP:\t%d\n", inmate->health[1]);
    printf("speed:\t%d\n", inmate->speed);
    printf("rep:\t%d\n", inmate->rep);
    printf("panic:\t%d\n", inmate->panic);
    printf("\n");

    return;
}


void printGuard(struct Guard *guard) {

    int i = 0;

    printf("Guard #%d\n", i + 1);

    switch (guard->type) {
        case GUARD:
            printf("unit:\t\tGuard\n");
            break;

        case DOGS:
            printf("unit:\t\tDogs\n");
            break;

        case LUNCH:
            printf("unit:\t\tLunch Lady\n");
            break;

        case PSYCH:
            printf("unit:\t\tPsychopath\n");
            break;

        case SHARP:
            printf("unit:\t\tSharp Shooter\n");
            break;

        case WARDEN:
            printf("unit:\t\tWarden\n");
            break;

        case CYBORG:
            printf("unit:\t\tCyborg\n");
            break;

        default:
            break;
    }

    printf("pos: %d\n", guard->position);
    printf("damage: %d\n", guard->damage);
    printf("range: %d\n", guard->range);
    printf("cooldown: %d\n", guard->cooldown);
    printf("ai: %d\n", guard->ai);
    printf("\n");

    return;
}


void quit(char *message) { }
