#include "riotUI.h"

_Bool menuMain() {

    // _Bool status;

    initscr();
    noecho(); // hide keypresses
    curs_set(FALSE); // hide cursor

    // menuInterface = newwin(MINY, MINX, 1, 1);
    // box(menuInterface, 0, 0);
    // wrefresh(menuInterface);
    return true;
}

void menuNew() {
}
void menuContinue() {
}

void checkDisplay() {

    int y, x;

    /* Get terminal dimensions */
    initscr();
    getmaxyx(stdscr, y, x);
    endwin();

    /* Exit if < minimally permissable dimensions */
    if ((x < MINX) || (y < MINY)) {
        printf(
            "Error. Requires a terminal size of atleast %d by %d. Exiting.",
            MINX, MINY
        );
        exit(-1);
    }

    return;
}
