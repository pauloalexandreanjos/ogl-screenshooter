#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>

struct SHADERS {
    unsigned int vertexShader;
    unsigned int fragmentShader;
};

void createShaders(SHADERS *shaders);

unsigned int createShaderProgram();

int main();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void initTriangle(unsigned int);

void renderScreen(unsigned int,unsigned int);

void renderTriangle(unsigned int,unsigned int);