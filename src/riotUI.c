#include "riotUI.h"

#ifndef _DEBUG
#define _DEBUG
#endif


void uiInit(struct Windows *win) {

    int y, x;

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    noecho(); // hide keypresses
    curs_set(FALSE); // hide cursor

    /* Verify terminal dimensions */
    getmaxyx(stdscr, y, x);
    if ((x < MAX_COLS) || (y < MAX_ROWS)) quit("Terminal size too small");

    /* Set window positions*/
    win->header = newwin(HEADER, MAX_COLS, 0, 0);
    win->body = newwin(MAIN, MAX_COLS, HEADER, 0);
    win->footer = newwin(FOOTER, MAX_COLS, HEADER + MAIN, 0);
    win->menu = newwin(MAX_ROWS, MAX_COLS, 0, 0);
    wbkgd(win->body, COLOR_PAIR (1));
}


void uiFree(struct Windows *win) {
    if (stdscr) {
        if (win->header) delwin(win->header);
        if (win->body) delwin(win->body);
        if (win->footer) delwin(win->footer);
        if (win->menu) delwin(win->menu);
        endwin();
    }
}


enum GameMode menuMain(struct Windows *gameInterface) {

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

    while (gameMode != NEW && gameMode != CONTINUE && gameMode != EXIT)
        gameMode = wgetch(menu);

    return gameMode;
}


