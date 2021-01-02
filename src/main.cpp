#include "main.h"

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900

double posicaoX = 0;
double posicaoY = 0;

bool startSelection = false;
bool endSelection = false;

double initPosX = 0;
double initPosY = 0;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width, height, bitsPerPixel;
    std::vector<char> pixels;

    ImageFromDisplay(pixels, width, height, bitsPerPixel);

    // Para fazer full screen deve-se escolhar um monitor
    auto monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    
    //GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Screenshooter", monitor, NULL);
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

    std::cout << "Carregou o GLEW na versão -> " << glewGetString(GLEW_VERSION) << std::endl;
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // TODO: Verificar pois talvez não seja necessário pois essa janela nunca é redimensionada
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shaderTexture(
        "/home/paulo/projetos/cpp/openglexample/src/shaders/texture.vert",
        "/home/paulo/projetos/cpp/openglexample/src/shaders/texture.frag");

    Shader shaderColor(
        "/home/paulo/projetos/cpp/openglexample/src/shaders/color.vert",
        "/home/paulo/projetos/cpp/openglexample/src/shaders/color.frag");

    //Texture texture("/home/paulo/projetos/cpp/openglexample/src/container.jpg");

    Texture texture = Texture(pixels, width, height);

    /*unsigned int VAOtri;
    glGenVertexArrays(1, &VAOtri);  

    initTriangle(VAOtri);*/

    unsigned int VAORet;
    glGenVertexArrays(1, &VAORet);  

    initRetangle(VAORet);

    unsigned int VAOLineV;
    glGenVertexArrays(1, &VAOLineV);  

    initLine(VAOLineV, false);

    unsigned int VAOLineH;
    glGenVertexArrays(1, &VAOLineH);  

    initLine(VAOLineH, true);

    unsigned int VAORectangle;
    glGenVertexArrays(1, &VAORectangle);  

    initLineRectangle(VAORectangle);

    // Wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader *shaders[] = { &shaderTexture, &shaderColor};

    // Desabilita o cursor do mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Callback de posição do mouse
    glfwSetCursorPosCallback(window, mousePositionCallback);
    
    // Callback de clique do mouse
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    std::cout << "Começando o loop da janela..." << std::endl;
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        renderScreen(VAORet, VAOLineV, VAOLineH, VAORectangle, shaders, &texture);
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

float screenXtoGlX(int pos) {
    pos += 1;
    return 2.f * (pos - 1) / (1440 - 1) - 1;
}

float screenYtoGlY(int pos) {
    pos += 1;
    return 2.f * (pos - 1) / (900 - 1) - 1;
}

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mousePositionCallback(GLFWwindow*, double xpos, double ypos) {
    posicaoX = xpos;
    posicaoY = ypos;
}

void mouseButtonCallback(GLFWwindow*, int button, int action, int)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        startSelection = true;
        initPosX = posicaoX;
        initPosY = posicaoY;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        //endSelection = true;
        startSelection = false;
}

/*
    TODO: Criar uma estrutura para agrupar os shaders com identificador proprio para cada
    struct Shaders {
        Shader * textureShader;
        Shader * colorShader;
    }
*/
void renderScreen(unsigned int VAORet, unsigned int VAOLineV, unsigned int VAOLineH, unsigned int VAORectangle, Shader *shaders[2], Texture *texture) {

    Shader* textureShader = shaders[0];
    Shader* colorShader = shaders[1];
    // Passa parametro para o shader
    /*float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaders, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    textureShader->use();
    
    renderRetangle(VAORet, texture->ID);

    colorShader->use();

    if (startSelection) {

        int vertexColorLocation = glGetUniformLocation(colorShader->shaderID, "myPosition");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        float xLoc = screenXtoGlX(posicaoX);
        float yLoc = screenYtoGlY(posicaoY);

        glUniform2f(vertexColorLocation, 0.0f, yLoc);

        renderLine(VAOLineV);

        glUniform2f(vertexColorLocation, xLoc, 0.0f);

        renderLine(VAOLineH);
    } else {
        
        int vertexColorLocation = glGetUniformLocation(colorShader->shaderID, "myPosition");
        glUniform2f(vertexColorLocation, 0.0f, 0.0f);

        renderLines(VAORectangle);
    }
}

void initTriangle(unsigned int VAO) {

    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
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
    /*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);*/

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

}

void renderTriangle(unsigned int VAO) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void initRetangle(unsigned int VAO) {
    
    float vertices[] = {
        // positions          // colors           // texture coords
        1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // top right
        1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f    // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO); 

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // ..:: Initialization code :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); 
}

void renderRetangle(unsigned int VAO, unsigned int texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void initLine(unsigned int VAO, bool horizontal) {

    float vertices[] = {
        // posisions       colors
        /*1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f*/
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    if (!horizontal) {
        vertices[0] = 1.0f;
        vertices[6] = -1.0f;
    } else {
        vertices[1] = 1.0f;
        vertices[7] = -1.0f;
    }

    unsigned int VBO;
    glGenBuffers(1, &VBO); 

    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void renderLine(unsigned int VAO) {
    glBindVertexArray(VAO);
    glLineWidth(3.f);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
}

void initLineRectangle(unsigned int VAO) {
    
    float vertices[] = {
        // posisions       colors
        /*1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f*/
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void renderLines(unsigned int VAO) {
    glBindVertexArray(VAO);
    glLineWidth(1.f);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}
