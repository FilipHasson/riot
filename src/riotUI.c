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
        if (last->beaten) {
#endif

        mvwprintw(menu, y + i, 21, "[%i] %s", i, current->name);

#ifndef _DEBUG
        } else y--;
#endif

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
    } while (false);
#else
    } while (!unlocked[select - '0']);
#endif

    return (select - '0');
}

void drawInmateSelection(struct Interface *win, struct Map *map, struct UnitList *inmates) {
    struct Inmate * inmate;
    char input;
    int y;

    mvwprintw(win->body, MAP_ROWS, 3, "Press the corresponding letter to buy inmate");
    mvwprintw(win->footer, 0, 3, "Press \"Enter\" to play:");
    drawLevel (win, map);
    wrefresh(win->footer);
    do {
        updateHeader(win->header,map);
        wrefresh(win->header);
        input = wgetch(win->body);
            switch (input) {
                case 'h':
                    if (map->repMax >= 10) {
                        mvwprintw(win->footer, 0, 40, "HOMEBOY ADDED");
                        map->repMax -= 10;
                        inmate = createInmate(input);
                    } 
                    else {
                        mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                    }     
                    break;
                case 'b':
                    if (map->repMax >= 16) {
                        mvwprintw(win->footer, 0, 40, "BRUISER ADDED");
                        inmate = createInmate(input);
                        map->repMax-=16;
                    }
                    else {
                        mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 'l':
                    if (map->repMax >= 16) {
                        mvwprintw(win->footer, 0, 40, "LUNATIC ADDED");
                        inmate = createInmate(input);
                        map->repMax-=16;
                    }
                    else {
                        mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 'f':
                    if (map->repMax >= 60) {
                        mvwprintw(win->footer, 0, 40, "FATTY ADDED");
                        inmate = createInmate(input);
                        map->repMax-=60;
                    }
                    else {
                        mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 's':
                    if (map->repMax >= 10) {
                        mvwprintw(win->footer, 0, 40, "SPEEDY ADDED");
                        inmate = createInmate(input);
                        map->repMax-=10;
                    }
                    break;
                case 'c':
                    if (map->repMax >= 20) {
                        mvwprintw(win->footer, 0, 40, "CUTIE ADDED");
                        inmate = createInmate(input);
                        map->repMax-=20;
                    }
                    else {
                        mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 'a':
                    if (map->repMax >= 30) {
                        mvwprintw(win->footer, 0, 40, "ATTORNEY ADDED");
                        inmate = createInmate(input);
                        map->repMax-=30;
                    }
                    else {
                        mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                    }   
                    break;
                case 'd':
                    if (map->repMax >= 10) {
                        mvwprintw(win->footer, 0, 40, "DOCTOR ADDED");
                        inmate = createInmate(input);
                        map->repMax-=10;
                    }
                    else {
                        mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                    }              
                    break;
                default:
                    mvwprintw(win->footer, 0, 40, "INMATE NOT FOUND");
            }       
            if (map->repMax < 10) {
                mvwprintw(win->footer, 0, 20, "INSUFICIENT FUNDS");
                wrefresh(win->footer);
                wgetch(win->body);
                break;
            }
            wrefresh(win->footer);
            for (y=40; y<MAX_COLS-5;y++){
               mvwaddch(win->footer, 0,y,ACS_HLINE);
        }
    } while (input != '\n');

    wclear(win->header);
    wclear(win->body);
    wclear(win->footer);
        
}

void updateHeader (WINDOW *header, struct Map *map){
    wclear(header);
    box(header, 0, 0);
    mvwprintw(header, 1, 1, "Level %d: %s", map->levelNo,
        map->name); // Display Level
    mvwprintw(header, 1, MAX_COLS - 24, "Panic:%d%%",
        map->panicMax); // Display Panic
    mvwprintw(header, 1, MAX_COLS - 11, "Rep:%d",
        map->repMax); // Display Rep
    mvwaddstr(header, 0, 1, "riot");
    mvwaddch (header, 2, 0, ACS_LTEE);
    mvwaddch (header, 2, MAX_COLS - 1, ACS_RTEE);
}

void startHeadFoot(struct Interface *win, struct Map *map){
    int y;

    wclear(win->header);
    wclear(win->footer);

    /*Draws the header*/
    updateHeader(win->header, map);

    /* Draw window borders around windows */
    box(win->footer, 0, 0);
    mvwaddch(win->footer, 0, 0, ACS_LTEE);
    mvwaddch(win->footer, 0, MAX_COLS - 1, ACS_RTEE);
    mvwaddch(win->header, 0, 0, ACS_ULCORNER);
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(win->body, y, 0, ACS_VLINE);
        mvwaddch(win->body, y, MAX_COLS - 1, ACS_VLINE);
    }
        /*Populates footer*/
    drawFooterInmates(win, map->inmates);
}

void drawQueue (WINDOW *body){
    int y;

    mvwaddstr(body, 4, MAX_COLS - 6, "QUEUE");
    mvwaddch(body, 5, MAX_COLS - 6, ACS_ULCORNER);
    mvwaddch(body, 5, MAX_COLS - 2, ACS_URCORNER);
    mvwaddch(body, 11, MAX_COLS - 6, ACS_LLCORNER);
    mvwaddch(body, 11, MAX_COLS - 2, ACS_LRCORNER);
    mvwaddch(body, 6, MAX_COLS - 3, '.');
    for (y = 1; y < 6; y++)
        mvwprintw(body, 5 + y, MAX_COLS - 5, "%d", y);
    for (y = 0; y < 3; y++) {
        mvwaddch(body, 5, MAX_COLS - 5 + y, ACS_HLINE);
        mvwaddch(body, 11, MAX_COLS - 5 + y, ACS_HLINE);
    }
    for (y = 0; y < 5; y++) {
        mvwaddch(body, 6 + y, MAX_COLS - 6, ACS_VLINE);
        mvwaddch(body, 6 + y, MAX_COLS - 2, ACS_VLINE);
    }
    wrefresh(body);
}

void updateQueue (WINDOW *body, struct UnitList *list){
    //Need to DO
    wrefresh(body);
}

void drawMap (WINDOW *body, struct Map*map){
    int y;
    for (y = 0; y < MAP_ROWS; y++)
        mvwaddstr(body, y, 1, map->overlay[y]);
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(body, y, 0, ACS_VLINE);
        mvwaddch(body, y, MAX_COLS - 1, ACS_VLINE);
    }
}


void drawLevel(struct Interface *win, struct Map *map){
    drawMap(win->body,map);
    drawQueue(win->body);
    /* Refresh windows */
    wrefresh(win->body);
    return;
}

void redrawUnit(struct Interface *win, struct Inmate *inmate, struct Path *path,
    int oldPosition) {
    int *currentCoordinates;
    int *newCoordinates;
    float hp, mhp, php;

    hp = 1*inmate->currentHealth;
    mhp = 1*inmate->maxHealth;
    php = (hp/mhp)*100;

    init_pair(1,COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN, GREEN, COLOR_BLACK);
    init_pair(YELLOW, YELLOW, COLOR_BLACK);
    init_pair(RED, RED, COLOR_BLACK);
    init_pair(PURPLE, PURPLE, COLOR_BLACK);

    if (php > 75){
        attron (COLOR_PAIR (GREEN));
    } else if (php >50){
        attron (COLOR_PAIR (YELLOW));
    } else if (php >25){
        attron (COLOR_PAIR (RED));
    } else{
        attron (COLOR_PAIR (PURPLE));
    }

    currentCoordinates = getCoordinate(oldPosition);
    mvwaddch(win->body, currentCoordinates[0], currentCoordinates[1], '*');

    newCoordinates = getCoordinate(inmate->position);
    mvwaddch(win->body, newCoordinates[0], newCoordinates[1], inmate->type);

    attron (COLOR_PAIR (1));

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
    int i;

    strcpy(output, "");
    for (i = 0; i < strlen(inmates); i++) {
        strcat(output, getInmateName(inmates[i]));
        strcat(output, "\t");
        if (i == 3) {
            mvwaddstr(win->footer, 1, 10, output);
            strcpy(output, "");
        }
    }
    mvwprintw(win->footer, 1, 1, "INMATES");
    mvwaddstr(win->footer, 2, 10, output);
}


void drawIntroText (struct Interface *win, struct Map *map){
    /* creates pause with text output*/
    startHeadFoot(win,map);
    mvwprintw(win->body, 7, 10, "Placeholder text motherfucker.....");//temp
    wrefresh(win->body);
    wclear(win->body);
    wrefresh(win->header);
    wrefresh(win->footer);
    getchar();
}


void drawOutroText (struct Interface *win, struct Map *map){
    /* creates pause with text output*/
    mvwprintw(win->body, 7, 10, "Placeholder text motherfucker.....");//temp
    wrefresh(win->body);
    wrefresh(win->header);
    wrefresh(win->footer);
    getchar();
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
