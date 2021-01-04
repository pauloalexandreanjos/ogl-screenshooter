#include "Texture.h"
#include "screenshot.h"

Texture::Texture(SSImage& screenImage) {

    std::cout << "Carregando textura" << std::endl;
    glGenTextures(1, &this->ID); 
    glBindTexture(GL_TEXTURE_2D, this->ID); 

    std::cout << "Parametrizando textura" << std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::cout << "Configurando textura..." <<
    " width: " << screenImage.getWidth() << 
    " height: " << screenImage.getHeight() <<
    std::endl;


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenImage.getXImage()->width, screenImage.getXImage()->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, screenImage.getXImage()->data);
    std::cout << "Gerando Mipmap..." << std::endl;
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(std::string textureFile) {

    std::cout << "Carregando textura" << std::endl;
    glGenTextures(1, &this->ID); 
    glBindTexture(GL_TEXTURE_2D, this->ID); 

    std::cout << "Parametrizando textura" << std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const char * filePath = textureFile.c_str();

    int width, height, nrChannels;
    
    std::cout << "Carregando imagem " << textureFile << " do disco..." << std::endl;
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    std::cout << "Canais " << nrChannels << std::endl;

    if (data)
    {
        std::cout << "Configurando textura..." << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        std::cout << "Gerando Mipmap..." << std::endl;
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    std::cout << "Limpando imagem da memoria" << std::endl;
    stbi_image_free(data);

}