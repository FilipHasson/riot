#include <dirent.h>
#include <regex.h>
#include <unistd.h>
#include "riotMap.h"


struct MapList *parseMap(char *loadDir) {

    FILE *file;
    DIR *directory;
    regex_t riotExt;

    struct MapList *mapList;
    struct Map *current;
    struct dirent *entry;

    char path[PATH_MAX];
    char line[MAX_COLS];
    char *textBox[3];
    char checkChar;
    bool useCwd = false;
    bool firstRun = true;

    int x, y;

    /* Compile regex */
    regcomp(&riotExt, REGEX_EXT, REG_NOSUB | REG_EXTENDED);

    /* Create a new mapList to store map file details */
    mapList = malloc(sizeof(struct MapList));
    mapList->count = 0;

    /* Use map directory passed as argument if provided, else cwd */
    if (!loadDir) {
        loadDir = getcwd(loadDir, PATH_MAX);
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

            /* Assign beaten status */
            current->beaten = false;

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
                fgets(current->overlay[y], MAP_COLS, file);
                fseek(file,2,SEEK_CUR);
            }

            /* Get text boxes*/
            textBox[0] = current->textIntro;
            textBox[1] = current->textWin;
            textBox[2] = current->textLose;

            for (int i = 0; i < 3; i++) {
                x = 0;
                do checkChar = fgetc(file); while (checkChar == '>');
                if (checkChar == '\0') strcpy(textBox[i], "");
                else while ((checkChar = fgetc(file)) != '>') {
                    if (checkChar == '\n')textBox[i][x++] = ' ';
                    else textBox[i][x++] = checkChar;
                }
                printf("%s\n",textBox[i]);

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

//    /* Terminate on level ordering inconsistency */
//    for (int i = MAX_LEVELS; i > 1; i--) {
//        if (strlen(mapList->level[i].name) &&
//            !strlen(mapList->level[i - 1].name))
//            quit("Inconsistent map file numbering");
//    }

    return mapList;
}


int getFilename(char *filename, char *ext) {
    const char *dotPos = strrchr(filename, '.');
    if (dotPos)
        return !strncmp(++dotPos, ext, strlen(ext));
    return 0;
}


void checkArgs(int argc, char **argv) {

    /* Assess passed directory */

    if (argc > 2) quit("Too Many arguments");

    if (argc == 2) {
        //check passed dir
        //if invalid, abort
    }

    return;
}
