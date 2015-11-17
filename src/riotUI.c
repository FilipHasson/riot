#include "riotUI.h"

void uiSet(enum GameMode gameMode, struct Interface *win) {

    int y, x;

    switch (gameMode) {

        case INIT:
            initscr();
            start_color();
            noecho(); // hide keypresses
            curs_set(FALSE); // hide cursor

            /* Verify terminal dimensions */
            getmaxyx(stdscr, y, x);
            if ((x < MAX_COLS) || (y < MAX_ROWS))
                quit("Terminal size too small");

            /* Set window positions*/
            win->header = newwin(HEADER, MAX_COLS, 0, 0);
            win->body = newwin(MAIN, MAX_COLS, HEADER, 0);
            win->footer = newwin(FOOTER, MAX_COLS, HEADER + MAIN, 0);
            win->menu = newwin(MAX_ROWS, MAX_COLS, 0, 0);
            break;

        case MENU:
            wrefresh(win->menu);
            break;

        case NEW:
        case CONTINUE:
        case PLAY:
            wclear(win->body);
            wclear(win->header);
            wclear(win->footer);
            wclear(win->menu);
            break;

        case EXIT:
            if (win->header) delwin(win->header);
            if (win->body) delwin(win->body);
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

    enum GameMode gameMode = _GAME_MODE_LIMIT;
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


int menuContinue(struct Interface *gameInterface, struct MapList *mapList) {

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
#ifndef _DEBUG
        if (!current->hidden) {
            mvwprintw(menu, y + i, 21, "[%c] %s",
                last->beaten ? i + '0' : '-', current->name);
        } else if (current->hidden && last->beaten) {
            mvwprintw(menu, y + i, 21, "[%i] %s", i, current->name);
        } else y--;
#else
        mvwprintw(menu, y + i, 21, "[%c] %s", i + '0', current->name);
#endif

        /* Set unlocked state */
        unlocked[i] = current->beaten;
    }
    mvwaddstr(menu, MAX_ROWS - 4, 21, "[b]ack");
    wrefresh(menu);

    /* Get user input */
    do {
        select = (char) wgetch(menu);
        if (select == 'b') return -1;
        if (select - '0' < 0 || select > MAX_LEVELS) continue;
#ifndef _DEBUG
        } while (!unlocked[select - '0']);
#else
    } while (false);
#endif

    return (int) (select - '0');
}

