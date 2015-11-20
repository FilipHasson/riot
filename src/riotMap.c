#include <dirent.h>
#include <regex.h>
#include <unistd.h>
#include "riotMap.h"


void parseMap(char *loadDir, struct MapList *mapList, struct Dialog *dialog) {

    FILE *file;
    DIR *directory;
    regex_t riotExt;

    struct Map *current;
    struct dirent *entry;

    char path[PATH_MAX];
    wchar_t line[MAX_COLS];
    char *textBox[3];
    wchar_t checkChar;
    bool useCwd = false;
    bool firstRun = true;

    int x, y;

    setlocale(LC_ALL, "");

    /* Compile regex */
    regcomp(&riotExt, REGEX_EXT, REG_NOSUB | REG_EXTENDED);

    /* Create a new mapList to store map file details */
    mapList->count = 0;

    /* Use map directory passed as argument if provided, else cwd */
    if (!loadDir) {
        loadDir = getcwd(loadDir, PATH_MAX);
        strcat(loadDir,"/assets");
        useCwd = true;
    }

    /* Attempt to iterate through files in loadDir */
    if ((directory = opendir(loadDir)))

        while ((entry = readdir(directory))) {
            sprintf(path, "%s/%s", loadDir, entry->d_name);

            /* Skip if not readable .riot# file */
            if (regexec(&riotExt, entry->d_name, 0, NULL, 0)) continue;
            if (!(file = fopen(path, "r"))) continue;
            fseek(file, 0, SEEK_END);
            if (ftell(file) < MAP_SIZE) continue;
            rewind(file);
            /* Determine level number from filename*/
            if (entry->d_name[0] == '.') {
                current = &mapList->level[entry->d_name[1] - '0'];
                current->levelNo = entry->d_name[1] - '0';
            } else {
                current = &mapList->level[entry->d_name[0] - '0'];
                current->levelNo = entry->d_name[0] - '0';
            }

            /* Get level name */
            fgets(line, MAX_COLS, file);
            strtok(line, "]");
            strcpy(current->name, strtok(NULL, "\n"));

            /* Get rep */
            fgets(line, MAX_COLS, file);
            strtok(line, "]");
            current->repMax = atoi(strtok(NULL, "\n"));

            /* Get panic */
            fgets(line, MAX_COLS, file);
            strtok(line, "]");
            current->panicMax = atoi(strtok(NULL, "\n"));

            /* Get units */
            fgets(line, MAX_COLS, file);
            strtok(line, "]");
            strcpy(current->inmates, strtok(NULL, "\n"));

            /* Get map */
            while((fgetc(file)=='>'));
            for(y=0;y<MAP_ROWS;y++) {
                fgets(current->overlay[y], MAP_COLS*2, file);
                fseek(file,2,SEEK_CUR);
            }

            /* Get text boxes*/
            textBox[0] = dialog[current->levelNo].textIntro;
            textBox[1] = dialog[current->levelNo].textWin;
            textBox[2] = dialog[current->levelNo].textLose;

            for (int i = 0; i < 3; i++) {
                x = 0;
                do checkChar = fgetc(file); while (checkChar == '>');
                if (checkChar == '\0') strcpy(textBox[i], "");
                else
                    while ((checkChar = fgetc(file)) != '>') {
                        textBox[i][x++] = checkChar;
                    }
            }

            fclose(file);
            mapList->count++;
            firstRun = false;
        }

    /* Clean up memory */
    closedir(directory);
    regfree(&riotExt);
    if (useCwd) free(loadDir); //getcwd calls malloc, if used must free loadDir

    /* Terminate if no map files where found */
    if (firstRun) {
        quit("No map files found");
    }

    return;
}


