#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include "glutils.h"

void framebuffer_size_callback(GLFWwindow *win, GLint width, GLint height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    }
}

void GLAPIENTRY messageCallBack(GLenum source, GLenum type, GLenum id, GLenum severity,
                                GLsizei length, const GLchar *message, const void *userParam)
{
    printf("GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message);
}

int glMain(int *buffer , pvr_image_t *image)
{ 
    const char* vertexSource = "#version 440 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 inTexCoord;\n"
    "layout (location = 2) in vec3 inColor;\n"
    "out vec2 TexCoord;\n"
    "out vec3 Color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   TexCoord = inTexCoord;\n"
    "   Color = inColor;\n"
    "}\0";

    const char* fragmentSource = "#version 440 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"
    "in vec3 Color;\n"
    "uniform sampler2D Tex;\n"
    "void main()\n"
    "{\n"
    " FragColor = texture(Tex, TexCoord);\n"
    "}\0";

    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  
    };

    int indices [] ={
        0,1,3,
        1,2,3
    };

    int VAO, VBO, EBO, vShader, fShader, texture;
    char compilationStatus;
    char log[2048];

    if(!glfwInit())
        return 1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *winptr = glfwCreateWindow(800, 600, "DreamViewer", NULL, NULL);

    if(winptr == NULL)
        return 2;

    glfwSetFramebufferSizeCallback(winptr, framebuffer_size_callback);
    glfwSetKeyCallback(winptr, key_callback);
    glfwMakeContextCurrent(winptr);
    

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return 3;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallBack, 0);



    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertexSource, NULL);
    glCompileShader(vShader);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &compilationStatus);

    if(!compilationStatus)
    {
        printf("Vertex shader compilation error\n");
    }

    fShader = glCreateShader(GL_FRAGMENT_SHADER) ;
    glShaderSource(fShader, 1, &fragmentSource, NULL);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &compilationStatus);

    if(!compilationStatus)
    {
        printf("Fragment shader compilation error\n");
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compilationStatus);
    if(!compilationStatus)
    {   
        glGetProgramInfoLog(shaderProgram, 2048, NULL, log);
        printf("Error compiling shader program\n %s", log);
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    
    glUseProgram(shaderProgram);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //int width, height, channels;
    //unsigned char *data = stbi_load("C:\\Users\\Casa\\Desktop\\programas\\C\\PVieweR\\res\\wall.jpg", &width, &height, &channels, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB565, GL_UNSIGNED_INT, buffer);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    //stbi_image_free(data);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(winptr))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(winptr);
        glfwPollEvents();

    }

    glDeleteProgram(shaderProgram);

    return 0;
}
