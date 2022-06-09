/***
 * code for detwiddling PVR textures/images
 * heavily inspired/borrowed from Dan Potter's twiddle.c 
 * over at http://gamedev.allusion.net/softprj
 ***/
#include "PVRUtils.h"

int counter = 0;

void detwiddle( int x1, int y1, int size, uint16_t *texture_ptr, char *texBuffer)
{
    if(size == 1)
    {
        texture_ptr[y1 * size +x1] = texBuffer[counter];
    } else
    {
        int ns = size/2;
        detwiddle(x1, y1, ns, texture_ptr, texBuffer);
        detwiddle(x1, y1+ns, ns, texture_ptr, texBuffer);
        detwiddle(x1+ns, y1, ns, texture_ptr, texBuffer);
        detwiddle(x1+ns, y1+ns, ns, texture_ptr, texBuffer);    
    }
}