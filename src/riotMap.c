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

    char filePath[PATH_MAX];
    bool useCwd = false;
    bool firstRun = true;

    /* Compile regex */
    regcomp(&riotExt, REGEX_EXT, REG_NOSUB | REG_EXTENDED);

    /* Create a new mapList to store map file details */
    mapList = malloc(sizeof(struct MapList));
    mapList->first = malloc(sizeof(struct Map));
    mapList->count = 0;
    current = mapList->first;

    /* Use map directory passed as argument if provided, else cwd */
    if (!loadDir) {
        loadDir = getcwd(loadDir, PATH_MAX);
        useCwd = true;
    }

    /* Attempt to iterate through files in loadDir */
    directory = opendir(loadDir);

    while ((entry = readdir(directory))) {

        sprintf(filePath, "%s/%s", loadDir, entry->d_name);

        /* Skip if not .riot file */
        if (regexec(&riotExt, entry->d_name, 0, NULL, 0)) continue;
        if (!(file = fopen(filePath, "r"))) continue;

        /* Ensure that map size is sufficient */
        fseek(file, 0, SEEK_END);
        if (ftell(file) < MAP_SIZE) continue;
        fseek(file, 0, SEEK_SET);

        /* Move to next element of mapList */
        if(!firstRun) {
            current->next = malloc(sizeof(struct Map));
            current = current->next;
        }

        /* Determine level name (from file name) */
        if (entry->d_name[0] == '_') {
            current->hidden = true;
            memmove(current->name,entry->d_name+1,strlen(entry->d_name)-6);
        } else {
            current->hidden = false;
            memmove(current->name,entry->d_name,strlen(entry->d_name)-5);
        }
        current->beaten = false;

        /* Copy map elements to array */
        for (int i = 0; i < 16; i++) fgets(current->overlay[i], SIZE_X, file);


        /* Determine path */
        //TODO

        current->next = NULL;
        mapList->count++;
        firstRun = false;
    }

    /* Clean up memory */
    closedir(directory);
    if (useCwd) free(loadDir); //getcwd calls malloc, if used must free loadDir

    /* Terminate if no map files where found */
    if (!mapList->count) {
        free(mapList->first);
        free(mapList);
        quit("No map files found");
    }

    return mapList;
}


int getFilename(char *filename, char *ext) {
    const char* dotPos = strrchr(filename, '.');
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



