#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glutils.h>
#include "PVRUtils.h"


int colorMappedImage(GLint location, pvr_image_t *image)
 {

     return 0;
 }


 int bitmapImage(GLint location, pvr_image_t *image)
 {  
     int i = 0;
     int j = 0;

     detwiddle(0,0, image->height);
     for(i; i <=  image->height; i++)
     {
        for(j; j <= image->width; j++)
        {   
            glUniform4f()
        }
     }
     return 0;
 }

int createBitMap(pvr_image_t *image, char *imageBuffer, GLuint shaderp)
{   
    //Ok, not all images have color maps, which was why I wasn't going anywhere
    //Instead  only two image types use them, the rest are bit maps of sorts (not sure if it is the correct term)    

    GLint uniLocation = glGetUniformLocation(shaderp, "inColor");
    char *buffer = imageBuffer;
    uint16_t texture_ptr = malloc(image->width * image->height * 2);

    switch (image->fileTypebyte1)
    {
    case 0x05:
        
        colorMappedImage(uniLocation, image);
        break;
    
    case 0x06:
        
        colorMappedImage(uniLocation, image);
        break;
    default:

        bitmapImage(uniLocation, image);
        break;
    }


} 