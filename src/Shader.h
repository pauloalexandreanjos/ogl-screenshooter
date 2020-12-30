#ifndef LOAD_SHADERS
#define LOAD_SHADERS

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>

class Shader {
    public:
        unsigned int shaderID;
        Shader(std::string vertexShaderFile, std::string fragmentShaderFile);
        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
    private:
        std::string loadShader(std::string shaderFile);
        unsigned int createShader(std::string shaderSourceFile, GLenum shaderType);
};

#endif