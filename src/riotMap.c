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

    char path[PATH_MAX], line[MAX_COLS];
    bool useCwd = false;
    bool firstRun = true;

    int x,y;

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

            /* Determine level number and hidden status from filename*/
            if(entry->d_name[0]=='.') {
                current = &mapList->level[entry->d_name[1]-'0'];
                current->levelNo = entry->d_name[1]-'0';
                current->hidden=false;
            } else{
                current = &mapList->level[entry->d_name[0]-'0'];
                current->levelNo = entry->d_name[0]-'0';
                current->hidden=true;
            }

            /* Assign beaten status */
            current->beaten = false;

            /* Determine level name*/
            rewind(file);
            fgets(line,MAX_COLS,file);
            strncpy(current->name,strtok(line,DELIMITER),LINE_MAX);

            /* Determine starting rep */
            current->repMax=atoi(strtok(NULL,DELIMITER));

            /* Determine panic threshold */
            current->panicMax=atoi(strtok(NULL,DELIMITER));

            /* Determine level inmates*/
            strncpy(current->inmates,strtok(NULL,"\n"),INMATE_TYPES);

            /* Copy map elements to array */
            rewind(file);
            while (fgetc(file) != '\n');
            while (fgetc(file) != '\n');
//            fseek(file, 1, SEEK_CUR);
            for ( y = 0; y < MAP_ROWS; y++) {
                fseek(file, 7, SEEK_CUR);
                for( x = 0; x < MAP_COLS-1; x++)
                    current->overlay[y][x] = fgetc(file);
                fseek(file, 3, SEEK_CUR);
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
