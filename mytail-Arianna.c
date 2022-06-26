/*
    AUTHORS: Arianna Ali
    The program will accept two additional arguments
    That is: n (number of lines to extract) and name of file
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

    if(argc == 3){
        //Step 1: figure out which argument is the filename
        struct stat file;
        char* path = argv[1];
        int fileName;

        if(stat(path, &file) == -1){
            //This is not the right argument
            path = argv[2];
            if(stat(path, &file) == -1){
                printf("No such files exist.\n");
            }
            //fileName is arg2
            else {
                //Open file
                fileName = open(path, O_RDONLY);
                if(fileName < 0){
                    printf("Error, could not open file.\n");
                    return 0;
                }

                //How many lines do we need to print?
                int lines = atoi(argv[1]);

                //lseek command to read near the end of the file
                int i = -1;
                lseek(fileName, i, SEEK_END);

                //read from file
                int numChars = 1;
                //Need buffer to hold information from file
                char buffer[10000];
                char* check;

                //Perhaps we can read char by char and count the lines
                while(lines > 0) {
                    read(fileName, buffer, numChars);
                    check = buffer;

                    //if we find a end line char we decrement lines
                    if(*check == '\n'){
                        --lines;
                    }
                    ++check;
                    numChars += 1;
                    
                    //update lseek
                    --i;
                    lseek(fileName, i, SEEK_END);
                }
                printf("%s\n", buffer);
                close(fileName);
            }

        }
        //fileName is arg1
        else {
            //Open file
            fileName = open(path, O_RDONLY);
            if(fileName < 0){
                printf("Error, could not open file.\n");
                return 0;
            }

            //How many lines do we need to print?
            int lines = atoi(argv[2]);

            //lseek command to read near the end of the file
            int i = -1;
            lseek(fileName, i, SEEK_END);

            //read from file
            int numChars = 1;
            //Need buffer to hold information from file
            char buffer[10000];
            char* check;

            //Perhaps we can read char by char and count the lines
            while(lines > 0) {
                read(fileName, buffer, numChars);
                check = buffer;

                //if we find a end line char we decrement lines
                if(*check == '\n'){
                    --lines;
                }

                ++check;
                numChars += 1;

                //update lseek
                --i;
                lseek(fileName, i, SEEK_END);
            }
            printf("%s\n", buffer);
            close(fileName);
        }

    }
    else {
        printf("Insufficient arguments provided.\n");
        return 0;
    }
}