#include "riotTesting.h"

int main(int argc, char **argv) {

    struct List *inmates, *guards;

    inmates = createList();
    guards = createList();

    destroyList(inmates);
    destroyList(guards);
}


void quit(char *message) { }
