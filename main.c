#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char source_path[PATH_MAX];
    char destination_path[PATH_MAX];

    printf("Which folder do you want to copy?\n");
    fgets(source_path, sizeof(source_path), stdin);
    if (source_path == NULL) {
        printf("Failed to get input");
        return 1;
    }

    printf("Where should the copys go?\n");
    fgets(destination_path, sizeof(destination_path), stdin);
    if (destination_path == NULL) {
        printf("Failed to get input");
        return 1;
    }
    printf("attempting to copy contents of %s\nTo the destination of: %s\n", source_path, destination_path);

    char dir_cmd[PATH_MAX];
    strcpy(dir_cmd, "dir \"");
    strcat(dir_cmd, source_path);
    strcat(dir_cmd, "\" /OD /TC");

    FILE *cmd_output;
    int status;
    char file[PATH_MAX];

    cmd_output = popen(dir_cmd, "r");
    if (cmd_output == NULL) {
        printf("Error executing dir command!\n");
        return -1;
    }
    
    int i = 0;
    printf("%s\n", cmd_output);
    while (fgets(file, PATH_MAX, cmd_output) != NULL)   {
        printf("Files: %s", file);
        i++;
        printf("%i\n", strlen(file));
    }


    status = pclose(cmd_output);
    if (status == -1) {
        printf("Error during pclose!");
        return -1;
    }
    printf("%s\n%s\n", source_path, destination_path);
    
    return 0;
}