#include "Shader.h"
#include <iostream>
#include <string>

Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile) {

    unsigned int vertexShader = this->createShader(
        vertexShaderFile,
        GL_VERTEX_SHADER);

    unsigned int fragmentShader = this->createShader(
        fragmentShaderFile,
        GL_FRAGMENT_SHADER);

    std::cout << "Criou os shaders" << std::endl;

    this->shaderID = glCreateProgram();

    glAttachShader(this->shaderID, vertexShader);
    glAttachShader(this->shaderID, fragmentShader);
    glLinkProgram(this->shaderID);

    int success;
    GLchar infoLog[512];
    glGetProgramiv(this->shaderID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(this->shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    std::cout << "Deletou os shaders " << std::endl;
}

std::string Shader::loadShader(std::string shaderName) {
    std::ifstream file;

    std::cout << "Tentando abrir o arquivo " << shaderName << std::endl;
    file.open(shaderName, std::fstream::in | std::ifstream::binary);

    if (!file.is_open()) {
        std::cout << "Arquivo não abriu" << std::endl;
        return nullptr;
    }

    /*file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    fragmentShaderSource = new char[length+1];

    file.read(fragmentShaderSource, length);

    fragmentShaderSource[length] = '\0';*/

    std::stringstream source;

    source << file.rdbuf();

    file.close();
    std::cout << "Fechou o arquivo" << std::endl;

    return source.str();
}

unsigned int Shader::createShader(std::string shaderSourceFile, GLenum shaderType) {

    unsigned int shaderId = glCreateShader(shaderType); // GL_VERTEX_SHADER | GL_FRAGMENT_SHADER
    std::cout << "Compilando o shader >> " << shaderId << " <<" << std::endl;

    std::string shaderSource = loadShader(shaderSourceFile);
    const char *shaderSourceCode = shaderSource.c_str();

    glShaderSource(shaderId, 1, &shaderSourceCode, NULL);
    glCompileShader(shaderId);

    int  success;
    GLchar infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "Shader >> " << shaderId << " << compilado com sucesso!" << std::endl;
    }

    return shaderId;
}

void Shader::use() {
    glUseProgram(this->shaderID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(this->shaderID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(this->shaderID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(this->shaderID, name.c_str()), value); 
}