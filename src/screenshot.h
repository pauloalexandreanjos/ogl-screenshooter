#ifndef SCREENSHOT
#define SCREENSHOT

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <vector>

void ImageFromDisplay(std::vector<char>& Pixels, int& Width, int& Height, int& BitsPerPixel);

#endif