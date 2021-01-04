#ifndef SCREENSHOT
#define SCREENSHOT

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <vector>

class SSImage {
    private:
        XImage* image;
        Display* display;
        int Width, Height;
    public:
        SSImage();
        ~SSImage();
        void CopyData(std::vector<u_char>&);
        XImage* getXImage();
        int getWidth();
        int getHeight();
        void destroy();
};

#endif