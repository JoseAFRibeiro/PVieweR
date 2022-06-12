#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glutils.h>
#include "PVRUtils.h"

char *buffer;
char *tex;

int colorMappedImage(GLint location, pvr_image_t *image, GLFWwindow *win)
 {

     return 0;
 }

 int bitmapImage(GLint location, pvr_image_t *image, GLFWwindow *win)
 {  
     int i = 0;
     int j = 0;

     tex = detwiddle(0,0, image->height, buffer);

     while(!glfwWindowShouldClose(win))
     {

         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT);

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
    buffer = imageBuffer;
    switch (image->fileTypebyte1)
    {
    case 0x05:
        
        colorMappedImage(uniLocation, image, win);
        break;
    
    case 0x06:
        
        colorMappedImage(uniLocation, image, win);
        break;
    default:

        bitmapImage(uniLocation, image, win);
        break;
    }

    glDeleteProgram(shaderp);
    return 0;
} 