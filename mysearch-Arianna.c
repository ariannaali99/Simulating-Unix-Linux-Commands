/*
    AUTHOR: Arianna Ali
    This program can accept at most one argument
    That is, the name of a directory
*/

#include <stdio.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>    
#include <dirent.h>    // opendir, readdir, closedir
#include <string.h>    // strlen, strncpy, strncat
#include <errno.h>

void recSearch(char *path);
void dirSearch(char *directory, char *path);

int main(int argc, char* argv[]){
    
    //If there are no arguments, we use the current directory as the root
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);
    if(argc == 1){
        printf("Root: %s\n", cwd);
        recSearch(cwd);
        printf("Search has finished");
    }
    else if(argc == 2){
        //First, we need to find the directory
        char* directory = argv[1];
        dirSearch(directory, cwd);
        printf("Search has finished");
    }
    else {
        printf("An excessive number of arguments have been provided.\n");
    }
}

void recSearch(char* path){
    //We want to print all the files in this directory
    DIR *folder;
    struct dirent *entry;
    folder = opendir(path);
    if(folder == NULL){
        return;
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
                recSearch(entry->d_name);
            }
        }
    }
    closedir(folder);
}

void dirSearch(char *directory, char *path) {
    DIR *folder;
    struct dirent *entry;
    folder = opendir(path);
    if(folder == NULL){
        return;
    }
    else{
        while(entry = readdir(folder)){
            if(entry == NULL){
                continue;
            }
            else if(strcmp(entry->d_name, ".") == 0){
                continue;
            }
            else if(strcmp(entry->d_name, "..") == 0){
                continue;
            }
            else if(strcmp(entry->d_name, directory) == 0) {
                char root[PATH_MAX];
                getcwd(root, PATH_MAX);
                printf("Selected path: %s\n", root);
                recSearch(entry->d_name);
                return;

            }
            else{
                dirSearch(directory, entry->d_name);
            }
        }
    }
    closedir(folder);
}