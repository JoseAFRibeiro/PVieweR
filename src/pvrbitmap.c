#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glutils.h>
#include "PVRUtils.h"

char *buffer;
unsigned int *headerlessBuff;
unsigned int *tex;

int colorMappedImage(pvr_image_t *image)
 {

     return 0;
 }

int bitmapImage(pvr_image_t* image)
{
    int i = 0;
    int j = 0;

    tex = detwiddle(0, 0, image->height, buffer);

    return 0;
}

int createBitMap(pvr_image_t *image, char *imageBuffer)
{   
    //Ok, not all images have color maps, which was why I wasn't going anywhere
    //Instead  only two image types use them, the rest are bit maps of sorts (not sure if it is the correct term)    

    buffer = imageBuffer;
    switch (image->fileTypebyte1)
    {
    case 0x05:
        
        colorMappedImage(image);
        break;
    
    case 0x06:
        
        colorMappedImage(image);
        break;
    default:

        bitmapImage(image);
        break;
    }

    glMain(tex, image);

    return 0;
} 