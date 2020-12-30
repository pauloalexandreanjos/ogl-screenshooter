#ifndef LOAD_SHADERS
#define LOAD_SHADERS

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>

class Shader {
    public:
        unsigned int shaderID;
        Shader(std::string vertexShaderFile, std::string fragmentShaderFile);
        void use();
    private:
        char * loadShader(std::string shaderFile);
        unsigned int createShader(std::string shaderSourceFile, GLenum shaderType);
};

#endif