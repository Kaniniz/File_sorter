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
    

    //Create the dir command to use in the cli, /OD sorts the list oldest file first, /TC makes it sort after the date the file was created.
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

    
    char *date;
    char *name;
    
    
    while (fgets(file, PATH_MAX, cmd_output) != NULL)   {
        if (strchr(file, ' ') == file || strchr(file, '\\') == file) {
            continue;
        }
        
        //Grab the name of the file listed
        //TODO: Doesn't account for whitespace in file names
        name = strrchr(file, ' ');
        //remove a leading whitespace in the name
        if (name == NULL || name == " .."){
            continue;
        }
        name++;
        
        //Grab the date the file was created
        date = strtok(file, "-");
        printf("Date: %s\nname: %s", date, name); 
        
        //Complete the target folder file path, if folders already exist does nothing
        //TODO: get this part to work. system(mkdir C:\dir\path\name\) works, but getting the full path name is fucking impossible with how shit the string manipulations are in C.
        


    }


    status = pclose(cmd_output);
    if (status == -1) {
        printf("Error during pclose!");
        return -1;
    }
    //printf("%s\n%s\n", source_path, destination_path);
    
    return 0;
}