void drawInmateSelection(struct Interface *win, struct Map *map) {
    int y, i;
    int rep = map->panicMax;
    struct Inmate * inmate;
    char input;

    do {
        drawBorders(win);
        
        mvwprintw(win->header, 1, MAX_COLS - 11, "Rep:%d",
            rep);
        mvwprintw(win->header, 1, 1, "Level %d: %s", map->levelNo,
            map->name); // Display Level
        mvwprintw(win->header, 1, MAX_COLS - 24, "Panic:%d%%",
            map->panicMax); // Display Panic

        mvwprintw(win->body, 1, MAX_COLS/2-9, "Inmate Selection");
        mvwhline(win->body, 2, MAX_COLS/2-10, '-', 18);

        y=4;
        for (i=0; i<strlen(map->inmates); i++) {
            mvwprintw(win->body, y, 30, "%s", getInmateName(map->inmates[i]));
            y++;
        }

        mvwprintw(win->footer, 1, 1, "\t\tPress the corresponding letter to buy inmate");
        mvwprintw(win->footer, 2, 1, "\t\tPress \"Enter\" to continue");

        wrefresh(win->header);
        wrefresh(win->footer);
        wrefresh(win->body);

        input = wgetch(win->body);
        wclear(win->body);

            switch (input) {
                case 'h':
                    if (rep >= 10) {
                        mvwprintw(win->body, 15, 30, "HOMEBOY ADDED");
                        rep-=10;
                        inmate = createInmate(input);
                    } 
                    else {
                        mvwprintw(win->body, 15, 30, "INSUFICIENT FUNDS");
                    }     
                    break;
                case 'b':
                    if (rep >= 16) {
                        mvwprintw(win->body, 15, 30, "BRUISER ADDED");
                        inmate = createInmate(input);
                        rep-=16;
                    }
                    else {
                        mvwprintw(win->body, 15, 30, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 'l':
                    if (rep >= 16) {
                        mvwprintw(win->body, 15, 30, "LUNATIC ADDED");
                        inmate = createInmate(input);
                        rep-=16;
                    }
                    else {
                        mvwprintw(win->body, 15, 30, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 'f':
                    if (rep >= 60) {
                        mvwprintw(win->body, 15, 30, "FATTY ADDED");
                        inmate = createInmate(input);
                        rep-=60;
                    }
                    else {
                        mvwprintw(win->body, 15, 30, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 's':
                    if (rep >= 10) {
                        mvwprintw(win->body, 15, 30, "SPEEDY ADDED");
                        inmate = createInmate(input);
                        rep-=10;
                    }
                    break;
                case 'c':
                    if (rep >= 20) {
                        mvwprintw(win->body, 15, 30, "CUTIE ADDED");
                        inmate = createInmate(input);
                        rep-=20;
                    }
                    else {
                        mvwprintw(win->body, 15, 30, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 'a':
                    if (rep >= 30) {
                        mvwprintw(win->body, 15, 30, "ATTORNEY ADDED");
                        inmate = createInmate(input);
                        rep-=30;
                    }
                    else {
                        mvwprintw(win->body, 15, 30, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 'd':
                    if (rep >= 10) {
                        mvwprintw(win->body, 15, 30, "DOCTOR ADDED");
                        inmate = createInmate(input);
                        rep-=10;
                    }
                    else {
                        mvwprintw(win->body, 15, 30, "INSUFICIENT FUNDS");
                    }              
                    break;
                default:
                    mvwprintw(win->body, 15, 30, "INMATE NOT FOUND");
            }       
            if (rep == 0) {
                wclear(win->body);
                drawBorders(win);
                mvwprintw(win->body, 4, 20, "0 REP, PRESS ANY KEY TO CONTINUE");
                wgetch(win->body);
                break;
            }
    } while (input != '\n');
    

    wclear(win->header);
    wclear(win->body);
    wclear(win->footer);
        
}

void drawLevel(struct Interface *win, struct Map *map) {
    int y;

    /* Draw Header */
    mvwprintw(win->header, 1, 1, "Level %d: %s", map->levelNo,
        map->name); // Display Level
    mvwprintw(win->header, 1, MAX_COLS - 24, "Panic:%d%%",
        map->panicMax); // Display Panic
    mvwprintw(win->header, 1, MAX_COLS - 11, "Rep:%d",
        map->repMax); // Display Rep

    /* Draw window borders around windows */
    box(win->header, 0, 0);
    box(win->footer, 0, 0);
    mvwaddch(win->footer, 0, 0, ACS_LTEE);
    mvwaddch(win->footer, 0, MAX_COLS - 1, ACS_RTEE);
    mvwaddch(win->header, 0, 0, ACS_ULCORNER);
    mvwaddstr(win->header, 0, 1, "riot");
    mvwaddch (win->header, 2, 0, ACS_LTEE);
    mvwaddch (win->header, 2, MAX_COLS - 1, ACS_RTEE);
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(win->body, y, 0, ACS_VLINE);
        mvwaddch(win->body, y, MAX_COLS - 1, ACS_VLINE);
    }

    /* creates pause with text output*/
    mvwprintw(win->body, 7, 10, "Placeholder text motherfucker.....");//temp
    wrefresh(win->body);
    wrefresh(win->header);
    wrefresh(win->footer);
    getchar();

    /* Draw Footer */
    mvwprintw(win->footer, 1, 1, "INMATES");
    drawFooterInmates(win, map->inmates);

    /* Draw the game map */
    for (y = 0; y < MAP_ROWS; y++)
        mvwaddstr(win->body, y, 1, map->overlay[y]);
    wrefresh(win->body);
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(win->body, y, 0, ACS_VLINE);
        mvwaddch(win->body, y, MAX_COLS - 1, ACS_VLINE);
    }

    /* Draw Queue */
    mvwaddstr(win->body, 4, MAX_COLS - 6, "QUEUE");
    mvwaddch(win->body, 5, MAX_COLS - 6, ACS_ULCORNER);
    mvwaddch(win->body, 5, MAX_COLS - 2, ACS_URCORNER);
    mvwaddch(win->body, 11, MAX_COLS - 6, ACS_LLCORNER);
    mvwaddch(win->body, 11, MAX_COLS - 2, ACS_LRCORNER);
    mvwaddch(win->body, 6, MAX_COLS - 3, '.');
    for (y = 1; y < 6; y++)
        mvwprintw(win->body, 5 + y, MAX_COLS - 5, "%d", y);
    for (y = 0; y < 3; y++) {
        mvwaddch(win->body, 5, MAX_COLS - 5 + y, ACS_HLINE);
        mvwaddch(win->body, 11, MAX_COLS - 5 + y, ACS_HLINE);
    }
    for (y = 0; y < 5; y++) {
        mvwaddch(win->body, 6 + y, MAX_COLS - 6, ACS_VLINE);
        mvwaddch(win->body, 6 + y, MAX_COLS - 2, ACS_VLINE);
    }
    /* Refresh windows */
    wrefresh(win->body);
    wrefresh(win->header);
    wrefresh(win->body);
    wrefresh(win->footer);
    //TODO
    getchar(); //temporary
    return;
}

void redrawUnit(struct Interface *win, struct Inmate *inmate, struct Path *path,
    int oldPosition) {
    int *currentCoordinates;
    int *newCoordinates;

    init_pair(GREEN, GREEN, COLOR_BLACK);
    init_pair(YELLOW, YELLOW, COLOR_BLACK);
    init_pair(RED, RED, COLOR_BLACK);
    init_pair(PURPLE, PURPLE, COLOR_BLACK);

    currentCoordinates = getCoordinate(oldPosition);
    mvwaddch(win->body, currentCoordinates[0], currentCoordinates[1], '*');

    newCoordinates = getCoordinate(inmate->position);
    mvwaddch(win->body, newCoordinates[0], newCoordinates[1], inmate->type);
}

void drawUnit(struct Interface *win, char unitType, int health, int position) {
    int *coordinates;
    coordinates = getCoordinate(position);
    mvwaddch(win->body, coordinates[0], coordinates[1], unitType);
}

void eraseUnit(struct Interface *win, int position) {
    int *coordinates;
    coordinates = getCoordinate(position);
    mvwaddch(win->body, coordinates[0], coordinates[1], '*');
}

void drawTile(struct Interface *win, char type, int position) {
    int *coordinates;
    coordinates = getCoordinate(position);
    mvwaddch(win->body, coordinates[0], coordinates[1], type);
}

int *getCoordinate(int position) {
    static int coordinates[2];

    coordinates[0] = ((position - 1) /
        MAX_ROWS);    //Gives you the row, where the lowest row is 0
    coordinates[1] = position - (coordinates[0] * MAX_ROWS);      //Gives you x

    return coordinates;
}

void drawFooterInmates(struct Interface *win, char *inmates) {
    char output[100];
    strcpy(output, "");
    int i;

    for (i = 0; i < strlen(inmates) - 1; i++) {
        strcat(output, getInmateName(inmates[i]));
        strcat(output, "\t");
        if (i == 3) {
            mvwaddstr(win->footer, 1, 10, output);
            strcpy(output, "");
        }
    }
    mvwaddstr(win->footer, 2, 10, output);
}

char *getInmateName(char ch) {
    switch (ch) {
        case 'h':
            return "[h]omeboy(10)";
        case 'b':
            return "[b]ruiser(16)";
        case 'l':
            return "[l]unatic(16)";
        case 'f':
            return "[f]fatty(60)";
        case 's':
            return "[s]peedy(10)";
        case 'c':
            return "[c]utie(20)";
        case 'a':
            return "[a]ttorney(30)";
        case 'd':
            return "[d]octor(10)";
        default:
            return "FAIL";
    }
}

void drawBorders (struct Interface * win) {
    int y;

    box(win->header, 0, 0);
        box(win->footer, 0, 0);
        mvwaddch(win->footer, 0, 0, ACS_LTEE);
        mvwaddch(win->footer, 0, MAX_COLS - 1, ACS_RTEE);
        mvwaddch(win->header, 0, 0, ACS_ULCORNER);
        mvwaddstr(win->header, 0, 1, "riot");
        mvwaddch (win->header, 2, 0, ACS_LTEE);
        mvwaddch (win->header, 2, MAX_COLS - 1, ACS_RTEE);
        for (y = 0; y < MAX_ROWS; y++) {
            mvwaddch(win->body, y, 0, ACS_VLINE);
            mvwaddch(win->body, y, MAX_COLS - 1, ACS_VLINE);
        }
}

