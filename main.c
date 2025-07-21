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

    char source_path_copy[PATH_MAX];
    
    strncpy(source_path_copy, source_path, strlen(source_path)-1);

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
    strcat(dir_cmd, "\" /a-d /od /tc");

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
    char make_dir_cmd[PATH_MAX];
    
    
    
    while (fgets(file, PATH_MAX, dir_cmd_output) != NULL || fgets(file_names, PATH_MAX, file_names_dir_cmd_output))   {
        if (strchr(file, ' ') == file || strchr(file, '\\') == file || strrchr(file, ' ') == NULL) {
            continue;
        }
        strcpy(make_dir_cmd, "");
        
        strcat(make_dir_cmd, "mkdir ");
        strncat(make_dir_cmd, destination_path, strlen(destination_path)-1);
        //Grab the date the file was created, I know this looks awful but it's what i know works and I really just wanna get this first project working. Getting style points for clean code isn't the goal of my first personal project. 
        strcat(make_dir_cmd, "\\");
        date = strtok(file, "-");
        strcat(make_dir_cmd, date);
        strcat(make_dir_cmd, "\\");
        date = strtok(NULL, "-");
        strcat(make_dir_cmd, date);
        strcat(make_dir_cmd, "\\");
        date = strtok(NULL, "  ");
        strcat(make_dir_cmd, date);
        
        printf("make dir cmd: %s\n", make_dir_cmd);

        
        //Complete the target folder file path, if folders already exist does nothing
        //TODO: get this part to work. system(mkdir C:\dir\path\name\) works, but getting the full path name is fucking impossible with how shit the string manipulations are in C.
        


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