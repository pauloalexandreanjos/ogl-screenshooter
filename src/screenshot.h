#ifndef SCREENSHOT
#define SCREENSHOT

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <vector>
#include <jpeglib.h>

class SSImage {
    private:
        XImage* image;
        Display* display;
        int Width, Height, subWidth, subHeight, subInitWidth, subInitHeight;
        std::vector<std::vector<unsigned char>> image_data;
        void processImage();
        bool save_to_jpeg(const char * path, int quality);
    public:
        SSImage();
        ~SSImage();
        void setSubImage(int,int,int,int);
        void CopyData(std::vector<u_char>&);
        XImage* getXImage();
        int getWidth();
        int getHeight();
        void destroy();
        void save();
};

#endif