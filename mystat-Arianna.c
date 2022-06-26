/*  
    AUTHOR: Arianna Ali
    Input: ./executable ./fileName OR ./executable fileName
    This program requires the name of a file in the current directory
    After being executed, it will return information about the named file
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    //Terminal input is ./mystat ./filename so we need argc = 2
    if(argc < 2) {
        printf("Incufficient arguments provided.\n");
        return 0;
    }
    else if(argc > 2) {
        printf("Excessive arguments provided.\n");
        return 0;
    }
    else if(argc == 2) {
        //We need to check if the file is valid
        struct stat file;
        char* path = argv[1];
        //stat(path, &file);

        if(stat(path, &file) == -1) {
            printf("An error occurred while trying to execute.\n");
            return 0;
        }
        else {
            int blocks = 1;
            printf("File Information of %s\n", path);
            printf("File Size: %d\n", file.st_size);
            printf("Number of Blocks Allocated: %d\n", file.st_blocks);
            printf("Number of Links: %d\n", file.st_nlink);

            //This holds the dec number, but we need the octal number
            int permissions = file.st_mode&0777;
            
            //Hence, we use %o to format it into string
            int length = snprintf(NULL, 0, "%o", permissions);
            char perm[length+1];
            snprintf(perm, length + 1, "%o", permissions);
            
            printf("File Permissions: -");
            int i = 0;
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
            printf("\nFile Inode: %d\n", file.st_ino);
            return 0;
        }
    }
}