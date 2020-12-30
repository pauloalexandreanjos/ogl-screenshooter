#include "Shader.h"
#include <iostream>

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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    std::cout << "Deletou os shaders " << std::endl;
}

char * Shader::loadShader(std::string shaderName) {
    std::fstream file;

    char *fragmentShaderSource;

    std::cout << "Tentando abrir o arquivo " << shaderName << std::endl;
    file.open(shaderName, std::fstream::in | std::ifstream::binary);

    if (!file.is_open()) {
        std::cout << "Arquivo não abriu" << std::endl;
        return nullptr;
    }

    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    fragmentShaderSource = new char[length+1];

    file.read(fragmentShaderSource, length);

    fragmentShaderSource[length] = '\0';

    file.close();
    std::cout << "Fechou o arquivo" << std::endl;

    return fragmentShaderSource;
}

unsigned int Shader::createShader(std::string shaderSourceFile, GLenum shaderType) {

    unsigned int shaderId = glCreateShader(shaderType); // GL_VERTEX_SHADER | GL_FRAGMENT_SHADER
    std::cout << "Compilando o shader >> " << shaderId << " <<" << std::endl;

    char *shaderSource = loadShader(shaderSourceFile);

    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);

    delete[] shaderSource;

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