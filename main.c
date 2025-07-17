#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char file_path[100];
    
    printf("Which folder should do you want to list?\n");
    fgets(file_path, sizeof(file_path), stdin);
    if (file_path == NULL) {
        printf("Failed to get input");
        return 1;
    }
    printf("attempting to list contents in folder %s\n", file_path);
    
    char dir_cmd[100];
    strcpy(dir_cmd, "dir \"");
    strcat(dir_cmd, file_path);
    strcat(dir_cmd, "\" /OD /TC");
    printf("Command: %s\n", dir_cmd);

    FILE *fp;
    int status;
    char path[PATH_MAX];

    fp = popen(dir_cmd, "r");
    if (fp == NULL) {
        printf("Error executing dir command!\n");
        return -1;
    }

    while (fgets(path, PATH_MAX, fp) != NULL)
    printf("Files: %s", path);

    status = pclose(fp);
    if (status == -1) {
        printf("Error during pclose!");
        return -1;
    }
    return 0;
}