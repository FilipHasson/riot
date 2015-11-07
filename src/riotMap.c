#include "riotMap.h"

struct MapList *parseMap(char *loadDir) {
    return NULL;
}


int getFilename(char *filename, char *ext) {
    const char* dotPos = strrchr(filename, '.');
    if (dotPos)
        return !strncmp(++dotPos, ext, strlen(ext));
    return 0;
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



