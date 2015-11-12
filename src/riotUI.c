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
            if ((x < MAX_COLS) || (y < MAX_ROWS))
                quit("Terminal size too small");

            /* Set window positions*/
            win->header = newwin(HEADER, MAX_COLS, 0, 0);
            win->main = newwin(MAIN, MAX_COLS, HEADER, 0);
            win->footer = newwin(FOOTER, MAX_COLS, HEADER + MAIN, 0);
            win->menu = newwin(MAX_ROWS, MAX_COLS, 0, 0);
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

    enum GameMode gameMode=_GAME_MODE_LIMIT;
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

    while (gameMode != 'n' && gameMode != 'c' && gameMode != 'e')
        gameMode = wgetch(menu);

    return gameMode;
}


short menuContinue(struct Interface *gameInterface, struct MapList *mapList) {

    WINDOW *menu = gameInterface->menu;
    struct Map *current, *last;
    int select;
    int y = 3;
    bool unlocked[MAX_LEVELS];

    wclear(menu);
    box(menu, 0, 0);

    /* Print header information */
    mvwaddstr(menu, y, 21, "LEVEL SELECT");
    mvwhline(menu, y += 2, 21, ACS_HLINE, 37);
    y += 2;

    /* Always print first level */
    mvwprintw(menu, y, 21, "[0] %s", mapList->level[0].name);
    unlocked[0] = true;

    /* Print additional levels */
    for (int i = 1; i < mapList->count; i++) {
        current = &mapList->level[i];
        last = &mapList->level[i - 1];

        if (!current->hidden) {
            mvwprintw(menu, y + i, 21, "[%c] %s",
                last->beaten ? i + '0' : '-', current->name);
        } else if (current->hidden && last->beaten) {
            mvwprintw(menu, y + i, 21, "[%i] %s", i, current->name);
        } else y--;

        /* Set unlocked state */
        unlocked[i] = current->beaten;
    }
    mvwaddstr(menu, MAX_ROWS - 4, 21, "[b]ack");
    wrefresh(menu);

    /* Get user input */
    do {
        select = (char)wgetch(menu);
        if (select == 'b') return -1;
        if (select -'0' < 0 || select > MAX_LEVELS) continue;
    } while (!unlocked[select-'0']);

    return (short) (select - '0');
}


enum GameMode drawLevel(struct Interface *gi, struct MapList *ml, int lvl) {

    enum GameMode gameMode;

    WINDOW *header = gi->header;
    WINDOW *main = gi->main;
    WINDOW *footer = gi->footer;
    struct Map *m = &ml->level[lvl];
    int y;

    /* Draw the game map */
    for (y = 0; y < MAP_ROWS; y++)
        mvwprintw (main, y, 0, m->overlay[y]);

    /* Draw window borders around windows */
    box(header, 0, 0);
    box(footer, 0, 0);
    mvwaddch(footer, 0, 0, ACS_LTEE);
    mvwaddch(footer, 0, MAX_COLS - 1, ACS_RTEE);
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(main, y, 0, ACS_VLINE);
        mvwaddch(main, y, MAX_COLS - 1, ACS_VLINE);
    }
    mvwaddch(header, 0, 0, ACS_ULCORNER);
    mvwaddstr(header, 0, 1, "riot");
    mvwaddch (header, 2, 0, ACS_LTEE);
    mvwaddch (header, 2, MAX_COLS - 1, ACS_RTEE);

    wrefresh(main);
    wrefresh(header);
    wrefresh(main);
    wrefresh(footer);

    getchar();
    return (gameMode);
}
