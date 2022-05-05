#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

char *readFile(char *path)
{

    FILE *image;
    uint16_t imageSize;
    char *buffer;

    image = fopen(path, "rb");

    if(image == NULL)
    {
        printf("File not found!\n");
        return NULL;
    }

    fseek(image, 0, SEEK_END);
    imageSize = ftell(image);
    rewind(image); 
    buffer = malloc(imageSize);

    if(buffer == NULL)
    {
        printf("Critical error!\n Could not allocate memory buffer for the image!\n");
        return NULL;
    }
    
    fread(buffer, sizeof(char), imageSize, image);
    return buffer;   
}