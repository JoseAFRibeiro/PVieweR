#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "fileIO.h"
#include "PVRUtils.h"

int main(int argc, char const *argv[])
{
    if(argc <= 1)
    {
        printf("Not enough parameters. This program requires you to input the file path as an argument");
        exit(1);
    }
    else if (argc > 2)
    {
        printf("Error, too many arguments! Please only input the file path");
        exit(1);
    }

    char path[300];
    char *imageBuffer;

    strncpy(path, argv[1], 299);
    imageBuffer = readFile(path);
    
    displayImage(imageBuffer);

    free(imageBuffer);
    return 0;
}