void getPath(struct Path *path, struct Map map) {
    int i, j;
    int count = 0;
    int position = 0;
    int prevChecked[MAP_ROWS * MAP_COLS];

    for (i = 0; i < (MAP_ROWS * MAP_COLS); i++)
        prevChecked[i] = 0;
    path->count = 0;
    for (i = 0; i < MAP_ROWS; i++) {
        for (j = 0; j < MAP_COLS; j++) {
            if (map.overlay[i][j] == '$') {
                position = (i * MAP_COLS) + j;
                count = 0;
                prevChecked[count] = position;
                goto outer;
            }
        }
    }

    outer:
    pathSolve(map, path, prevChecked, count + 1, position);

    return;
}


struct Path *pathSolve(struct Map map, struct Path *path, int prevChecked[],
    int count, int currentPosition) {
    int i, j, nextPosition, beingChecked;

    i = (currentPosition - 1) / MAP_COLS;
    j = currentPosition - (MAP_COLS * i);

    beingChecked = ((i + 1) * MAP_COLS) + j;

    if (!beenChecked(prevChecked, beingChecked) &&
        isPathCharacter(map.overlay[i + 1][j])) {
        nextPosition = currentPosition + MAP_COLS;
        prevChecked[count] = currentPosition;
        pushToPath(createTileNode(currentPosition, map.overlay[i + 1][j]),
            path);
        pathSolve(map, path, prevChecked, count + 1, nextPosition);
    }

    beingChecked = (i * MAP_COLS) + (j + 1);

    if (!beenChecked(prevChecked, beingChecked) &&
        isPathCharacter(map.overlay[i][j + 1])) {
        nextPosition = currentPosition + 1;
        prevChecked[count] = currentPosition;
        pushToPath(createTileNode(currentPosition, map.overlay[i][j + 1]),
            path);
        pathSolve(map, path, prevChecked, count + 1, nextPosition);
    }

    beingChecked = ((i - 1) * MAP_COLS) + j;

    if (i > 0) {
        if (!beenChecked(prevChecked, beingChecked) &&
            isPathCharacter(map.overlay[i - 1][j])) {
            nextPosition = currentPosition - MAP_COLS;
            prevChecked[count] = currentPosition;
            pushToPath(createTileNode(currentPosition, map.overlay[i - 1][j]),
                path);
            pathSolve(map, path, prevChecked, count + 1, nextPosition);
        }
    }

    beingChecked = (i * MAP_COLS) + (j - 1);

    if (j > 0) {
        if (!beenChecked(prevChecked, beingChecked) &&
            isPathCharacter(map.overlay[i][j - 1])) {
            nextPosition = currentPosition - 1;
            prevChecked[count] = currentPosition;
            pushToPath(createTileNode(currentPosition, map.overlay[i][j]),
                path);
            pathSolve(map, path, prevChecked, count + 1, nextPosition);
        }
    }

    return path;
}


void pushToPath(struct TileNode *insertNode, struct Path *path) {
    struct TileNode *nextNode = NULL;

    if (path->count > 0) {
        nextNode = path->first;

        while (nextNode->next)
            nextNode = nextNode->next;

        nextNode->next = insertNode;
        path->count++;
    }

    else {
        path->first = insertNode;
        path->count++;
    }
}


bool beenChecked(int prevChecked[], int position) {
    int arrayLength;

    arrayLength = MAP_COLS * MAP_ROWS;
    for (int i = 0; i < arrayLength; i++) {
        if (prevChecked[i] == position)
            return true;
    }
    return false;
}


bool isPathCharacter(char tileChar) {
    return
        tileChar == '.' ||
            tileChar == '#' ||
            tileChar == '$' ||
            tileChar == '&' ||
            tileChar == '%';
}


struct TileNode *createTileNode(int location, char type) {
    struct TileNode *tileNode = NULL;

    tileNode = (struct TileNode *) malloc(sizeof(struct TileNode));

    tileNode->next = NULL;
    tileNode->location = location;
    tileNode->type = type;

    return tileNode;
}


void destroyPath(struct Path *path) {
    struct TileNode *nextNode = NULL;

    if (path->count > 0)
        nextNode = path->first;

    for (int i = 0; i < path->count; i++) {
        while (nextNode->next != NULL) {
            nextNode = nextNode->next;
            free(nextNode);
            path->count--;
        }
    }
    free(path);
}