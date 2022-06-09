#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glutils.h>
#include "PVRUtils.h"

uint16_t *texture_ptr;

int colorMappedImage(GLint location, pvr_image_t *image, char *buffer)
 {

     return 0;
 }

 int bitmapImage(GLint location, pvr_image_t *image, char *buffer, GLFWwindow *win)
 {  
     int i = 0;
     int j = 0;

     detwiddle(0,0, image->height, texture_ptr, buffer);

     while(!glfwWindowShouldClose(win))
     {

         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT);

         for(i; i <=  image->height; i++)
        {
            for(j; j <= image->width; j++)
            {   
                uint8_t r, g, b;
                r = (buffer[GBIXCLUT + (256 * i) + j]) & 0b1111100000000000;
                g = (buffer[GBIXCLUT + (256 * i) + j]) & 0b0000011111100000;
                b = (buffer[GBIXCLUT + (256 * i) + j]) & 0b0000000000011111;

                glUniform4f(location,r, g, b, 1);

                glEnable(GL_SCISSOR_TEST);
                glScissor(j, i, 800, 600);
                glDrawArrays(GL_TRIANGLES,0, 6);
                glDisable(GL_SCISSOR_TEST);
            }
        }

        glfwSwapBuffers(win);
        glfwPollEvents();
     }
     return 0;
 }

int createBitMap(pvr_image_t *image, char *imageBuffer, GLuint shaderp, GLFWwindow *win)
{   
    //Ok, not all images have color maps, which was why I wasn't going anywhere
    //Instead  only two image types use them, the rest are bit maps of sorts (not sure if it is the correct term)    

    GLint uniLocation = glGetUniformLocation(shaderp, "inColor");
    texture_ptr=  malloc(image->width * image->height * 2);

    switch (image->fileTypebyte1)
    {
    case 0x05:
        
        colorMappedImage(uniLocation, image, imageBuffer);
        break;
    
    case 0x06:
        
        colorMappedImage(uniLocation, image, imageBuffer);
        break;
    default:

        bitmapImage(uniLocation, image, imageBuffer, win);
        break;
    }

    glDeleteProgram(shaderp);
    return 0;
} 