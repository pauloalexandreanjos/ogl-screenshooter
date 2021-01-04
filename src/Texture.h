#ifndef TEXTURE
#define TEXTURE

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <vector>

#include "stb_image.h"
#include "screenshot.h"

class Texture {
    public:
        unsigned int ID;
        Texture(SSImage&);
        Texture(std::string textureFile);
};

#endif