#include <string>
#include <iostream>
#include <GL/glew.h>

#include "stb_image.h"

class Texture {
    public:
        unsigned int ID;
        Texture(std::string textureFile);
};