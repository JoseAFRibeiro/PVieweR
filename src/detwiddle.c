/***
 * code for detwiddling PVR textures/images
 * heavily inspired/borrowed from Dan Potter's twiddle.c 
 * over at http://gamedev.allusion.net/softprj
 ***/
#include "PVRUtils.h"

int counter = 0;

void detwiddle( int x1, int y1, int size)
{
    if(size == 1)
    {
        texture_ptr[y1 * size +x1] = buffer[counter];
    } else
    {
        int ns = size/2;
        detwiddle(x1, y1, ns);
        detwiddle(x1, y1+ns, ns);
        detwiddle(x1+ns, y1, ns);
        detwiddle(x1+ns, y1+ns, ns);    
    }
}