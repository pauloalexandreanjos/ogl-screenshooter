#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <array>
#include <vector>
/*#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"*/

#include "Shader.h"
#include "Texture.h"
#include "screenshot.h"

int main();

void framebuffer_size_callback(GLFWwindow* , int , int);

void processInput(GLFWwindow *);

void initTriangle(unsigned int);

void renderScreen(unsigned int,unsigned int,unsigned int,Shader* [2],Texture*);

void renderTriangle(unsigned int);

void initRetangle(unsigned int);

void renderRetangle(unsigned int, unsigned int);

void initLine(unsigned int, bool);

void renderLine(unsigned int);

void mousePositionCallback(GLFWwindow*, double, double);

void mouseButtonCallback(GLFWwindow*, int, int, int);

float screenXtoGlX(int);

float screenYtoGlY(int);

void initLineRectangle(unsigned int,float,float);

void renderLines(unsigned int);

void cutImage(SSImage&);