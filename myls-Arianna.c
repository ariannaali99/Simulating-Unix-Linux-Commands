/*
    AUTHOR: Arianna Ali
    This program can be executed with up to two additional arguments 
    These are: directory and -l which can be used in any order
    The program will either return the list of files, or the list of 
    file with additional information about the files
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>  
#include <string.h>
#include <time.h>

void printFileInformation(char *file);

int main(int argc, char* argv[]) {
    DIR *folder;
    struct dirent *entry;
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    //If argc == 1, we just list files in directory
    if(argc == 1) {
        //now we need to open and read from the directory
        folder = opendir(cwd);
        if(folder == NULL){
            printf("Error while opening directory\n");
            return 0;
        }
        else{
            while(entry = readdir(folder)){
                if(entry == NULL){
                    break;
                }
                else if(strcmp(entry->d_name, ".") == 0){
                    continue;
                }
                else if(strcmp(entry->d_name, "..") == 0){
                    continue;
                }
                else {
                    printf("%s\n",entry->d_name);
                }
            }
        }
        closedir(folder);
    }
    else if(argc == 2){
        //check if arg is -l
        if(strcmp(argv[1], "-l") == 0){
            //now we need to open and read from the directory
            folder = opendir(cwd);
            if(folder == NULL){
                printf("Error while opening directory\n");
                return 0;
            }
            else{
              printf("Permissions\t User\t\tSize\t\t Time\t\t\t Name\n");
                while(entry = readdir(folder)){
                    if(entry == NULL){
                        break;
                    }
                    else if(strcmp(entry->d_name, ".") == 0){
                        continue;
                    }
                    else if(strcmp(entry->d_name, "..") == 0){
                        continue;
                    }
                    else {
                        printFileInformation(entry->d_name);
                    }
                }
            }
            closedir(folder);
        }
        else {
            folder = opendir(argv[1]);
            if(folder == NULL){
                printf("Error while opening directory\n");
                return 0;
            }
            else {
                while(entry = readdir(folder)){
                    if(entry == NULL){
                        break;
                    }
                    else if(strcmp(entry->d_name, ".") == 0){
                        continue;
                    }
                    else if(strcmp(entry->d_name, "..") == 0){
                        continue;
                    }
                    else {
                        printf("%s\n",entry->d_name);
                    }
                }
            }
            closedir(folder);
        }
    }
    else if(argc == 3){
        if(strcmp(argv[1], "-l") == 0){
            folder = opendir(argv[2]);
            if(folder == NULL){
                printf("Error while opening directory\n");
                return 0;
            }
            else{
              printf("Permissions\t User\t\tSize\t\t Time\t\t\t Name\n");
              int i = 0;
                while(entry = readdir(folder)){
                    if(entry == NULL){
                        break;
                    }
                    else if(strcmp(entry->d_name, ".") == 0){
                        continue;
                    }
                    else if(strcmp(entry->d_name, "..") == 0){
                        continue;
                    }
                    else {
                        char curFile[PATH_MAX];
                        getcwd(curFile, PATH_MAX);
                        printFileInformation(curFile);
                    }
                }
            }
            closedir(folder);
        }
        else if(strcmp(argv[2], "-l") == 0){
            folder = opendir(argv[1]);
            if(folder == NULL){
                printf("Error while opening directory\n");
                return 0;
            }
            else{
              printf("Permissions\t User\t\tSize\t\t Time\t\t\t Name\n");
                while(entry = readdir(folder)){
                    if(entry == NULL){
                        break;
                    }
                    else if(strcmp(entry->d_name, ".") == 0){
                        continue;
                    }
                    else if(strcmp(entry->d_name, "..") == 0){
                        continue;
                    }
                    else {
                        char curFile[PATH_MAX];
                        getcwd(curFile, PATH_MAX);
                        printFileInformation(curFile);
                    }
                }
            }
            closedir(folder);
        }
    }
}

void printFileInformation(char *path){
    struct stat file;

    if(stat(path, &file) == -1) {
        printf("An error occurred while trying to execute.\n");
        return;
    }
    else {
        //File Permissions  user    size    date    name
        int permissions = file.st_mode&0777;
        
        int length = snprintf(NULL, 0, "%o", permissions);
        char perm[length+1];
        snprintf(perm, length + 1, "%o", permissions);
        
        printf("-");
        int i;
        for(i = 0; i < length; i++){
            if(perm[i] == '0'){
                printf("---");
            }
            if(perm[i] == '1'){
                printf("x--");
            }
            if(perm[i] == '2'){
                printf("w--");
            }
            if(perm[i] == '3'){
                printf("wx-");
            }
            if(perm[i] == '4'){
                printf("r--");
            }
            if(perm[i] == '5'){
                printf("rx-");
            }
            if(perm[i] == '6'){
                printf("rw-");
            }
            if(perm[i] == '7'){
                printf("rwx");
            }
        }
        
        //user
        printf("\t%llu",file.st_uid);
       
        //size
        printf("\t\t%d", file.st_size);

        //date
        char* date = ctime(&file.st_mtime);
        date[strlen(date) - 1] = '\0';
        printf("\t%s", date);

        //name of file
        printf("\t%s\n", path);
    }
}