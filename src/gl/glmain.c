#include <stdio.h>
#include "glutils.h"
#include "PVRUtils.h"


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

int glMain(GLFWwindow *win, GLuint *shaderProgram)
{
    const char* vertexSource = "#version 440 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char* fragmentSource = "#version 440 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 inColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = inColor;\n"
    "}\0";

	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};
    
    GLuint VAO, VBO, vShader, fShader;
    char compilationStatus;
    char log[2048];

    if(win == NULL)
        return 2;

    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    glfwSetKeyCallback(win, key_callback);
    glfwMakeContextCurrent(win);
    

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return 3;

    glGenBuffers(1, &VAO);
    glGenVertexArrays(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float) , (void*) 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

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

    shaderProgram = glCreateProgram();
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
    
    return 0;
}

