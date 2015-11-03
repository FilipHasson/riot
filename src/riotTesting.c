/******************************************************************************

ABOUT:
 - listTesting.c; logic testing for a singly linked list ADT
 - Last modified 06/16/2015

AUTHOR:
 - Written by Jessy Williams-Rancourt (0873195)
 - jwilli19@mail.uoguelph.ca

*******************************************************************************/

#include "riotTesting.h"

int main() {

    struct List* list;
    int i;

    list = createList();
    
    for (i = 0; i < 5; i++) {

        printf("\n###### RUN %d #####\n\n", i);

        if (i % 2) {
            printf("Removing %d from front\n",getFirst(list));
            deleteFront(list);
        }

        else {
            printf("Removing %d from back\n",getLast(list));
            deleteBack(list);
        }

        printf("Adding %d to front\n",arg[0]);
        insertFront(list, arg[0]);

        printf("Adding %d to back\n",arg[1]);
        insertBack(list, arg[1]);

        printf("\nResults:\n");
        printList(list);

        printf("\n");
    }

    destroyList(list);

    return 1;

}
