#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glutils.h>
#include "PVRUtils.h"

int colorMappedImage()
 {

     return 0;
 }


 int bitmapImage()
 {

     return 0;
 }

int createBitMap(pvr_image_t *image, char *imageBuffer)
{   
    //Ok, not all images have color maps, which was why I wasn't going anywhere
    //Instead  only two image types use them, the rest are bit maps of sorts (not sure if it is the correct term)    

    switch (image->fileTypebyte1)
    {
    case 0x05:
        
        colorMappedImage();
        break;
    
    case 0x06:
        
        colorMappedImage();
        break;
    default:

        bitmapImage();
        break;
    }


} 