/**
 * Before anyone comments with "you could have used memcpy"
 * Yes, I could, but think of this as training for bit shifting, 
 * boolean operations, and I feel it is easier to keep track 
 * of where you are 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint-gcc.h>
#include "PVRUtils.h"

void gbixHeaderImage(char *imageBuffer, pvr_image_t *image)
{
    //retrieve GBIX header parameters, could be optimized with intrinsics?
    //is this even useful for anything?
    int32_t globalIndexLength = 0x00000000;
    int32_t globalIndex = 0x0000000000000000 ;

    char lengthOffset = 4;
    char indexOffset = 8;
    char currOffset = 4;

    for(lengthOffset; lengthOffset <=  currOffset + 4; lengthOffset++)
    {
        globalIndexLength = globalIndexLength << 8;
        globalIndexLength = globalIndexLength | imageBuffer[lengthOffset];
    }

    currOffset = lengthOffset;
    for(currOffset; currOffset <= lengthOffset; currOffset++)
    {
        globalIndex = globalIndex << 8;
        globalIndex = globalIndex | imageBuffer[lengthOffset];
    }
    

    //reading the actual PVR header

    int32_t pvrHdrOffset = GBIXHDR_PVR;
    int32_t currentOffset;
    uint32_t pvrHdr = 0x00000000;
    for(pvrHdrOffset; pvrHdrOffset <= GBIXHDR_PVR + 3; pvrHdrOffset++)
    {
        pvrHdr = pvrHdr << 8;
        pvrHdr = pvrHdr | imageBuffer[pvrHdrOffset];
    }

    if(pvrHdr != PVRHDR)
    {
        printf("Error! PVR header section not found! Either you didn't provide a valid PVR image file or I can't do math, in which case you should submit a bug report or a fix");
        exit(EXIT_FAILURE);
    }
    
    //get the remaining "size"
    currentOffset = pvrHdrOffset;
    uint64_t imageSize = 0; 
        
    for(pvrHdrOffset; pvrHdrOffset < currentOffset + 4; pvrHdrOffset++)
    {
        //printf("Infinite loop! Weeeeeeeeeeeeeeeeeee! \n");
        imageSize = imageSize << 8;
        imageSize = imageSize | imageBuffer[pvrHdrOffset];
        //probably wrong, if you have any idea why this doesn't correspond to the file size as seen by your OS, feel free to fix
        //maybe I'm starting at the wrong position?
    }

    
    //Image type 
 
    image->fileTypebyte1 = imageBuffer[pvrHdrOffset++];
    image->fileTypebyte2 = imageBuffer[pvrHdrOffset++];

    //Image types are represented by 4 bytes but only 2 are actually used. Might be some padding of some sort?
    //to take this into account we add 2 to tthe counter to skip those unsed bytes
    pvrHdrOffset += 2;  
    currentOffset = pvrHdrOffset;
    
    for(pvrHdrOffset; pvrHdrOffset <= currentOffset + 1; pvrHdrOffset++)
    {
        image->width = image->width << 8;

        image->width = image->width | imageBuffer[pvrHdrOffset];
    }

    currentOffset = pvrHdrOffset;
    for(pvrHdrOffset; pvrHdrOffset <= currentOffset + 1; pvrHdrOffset++)
    {
    
        image->height = image->height << 8;
        image->height = image->height | imageBuffer[pvrHdrOffset];
    }

    image->height *= 256;
    image->width *= 256;
    //not how it works
    /*if((image->height % 256 != 0) || (image->width % 256 != 0) )
    {
        printf("Error! Image width or height attribute is invalid. Either you didn't provide a valid PVR image file, or I can't do maths, in which case you should provide a bug report or contributte with a fix!");
        exit(EXIT_FAILURE);
    }*/

    //Image metadata has been read at this point, now it's all about rendering it
}

void headerlessImage(char *imageBuffer, pvr_image_t *image)
{
    return;
}

void displayImage(char *imageBuffer)
{
    //check for GBIX header, could be optimized with intrinsics?

    pvr_image_t image;

    image.fileTypebyte1 = 0;
    image.fileTypebyte2 = 0;
    image.height = 0;
    image.width = 0;
    image.pixelType = 0;

    int i = 0;
    unsigned int header = 0x00000000;

    for(i; i <= 3; i++)
    {
        header = header << 8;
        header = header | imageBuffer[i];
    }
    
    if(header == GBIXHDR)
    {   
        printf("GBIX header found!\n");
        image.hasGBIX = true;
        gbixHeaderImage(imageBuffer, &image);
    }
    else
    {
        image.hasGBIX = false;
        headerlessImage(imageBuffer, &image);
    }

    if((image.fileTypebyte1 != 0x05) || (image.fileTypebyte1 != 0x06))
        printf("This image type doesn't include a color map\n");
        
    int imageReturn = createBitMap(&image, imageBuffer);


}
