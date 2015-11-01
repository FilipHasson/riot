#include "riotUI.h"

int main(int argc, char **argv) {

//    struct Map map;
    enum GameMode gameMode;
    struct GameInterface gameInterface;
//    map = parseMap(argv[1] ? argv[1] : NULL);

    uiSet(INIT, &gameInterface);
    gameMode = menuMain(&gameInterface);

    if (gameMode == NEW) {
        uiSet(NEW, &gameInterface);
//        newGame();

    } else {
        uiSet(CONTINUE, &gameInterface);
//        continueGame();
    }


    quit("Thanks for playing.");

    return 0;
}

void quit(char *message) {
    if (stdscr) endwin();;
    printf("%s. Exiting.", message);
    exit(-1);
}
