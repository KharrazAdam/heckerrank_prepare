#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <arg1> <arg2> ... <argN>\n", argv[0]);
        return 1;
    }

    // Create the folder name
    char folder_name[256] = {0};
    for (int i = 1; i < argc; i++) {
        strcat(folder_name, argv[i]);
        if (i < argc - 1) {
            strcat(folder_name, "_");
        }
    }

    // Create the directory
    if (mkdir(folder_name, 0777) == -1) {
        perror("Error creating directory");
        return 1;
    }
    printf("Directory '%s' created.\n", folder_name);

    // Create the file inside the directory
    char file_path[300];
    snprintf(file_path, sizeof(file_path), "%s/query.sql", folder_name);

    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }
    // fprintf(file, "This file was created inside %s\n", folder_name);
    // fclose(file);
    // printf("File '%s' created inside the directory.\n", file_path);

    return 0;
}
