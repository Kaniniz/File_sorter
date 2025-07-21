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
    
    
    /*
    Create the dir command to use in the cli
    /a-d removes directories from the list
    /od sorts the list oldest file first
    /tc makes it sort after the date the file was created.
    
    */
    char dir_cmd[PATH_MAX];
    strcpy(dir_cmd, "dir \"");
    strncat(dir_cmd, source_path, strlen(source_path)-1); //strlen(source_path)-1 is added to not copy a trailing linebreak which causes problems with the cli command.
    strcat(dir_cmd, "\" /a-d-h /od /tc");

    char dir_cmd_for_names[PATH_MAX];
    strcpy(dir_cmd_for_names, dir_cmd);
    strcat(dir_cmd_for_names, " /b");

    FILE *dir_cmd_output;
    int status;
    char file[PATH_MAX];

    FILE *file_names_dir_cmd_output;
    int file_name_status;
    char file_names[PATH_MAX];

    dir_cmd_output = popen(dir_cmd, "r");
    if (dir_cmd_output == NULL) {
        printf("Error executing dir command!\n");
        return -1;
    }

    file_names_dir_cmd_output = popen(dir_cmd_for_names, "r");
    if (file_names_dir_cmd_output == NULL) {
        printf("Error executing file name dir command!\n");
        return -1;
    }

    
    char *date;
    char *name;
    char destination[PATH_MAX];
    char mkdir_cmd[PATH_MAX];
    char copy_cmd[PATH_MAX];
    
    
    while (fgets(file, PATH_MAX, dir_cmd_output) != NULL)   {
        if (strchr(file, ' ') == file || strchr(file, '\\') == file || strrchr(file, ' ') == NULL) {
            continue;
        }
        
        strcpy(mkdir_cmd, "mkdir ");
        strcpy(destination, "\"");
        strcpy(copy_cmd, "copy \"");
        
        
        strncat(destination, destination_path, strlen(destination_path)-1);
        strcat(destination, "\\");
        //Grab the date the file was created and finish destiantion file path, I know this looks awful but it's what i know works and I really just wanna get this first project working. Getting style points for clean code isn't the goal of my first personal project. 
        date = strtok(file, "-");
        strcat(destination, date); //Year
        strcat(destination, "\\");
        
        date = strtok(NULL, "-");
        strcat(destination, date); //Month
        strcat(destination, "\\");
        
        date = strtok(NULL, "  ");
        strcat(destination, date); // Day
        strcat(destination, "\"");
        
        //Creates all folders for year, month and day, if folders already exist does nothing
        strcat(mkdir_cmd, destination);
        printf("mkdir cmd: %s\n", mkdir_cmd);
        system(mkdir_cmd);

        //Finish the Copy cmd and copy the file.
        fgets(file_names, PATH_MAX, file_names_dir_cmd_output);
        
        strncat(copy_cmd, source_path, strlen(source_path)-1);
        strcat(copy_cmd, "\\");
        strncat(copy_cmd, file_names, strlen(file_names)-1);
        strcat(copy_cmd, "\" ");
        strcat(copy_cmd, destination);

        system(copy_cmd);

    }


    status = pclose(dir_cmd_output);
    if (status == -1) {
        printf("Error during pclose!");
        return -1;
    }

    file_name_status = pclose(file_names_dir_cmd_output);
    if (file_name_status == -1) {
        printf("Error during file name pclose!");
        return -1;
    }
    
    return 0;
}