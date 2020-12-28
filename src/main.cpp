#include "main.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void createShaders(SHADERS *shaders) {

    shaders->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::cout << "vertexShader " << shaders->vertexShader << std::endl;

    glShaderSource(shaders->vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(shaders->vertexShader);

    int  success;
    GLchar infoLog[512];
    glGetShaderiv(shaders->vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shaders->vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaders->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::cout << "fragmentShader " << shaders->fragmentShader << std::endl;

    glShaderSource(shaders->fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(shaders->fragmentShader);
}

unsigned int createShaderProgram() {

    SHADERS shaders;
    createShaders(&shaders);
    std::cout << "vertexShader fora " << shaders.vertexShader << std::endl;
    std::cout << "fragmentShader fora " << shaders.fragmentShader << std::endl;

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, shaders.vertexShader);
    glAttachShader(shaderProgram, shaders.fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
    std::cout << "glUseProgram " << shaderProgram << std::endl;

    glDeleteShader(shaders.vertexShader);
    glDeleteShader(shaders.fragmentShader); 
    std::cout << "Deletou os shaders " << std::endl;

    return shaderProgram;
}

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "Erro ao inicializar o glew: " << glewGetErrorString(err) << std::endl;
    }

    std::cout << "Sucesso: " << glewGetString(GLEW_VERSION) << std::endl;
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    auto shaderProgram = createShaderProgram();

    std::cout << "Sucesso createShaderProgram" << std::endl;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  

    initTriangle(VAO);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        renderScreen(VAO, shaderProgram);
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void renderScreen(unsigned int VAO, unsigned int shaderProgram) {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    renderTriangle(VAO, shaderProgram);
}

void initTriangle(unsigned int VAO) {

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO); 

    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
}

void renderTriangle(unsigned int VAO, unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}