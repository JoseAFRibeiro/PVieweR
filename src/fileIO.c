#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

char *readFile(char *path)
{

    FILE *image;
    long long imageSize;
    char *buffer;

    image = fopen(path, "rb");

    if(image == NULL)
    {
        printf("File not found!\n Please provide a valid file path!");
        exit(EXIT_FAILURE);
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
    
    size_t result = fread(buffer, sizeof(char), imageSize, image);
    fclose(image);
    
    return buffer;   
}