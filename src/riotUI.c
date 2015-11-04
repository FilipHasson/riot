#include "riotUI.h"

void uiSet(enum GameMode gameMode, struct Interface *win) {

    int y, x;

    switch (gameMode) {

        case INIT:

            initscr();
            noecho(); // hide keypresses
            curs_set(FALSE); // hide cursor

            /* Verify terminal dimensions */
            getmaxyx(stdscr, y, x);
            if ((x < SIZE_X) || (y < SIZE_Y)) quit("Terminal size too small");

            /* Set window positions*/
            win->header = newwin(HEADER, SIZE_X, 0, 0);
            win->main = newwin(MAIN, SIZE_X, HEADER + 1, 0);
            win->footer = newwin(SIZE_Y, FOOTER, HEADER + MAIN + 1, 0);
            win->menu = newwin(SIZE_Y, SIZE_X, 0, 0);
            break;

        case MENU:
            wrefresh(win->menu);
            break;

        case NEW:
        case CONTINUE:
            break;


        case PLAY:
            wrefresh(win->header);
            wrefresh(win->main);
            wrefresh(win->footer);
            break;

        case EXIT:
            if (win->header) delwin(win->header);
            if (win->main) delwin(win->main);
            if (win->footer) delwin(win->footer);
            if (win->menu) delwin(win->menu);
            endwin();
            break;

        default:
            quit("Invalid game mode initialized");
            break;
    }

    return;
}

enum GameMode menuMain(struct Interface *gameInterface) {

    enum GameMode gameMode;
    WINDOW *menu = gameInterface->menu;

    int y = 3;

    wclear(menu);
    box(menu, 0, 0);
    mvwaddstr(menu, y++, 21, "8888888b. 8888888 .d88888b.88888888888");
    mvwaddstr(menu, y++, 21, "888   Y88b  888  d88P   Y88b   888");
    mvwaddstr(menu, y++, 21, "888    888  888  888     888   888");
    mvwaddstr(menu, y++, 21, "888   d88P  888  888     888   888");
    mvwaddstr(menu, y++, 21, "8888888P    888  888     888   888");
    mvwaddstr(menu, y++, 21, "888 T88b    888  888     888   888");
    mvwaddstr(menu, y++, 21, "888  T88b   888  Y88b. .d88P   888");
    mvwaddstr(menu, y++, 21, "888   T88b8888888  Y88888P     888");

    mvwhline(menu, y += 2, 21, ACS_HLINE, 37);

    mvwaddstr(menu, y += 3, 21, "GAME MENU");
    y += 2;
    mvwaddstr(menu, y++, 21, "[n]ew game");
    mvwaddstr(menu, y++, 21, "[c]ontinue");
    mvwaddstr(menu, y++, 21, "[e]xit");

    wrefresh(menu);

    do {
        gameMode = (enum GameMode) wgetch(menu);
    } while (gameMode != 'n' && gameMode != 'c' && gameMode != 'e');

    return gameMode;
}


short menuContinue(struct Interface *gameInterface, struct MapList *levels) {

    WINDOW *menu = gameInterface->menu;
    char select;
    struct Map* level = levels->first;
    int y = 3;


    wclear(menu);
    box(menu, 0, 0);

    wclear(menu);
    box(menu, 0, 0);

    mvwaddstr(menu, y+=3, 21, "LEVEL SELECT");
    mvwhline(menu, y += 2, 21, ACS_HLINE, 37);
    y+=3;


    for(int i = 1; i < 10 && level;i++){
        mvwprintw(menu, y++, 21, "[%d] %s",i,level->name);
        level = level->next;
    }

    mvwaddstr(menu, y++, 21, "[b]ack");


    wrefresh(menu);

    do {
        select =  wgetch(menu);
    } while (select >= '1' && select > levels->count && select != 'b');


    return 0;
}

void menuNew() {
    return;
}
