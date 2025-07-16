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

    
    
    system(dir_cmd);
    
    
    return 0;
}