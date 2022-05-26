#ifndef PVR_UTILS_H
#define PVR_UTILS_H

#include <stdint-gcc.h>
#include <stdbool.h>

//header used in some PVR image files
#define GBIXHDR 0x47424958
//I don't remember what this is but it is important
#define GBIXHDR_PVR 16
//basically PVR in hex
#define PVRHDR 0x50565254
//starting point for the CLUT on an image with the GBIX header
#define GBIXCLUT 0x20
/***
 * same thing but for files without the GBIX header
 ***/
#define PVRCLUT 0x10

/***
 * TODO: rearange the members to save space. Does it even work like that anymore? don't compilers pack structures 
 * automatically in the year of our Lord and Savior of 2022?
***/
typedef struct pvr_image
{
    char fileTypebyte1;
    char fileTypebyte2;
    char pixelType;
    int32_t width;
    int32_t height;
    bool hasGBIX;
}pvr_image_t;

void displayImage(char *imageBuffer);
int createBitMap(pvr_image_t *image, char *imageBuffer);


#endif /* E0C1BC5B_4475_4834_AB52_9176F838419B */