int levelSelect(struct Windows *gameInterface, struct MapList *mapList,
    bool *playerProgress) {
    WINDOW *menu = gameInterface->menu;
    struct Map *current;
    int select;
    int y = 3;

#ifndef _DEBUG
    bool unlocked[MAX_LEVELS];
    struct Map *current, *last;
#endif

    wclear(menu);
    box(menu, 0, 0);

    /* Print header information */
    mvwaddstr(menu, y, 21, "LEVEL SELECT");
    mvwhline(menu, y += 2, 21, ACS_HLINE, 37);
    y += 2;

    /* Always print first level */
    mvwprintw(menu, y, 21, "[0] %s", mapList->level[0].name);

#ifndef _DEBUG
    unlocked[0] = true;
#endif

    /* Print additional levels */
    for (int i = 1; i < mapList->count; i++) {
        current = &mapList->level[i];
#ifndef _DEBUG
        last = &mapList->level[i - 1];
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
#ifndef _DEBUG
        unlocked[i] = current->beaten;
#endif
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


void drawInmateSelection(struct Windows *win, struct Map *map,
    struct UnitList *inmates, struct UnitList *guards) {
    struct Inmate *inmate;
    char input;
    int y;
    int numAdded = 0;
//
//    mvwprintw(win->body, MAP_ROWS, 3,
//        "Press the corresponding letter to buy inmate");
//    mvwprintw(win->footer, 0, 3, "Press \"Enter\" to play:");
    do {
        updateHeader(win->header, map);
        wrefresh(win->header);
        input = wgetch(win->body);
        switch (input) {
            case 'h':
                if (map->repMax >= 10) {
                    mvwprintw(win->footer, 0, 40, "HOMEBOY ADDED");
                    map->repMax -= 10;
                    inmate = createInmate(input);
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
                }
                else {
                    mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                }
                break;
            case 'b':
                if (map->repMax >= 16) {
                    mvwprintw(win->footer, 0, 40, "BRUISER ADDED");
                    inmate = createInmate(input);
                    map->repMax -= 16;
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
                }
                else {
                    mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                }
                break;
            case 'l':
                if (map->repMax >= 16) {
                    mvwprintw(win->footer, 0, 40, "LUNATIC ADDED");
                    inmate = createInmate(input);
                    map->repMax -= 16;
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
                }
                else {
                    mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                }
                break;
            case 'f':
                if (map->repMax >= 60) {
                    mvwprintw(win->footer, 0, 40, "FATTY ADDED");
                    inmate = createInmate(input);
                    map->repMax -= 60;
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
                }
                else {
                    mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                }
                break;
            case 's':
                if (map->repMax >= 10) {
                    mvwprintw(win->footer, 0, 40, "SPEEDY ADDED");
                    inmate = createInmate(input);
                    map->repMax -= 10;
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
                }
                break;
            case 'c':
                if (map->repMax >= 20) {
                    mvwprintw(win->footer, 0, 40, "CUTIE ADDED");
                    inmate = createInmate(input);
                    map->repMax -= 20;
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
                }
                else {
                    mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                }
                break;
            case 'a':
                if (map->repMax >= 30) {
                    mvwprintw(win->footer, 0, 40, "ATTORNEY ADDED");
                    inmate = createInmate(input);
                    map->repMax -= 30;
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
                }
                else {
                    mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                }
                break;
            case 'd':
                if (map->repMax >= 10) {
                    mvwprintw(win->footer, 0, 40, "DOCTOR ADDED");
                    inmate = createInmate(input);
                    map->repMax -= 10;
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
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
        if (input == '\n' && numAdded == 0) {
            mvwprintw(win->footer, 0, 30, "Please select at least one unit");
            input = ' ';
        }
        else if (input == '\n') {
            break;
        }
        wrefresh(win->footer);
        for (y = 30; y < MAX_COLS - 5; y++) {
            mvwaddch(win->footer, 0, y, ACS_HLINE);
        }
    } while (input != '\n' && numAdded < 5);
    for (y = 1; y < MAX_COLS - 5; y++) {
        mvwaddch(win->footer, 0, y, ACS_HLINE);
    }
    for (y = 1; y < MAX_COLS - 5; y++) {
        mvwaddch(win->body, MAP_ROWS, y, ' ');
    }
    wrefresh(win->footer);
    wrefresh(win->body);
}


void updateHeader(WINDOW *header, struct Map *map) {
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


void updateQueue(WINDOW *body, struct UnitList *inmates, int numAdded) {
    struct Inmate *temp;
    struct UnitNode *node;
    node = getHead(inmates);
    temp = (struct Inmate *) node->unit;
    mvwaddch(body, 5 + numAdded, MAX_COLS - 3, temp->type);
    if (numAdded < 5) {
        mvwaddch(body, 6 + numAdded, MAX_COLS - 3, '.');
    }
    wrefresh(body);
}


void drawMap(WINDOW *body, struct Map *map) {
    int y;
    for (y = 0; y < MAP_ROWS; y++)
        mvwaddstr(body, y, 1, map->overlay[y]);
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(body, y, 0, ACS_VLINE);
        mvwaddch(body, y, MAX_COLS - 1, ACS_VLINE);
    }
}


void drawGuards(WINDOW *body, struct Map *map, struct UnitList *guards) {
    int *coordinates;
    int x;
    struct UnitNode *guardNode;
    struct Guard *guard;
    char type;
    guardNode = getHead(guards);
    guard = (struct Guard *) guardNode->unit;
    coordinates = getCoordinate(guard->position);
    type = guard->type;
    mvwaddch(body, coordinates[0], coordinates[1], type);
    for (x = 1; x < getLength(guards) - 2; x++) {
        guardNode = guardNode->next;
        guard = (struct Guard *) guardNode->unit;
        coordinates = getCoordinate(guard->position);
        type = guard->type;
        mvwaddch(body, coordinates[0], coordinates[1], type);
    }
}


void drawLevel(struct Windows *windows, struct Map *map,
    struct UnitList *guards) {

    char output[100];
    int i;
    int y;

    drawMap(windows->body, map);
    drawGuards(windows->body, map, guards);

    /* Draw Queue */
    mvwaddstr(windows->body, 4, MAX_COLS - 6, "QUEUE");
    mvwaddch(windows->body, 5, MAX_COLS - 6, ACS_ULCORNER);
    mvwaddch(windows->body, 5, MAX_COLS - 2, ACS_URCORNER);
    mvwaddch(windows->body, 11, MAX_COLS - 6, ACS_LLCORNER);
    mvwaddch(windows->body, 11, MAX_COLS - 2, ACS_LRCORNER);
    mvwaddch(windows->body, 6, MAX_COLS - 3, '.');
    for (y = 1; y < 6; y++)
        mvwprintw(windows->body, 5 + y, MAX_COLS - 5, "%d", y);
    for (y = 0; y < 3; y++) {
        mvwaddch(windows->body, 5, MAX_COLS - 5 + y, ACS_HLINE);
        mvwaddch(windows->body, 11, MAX_COLS - 5 + y, ACS_HLINE);
    }
    for (y = 0; y < 5; y++) {
        mvwaddch(windows->body, 6 + y, MAX_COLS - 6, ACS_VLINE);
        mvwaddch(windows->body, 6 + y, MAX_COLS - 2, ACS_VLINE);
    }

    /*Draws the header*/
    updateHeader(windows->header, map);

    /* Draw window borders around windows */
    box(windows->footer, 0, 0);
    mvwaddch(windows->footer, 0, 0, ACS_LTEE);
    mvwaddch(windows->footer, 0, MAX_COLS - 1, ACS_RTEE);
    mvwaddch(windows->header, 0, 0, ACS_ULCORNER);
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(windows->body, y, 0, ACS_VLINE);
        mvwaddch(windows->body, y, MAX_COLS - 1, ACS_VLINE);
    }

    /*Populates footer*/
    strcpy(output, "");
    for (i = 0; i < strlen(map->inmates); i++) {
        strcat(output, getInmateName(map->inmates[i]));
        strcat(output, "\t");
        if (i == 3) {
            mvwaddstr(windows->footer, 1, 10, output);
            strcpy(output, "");
        }
    }
    mvwprintw(windows->footer, 1, 1, "INMATES");
    mvwaddstr(windows->footer, 2, 10, output);

    wrefresh(windows->body);
    wrefresh(windows->header);
    wrefresh(windows->footer);

    return;
}


void redrawUnit(WINDOW *body, struct Inmate *inmate, struct Path *path,
    float oldPosition) {
    int *currentCoordinates = malloc(sizeof(int) * 2);
    int *newCoordinates = malloc(sizeof(int) * 2);
    float hp, mhp, php;
    int setColor = GREEN;
    hp = (float) inmate->currentHealth;
    mhp = (float) inmate->maxHealth;
    php = (hp / mhp) * 100;
    struct TileNode *tNode = path->first;
    char type = tNode->type;

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN, GREEN, COLOR_BLACK);
    init_pair(YELLOW, YELLOW, COLOR_BLACK);
    init_pair(RED, RED, COLOR_BLACK);
    init_pair(PURPLE, PURPLE, COLOR_BLACK);

    while (oldPosition < ((float) tNode->location)) {
        tNode = tNode->next;
    }
    type = tNode->type;

    wbkgd(body, COLOR_PAIR(1));

    if (php > 75.0) {
        setColor = GREEN;
    } else if (php > 50.0) {
        setColor = YELLOW;
    } else if (php > 25.0) {
        setColor = RED;
    } else {
        setColor = PURPLE;
    }

#ifndef _DEBUG
    /* Print movement debug information if the debug macro has been set */
    mvwprintw(
        body, 0, 1, "%d %d %f %f, %d, %d, %f, %f",
        newCoordinates[0], newCoordinates[1],
        inmate->position, php, inmate->currentHealth, inmate->maxHealth, hp, mhp
    );
#endif

    wbkgd(body, COLOR_PAIR(1));

    currentCoordinates = getCoordinate(oldPosition);
    mvwaddch(body, currentCoordinates[0], currentCoordinates[1], type);
    newCoordinates = getCoordinate(inmate->position);
    wbkgd(body, COLOR_PAIR(setColor));
    mvwaddch(body, newCoordinates[0], newCoordinates[1], inmate->type);
    wbkgd(body, COLOR_PAIR (1));
}


int *getCoordinate(int position) {
    static int coordinates[2];

    coordinates[0] = ((position - 1) /
        MAP_COLS);    //Gives you the row, where the lowest row is 0
    coordinates[1] =
        (position - (coordinates[0] * MAP_COLS)) + 1;      //Gives you x

    return coordinates;
}


void drawText(struct Windows *windows, struct Dialog dialog,
    enum GameMode gameMode) {
    char *target = NULL;
    char current;
    char new[] = "Placeholder newgame text"; //TODO revise
    int height = 0;
    int i = 1;
    int yOff, xOff;

    /* Get dialogue text field */
    switch (gameMode) {
        case NEW:
            target = new;
            height=1;
            break;
        case CONTINUE:
            target = dialog.textIntro;
            break;
        case WIN:
            target = dialog.textWin;
            break;
        case LOSE:
            target = dialog.textLose;
            break;
        default:
            quit("Simulation terminated with unknown condition");
    }

    xOff = MAX_COLS / 2 - MAP_COLS / 2;

    /* Print borders and static text */
    wclear(windows->menu);
    box(windows->menu, 0, 0);
    mvwaddstr(windows->menu,2,xOff,"Level x: Title"); //TODO revise
    mvwaddstr(windows->menu,2,MAX_COLS-27-xOff,"Press any key to continue...");


    wrefresh(windows->menu);

    /* Determine text height based on newline count */
    while ((current = target[i++]) != '\0')
        if (current == '\n')height++;
    if (height > MAX_ROWS) quit("Too much text in current dialogue entry");

    yOff = MAX_ROWS / 2 - height / 2;

    /* Resize window (temporarily)*/
    wresize(windows->menu, height, MAP_COLS + 1); // +1 for newline
    mvwin(windows->menu, yOff, xOff);
    wclear(windows->menu);


    /* Printout to screen */
    mvwaddstr(windows->menu,0,0, target);
    wrefresh(windows->menu);

    /* Wait for user input to continue */
    getchar();

    /* Restore window dimensions */
    wresize(windows->menu, MAX_ROWS, MAX_COLS);
    mvwin(windows->menu, 0, 0);
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
