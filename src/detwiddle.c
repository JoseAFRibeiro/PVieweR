/***
 * code for detwiddling PVR textures/images
 * heavily inspired/borrowed from Dan Potter's twiddle.c 
 * over at http://gamedev.allusion.net/softprj
 ***/
#include "PVRUtils.h"
#include "malloc.h"

/*int counter = 0;

void detwiddle( int x1, int y1, int size, uint16_t *texture_ptr, char *texBuffer)
{
    if(size == 1)
    {
        texture_ptr[y1 * size +x1] = texBuffer[counter++];
    } else
    {
        int ns = size/2;
        detwiddle(x1, y1, ns, texture_ptr, texBuffer);
        detwiddle(x1, y1+ns, ns, texture_ptr, texBuffer);
        detwiddle(x1+ns, y1, ns, texture_ptr, texBuffer);
        detwiddle(x1+ns, y1+ns, ns, texture_ptr, texBuffer);    
    }
}*/

int ptr = 0;
int imgsize = 0;
char *twiddled = NULL;
char *detwiddled = NULL;


unsigned short read_pixel() {
	return twiddled[ptr++];
}

void subdivide_and_move(int x1, int y1, int size, int op) {
	if (size == 1) {
		if (op == 0) {		/* Decode */
			detwiddled[y1*imgsize+x1] = read_pixel();
		} else {		/* Encode */
			//write_pixel(detwiddled[y1*imgsize+x1]);
		}
	} else {
		int ns = size/2;
		subdivide_and_move(x1, y1, ns, op);
		subdivide_and_move(x1, y1+ns, ns, op);
		subdivide_and_move(x1+ns, y1, ns, op);
		subdivide_and_move(x1+ns, y1+ns, ns, op);
	}
}
char *detwiddle(int x1, int y1, int size, char *imgBuffer)
{

    twiddled = imgBuffer;
    detwiddled = malloc( size * size * 2);
    subdivide_and_move(x1, y1, size, 0);   
    return detwiddled;
}