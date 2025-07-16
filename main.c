#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main() {
    char *file_path = "C:/User/majt1/pictures";
    printf("attempting to copy from: %s", file_path);
    char *dir_cmd = "dir ";
    strcat(dir_cmd, file_path);
    system("dir C:/User/majt1/pictures");
}