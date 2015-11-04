#include "riotMap.h"

struct MapList *parseMap(char *loadDir) {

    /* Map Placeholder Test Values */

    struct MapList *list = malloc(sizeof(struct MapList));
    list->first = malloc(sizeof(struct Map));
    strcpy(list->first->name,"Detention");
    list->first->path = NULL;
    list->first->next = NULL;
    list->count = 1;
    return list;
}

void checkArgs(int argc, char **argv) {

    /* Assess passed directory */

    if (argc > 2) quit("Too Many arguments");

    if (argc == 2) {
        //check passed dir
        //if invalid, abort
    }

    return;
}



