#include "screenshot.h"
#include <sys/types.h>

void ImageFromDisplay(std::vector<char>& Pixels, int& Width, int& Height, int& BitsPerPixel)
{
    Display* display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);

    XWindowAttributes attributes;
    XGetWindowAttributes(display, root, &attributes);

    Width = attributes.width;
    Height = attributes.height;

    XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
    BitsPerPixel = img->bits_per_pixel;
    Pixels.resize(Width * Height * 4);

    Pixels.insert(Pixels.begin(), &img->data[0], &img->data[Pixels.size()]);

    XDestroyImage(img);
    XCloseDisplay(display);
}