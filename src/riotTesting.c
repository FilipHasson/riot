#include <time.h>
#include <ncurses.h>
#include "riotTesting.h"

static void printPath(struct Path *path) {
    struct TileNode *nextNode;

    nextNode = path->first;
    printf("\n\n#### PRINTING PATH ####\n\n");
    for (int i = 0; i < path->count; i++) {
        printf("Location: %d :", nextNode->location);
        printf("Type: %c\n", nextNode->type);
        nextNode = nextNode->next;
    }
    printf("\n########################\n");
}

static void printGuardList(struct UnitList *guardList) {
    struct UnitNode *nextNode;
    struct Guard *guard;

    nextNode = getHead(guardList);
    guard = (struct Guard *) nextNode->unit;
    printf("\nGuard List Size: %d\n", guardList->count);
    printf("\n\n#### PRINTING GUARDS ####\n\n");
    for (int i = 0; i < guardList->count - 1; i++) {
        printf("Guard Type : %c\n", guard->type);
        printf("Location: %d\n", guard->position);
        printf("Damage: %d\n", guard->damage);
        printf("Range: %d\n", guard->range);
        printf("Cool Down: %d\n", guard->cooldown);
        printf("\n");
        nextNode = nextNode->next;
        guard = (struct Guard *) nextNode->unit;
    }
    printf("\n########################\n");
}


static void colorTest() {
    initscr();
    start_color();
    init_pair(GREEN, GREEN, COLOR_BLACK);
    init_pair(YELLOW, YELLOW, COLOR_BLACK);
    init_pair(RED, RED, COLOR_BLACK);
    init_pair(PURPLE, PURPLE, COLOR_BLACK);

    attron (COLOR_PAIR(GREEN));
    mvprintw(0, 0, "Green test");
    attron (COLOR_PAIR(YELLOW));
    mvprintw(1, 0, "Yellow test");
    attron (COLOR_PAIR(RED));
    mvprintw(2, 0, "Red test");
    attron (COLOR_PAIR(PURPLE));
    mvprintw(3, 0, "Purple test");
    refresh();
    getchar();
    endwin();
}

int main(int argc, char **argv) {

    if (argc == 1) {
        testingHelp();
        printf("\nExiting.");
        exit(-1);
    }
    for (int i = 1; i < argc; i++) {

        if (argv[i][0] != '-')continue; //only process flags

        if (!strcmp(argv[i], "-units")) unitsTest();
        else if (!strcmp(argv[i], "-map")) mapTest(argv[2] ? argv[2] : NULL);
        else if (!strcmp(argv[i], "-unitmove"))
            unitsMove(argv[2] ? argv[2] : NULL);
        else if (!strcmp(argv[i], "-color")) colorTest();
        else printf("Unknown command (%s)\n", argv[i]);
    }

    printf("Testing done.\n");
    return 0;

}

void unitsMove(char *loadDir) {
    struct UnitList *inmates;
    struct Inmate *inmateUnit;
    struct MapList *testList = parseMap(loadDir);
    struct Map *current;
    struct Path *path;
    printf("Riot Levels Found %d:\n\n", testList->count);
    inmates = createList();

    current = &testList->level[0];
    path = getPath(*current);
    printf("LEVEL %d: \n\n", 0);

    for (int j = 0; j < MAP_ROWS; j++) {
        printf("%s\n", current->overlay[j]);
    }

    printPath(path);

    inmateUnit = createInmate(HOMEBOY);
    inmateUnit->position = 693;
    enqueue(inmates, inmateUnit);
    printf("Adding an inmate to the list (%d)\n", inmates->count);
    printf("Inmate position is: %f\n-----\n", inmateUnit->position);

    for (int i = 0; i < 20; ++i) {
        /* code */
        inmateMove(inmates, path);
    }
    putchar('\n');

    while (inmates->count) {
        printf("Removing units (%d)\n", inmates->count);
        rmUnit(dequeue(inmates));
    }
    putchar('\n');

    destroyList(inmates);
}

