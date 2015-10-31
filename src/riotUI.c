#include "riotUI.h"
#include <locale.h>
#include <wchar.h>

void uiSet(enum GameMode gameMode, struct GameInterface *gameInterface) {

    switch (gameMode) {

        case INIT:
            initscr();
            noecho(); // hide keypresses
            curs_set(FALSE); // hide cursor

            gameInterface->header = newwin(HEADER, SIZE_X, 0, 0);
            gameInterface->main = newwin(MAIN, SIZE_X, HEADER + 1, 0);
            gameInterface->footer = newwin(SIZE_Y, FOOTER, HEADER + MAIN + 1, 0);
            gameInterface->menu = newwin(SIZE_Y, SIZE_X, 0, 0);
            break;

        case MENU:
            wrefresh(gameInterface->menu);
            break;

        case PLAY:
            wrefresh(gameInterface->header);
            wrefresh(gameInterface->main);
            wrefresh(gameInterface->footer);
            break;

        case EXIT:
            if (gameInterface->header) delwin(gameInterface->header);
            if (gameInterface->main) delwin(gameInterface->main);
            if (gameInterface->footer) delwin(gameInterface->footer);
            if (gameInterface->menu) delwin(gameInterface->menu);
            endwin();
            break;

        default:
            done("Invalid game mode initialized");
            break;
    }

    return;
}

enum GameMode menuMain(struct GameInterface *gameInterface) {

    enum GameMode gameMode;
    WINDOW * menu =  gameInterface->menu;

    int y = 3;

    box(menu, 0, 0);
    mvwaddstr(menu, y++, 21, "8888888b. 8888888 .d88888b.88888888888");
    mvwaddstr(menu, y++, 21, "888   Y88b  888  d88P   Y88b   888");
    mvwaddstr(menu, y++, 21, "888    888  888  888     888   888");
    mvwaddstr(menu, y++, 21, "888   d88P  888  888     888   888");
    mvwaddstr(menu, y++, 21, "8888888P    888  888     888   888");
    mvwaddstr(menu, y++, 21, "888 T88b    888  888     888   888");
    mvwaddstr(menu, y++, 21, "888  T88b   888  Y88b. .d88P   888");
    mvwaddstr(menu, y++, 21, "888   T88b8888888  Y88888P     888");

    mvwhline(menu,y+=2,21,ACS_HLINE,37);

    mvwaddstr(menu, y+=3, 21, "GAME MENU");
    y+=2;
    mvwaddstr(menu, y++, 21, "[n]ew game");
    mvwaddstr(menu, y++, 21, "[c]ontinue");
    mvwaddstr(menu, y++, 21, "[e]xit");

    wrefresh(menu);

    do {
        gameMode = (enum GameMode) wgetch(menu);
    } while (gameMode != 'n' && gameMode != 'c' && gameMode != 'e');

    return gameMode;
}

void menuNew() {
    return;
}

void menuContinue() {
    return;
}

void checkDisplay() {

    int y, x;

    /* Get terminal dimensions */
    initscr();
    getmaxyx(stdscr, y, x);
    endwin();

    /* Exit if < minimally permissable dimensions */
    if ((x < SIZE_X) || (y < SIZE_Y)) {
        done("Terminal size too small");
    }

    return;
}

