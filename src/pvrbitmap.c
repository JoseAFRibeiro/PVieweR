#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "PVRUtils.h"

int createBitMap(pvr_image_t *image, char *imageBuffer)
{   
    char CLUT[1024];

    uint16_t i;
    int j;

    if(image->hasGBIX == true)
    {
        memcpy(CLUT, imageBuffer + GBIXCLUT, sizeof CLUT);

        j = 1024 + GBIXCLUT;
        
        while(imageBuffer[j] != ('\0' || EOF))
        {
            j++;
        }

        printf("There are %d blocks\r");

    }else if (image->hasGBIX == false)
    {
        memcpy(CLUT, imageBuffer + PVRCLUT, sizeof CLUT);

    }
    
    

    
}