void unitsTest(void) {
    struct UnitList *inmates, *guards;
    struct Inmate *inmateUnit;
    struct Guard *guardUnit;
    inmates = createList();
    guards = createList();

    guardUnit = createGuard(DOGS);
    guardUnit->position = (rand() % MAPSIZE) + 1;
    enqueue(guards, guardUnit);
    printf("Adding a guard to the list (%d)\n", guards->count);
    printf("Guard position is: %d\n", guardUnit->position);
    putchar('\n');

    srand(time(NULL));

    for (int i = 0; i < TRIALS; i++) {
        inmateUnit = createInmate(HOMEBOY);
        inmateUnit->position = (rand() % 90) + 1;
        enqueue(inmates, inmateUnit);
        printf("Adding an inmate to the list (%d)\n", inmates->count);
        printf("Inmate position is: %f\n", inmateUnit->position);
    }

    putchar('\n');
    guardAttack(guards, inmates);

    while (inmates->count) {
        printf("Removing an inmate from the list (%d)\n", inmates->count);
        rmUnit(dequeue(inmates));
    }
    putchar('\n');

    destroyList(inmates);
    destroyList(guards);

    return;
}


void mapTest(char *loadDir) {
    struct MapList *testList = parseMap(loadDir);
    struct Map *current;
    struct Path *path;
    struct UnitList *guardList;
    printf("Riot Levels Found %d:\n\n", testList->count);

    for (int i = 0; i < testList->count; i++) {
        current = &testList->level[i];
        path = getPath(*current);
        guardList = getGuardList(*current);
        printf("LEVEL %d: \n\n", i);

        printf("Name: %s\n", current->name);
        printf("Hidden: %d\n", current->hidden);
        printf("Beaten: %d\n", current->beaten);
        printf("\n");

        printf("Layout:\n");
        for (int j = 0; j < MAP_ROWS; j++) {
            printf("%s\n", current->overlay[j]);
        }

        printPath(path);
        printGuardList(guardList);
        printf("\n\n");

        destroyList(guardList);
        destroyPath(path);
    }

    return;

}

void printInmate(struct Inmate *inmate) {

    switch (inmate->type) {
        case PROTAGONIST:
            printf("unit:\t Protagonist\n");
            break;

        case HOMEBOY:
            printf("unit:\t Homeboy\n");
            break;

        case BRUISER:
            printf("unit:\t Bruiser\n");
            break;

        case LUNATIC:
            printf("unit:\t Lunatic\n");
            break;

        case FATTY:
            printf("unit:\t Fatty\n");
            break;

        case SPEEDY:
            printf("unit:\t Speedy\n");
            break;

        case CUTIE:
            printf("unit:\t Cutie\n");
            break;

        case ATTORNEY:
            printf("unit:\t Attorney\n");
            break;

        case DOCTOR:
            printf("unit:\t Doctor\n");
            break;

        default:
            break;
    }

    printf("pos:\t%f\n", inmate->position);
    printf("curHP:\t%d\n", inmate->currentHealth);
    printf("maxHP:\t%d\n", inmate->maxHealth);
    printf("speed:\t%d\n", inmate->speed);
    printf("rep:\t%d\n", inmate->rep);
    printf("panic:\t%d\n", inmate->panic);
    printf("\n");

    return;
}


void printGuard(struct Guard *guard) {

    int i = 0;

    printf("Guard #%d\n", i + 1);

    switch (guard->type) {
        case GUARD:
            printf("unit:\t\tGuard\n");
            break;

        case DOGS:
            printf("unit:\t\tDogs\n");
            break;

        case LUNCH:
            printf("unit:\t\tLunch Lady\n");
            break;

        case PSYCH:
            printf("unit:\t\tPsychopath\n");
            break;

        case SHARP:
            printf("unit:\t\tSharp Shooter\n");
            break;

        case WARDEN:
            printf("unit:\t\tWarden\n");
            break;

        case CYBORG:
            printf("unit:\t\tCyborg\n");
            break;

        default:
            break;
    }

    printf("pos: %d\n", guard->position);
    printf("damage: %d\n", guard->damage);
    printf("range: %d\n", guard->range);
    printf("cooldown: %d\n", guard->cooldown);
    printf("ai: %d\n", guard->ai);
    printf("\n");

    return;
}


void testingHelp() {
    printf(
        "Usage:\ttest [FLAG]... [OPTION]\n\n"
            "Flags:"
            "\t'-map' tests file parsing"
            "(defaults to cwd, optional absolute path as arg)\n"
            "\t'-unit' tests unit creation and deletion\n"
    );
}


void quit(char *message) {
    printf("ERROR: %s\n", message);
}
