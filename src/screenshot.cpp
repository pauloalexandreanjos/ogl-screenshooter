#include "screenshot.h"
#include <sys/types.h>

SSImage::SSImage()
{
    this->display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(this->display);

    XWindowAttributes attributes;
    XGetWindowAttributes(this->display, root, &attributes);

    this->Width = attributes.width;
    this->Height = attributes.height;

    this->image = XGetImage(this->display, root, 0, 0 , this->Width, this->Height, AllPlanes, ZPixmap);
}

SSImage::~SSImage() {
    this->destroy();
}

void SSImage::destroy() {
    XDestroyImage(this->image);
    XCloseDisplay(this->display);
}

void SSImage::CopyData(std::vector<u_char> &Pixels) {
    Pixels.resize(Width * Height * 4);

    Pixels.insert(Pixels.begin(), &this->image->data[0], &this->image->data[Pixels.size()]);
}

XImage* SSImage::getXImage() {
    return this->image;
}

int SSImage::getWidth() {
    return this->Width;
}

int SSImage::getHeight() {
    return this->Height;
}