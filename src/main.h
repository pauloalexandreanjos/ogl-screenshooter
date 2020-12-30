#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "Shader.h"

int main();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void initTriangle(unsigned int);

void renderScreen(unsigned int,Shader*);

void renderTriangle(unsigned int);

void initRetangle(unsigned int);

void renderRetangle(unsigned int, unsigned int s);