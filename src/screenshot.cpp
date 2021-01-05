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

    this->image = XGetImage(this->display, root, 0, 0, this->Width, this->Height, AllPlanes, ZPixmap);
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

void SSImage::save() {
    
    /*this->subImage = this->image;
    this->subWidth = this->Width;
    this->subHeight = this->Height;*/

    this->processImage();

    this->save_to_jpeg("./saida.jpeg", 90);
}

void SSImage::processImage() {

    std::vector<unsigned char> image_data_row;

    unsigned long red_mask = this->image->red_mask;
    unsigned long green_mask = this->image->green_mask;
    unsigned long blue_mask = this->image->blue_mask;

    unsigned long pixel;
    unsigned char blue, green, red;
    
    for (int y = 0; y < this->subHeight; y++) {
        for (int x = 0; x < this->subWidth; x++) {
            pixel = XGetPixel(this->image, x + this->subInitWidth, y + this->subInitHeight);

            blue = pixel & blue_mask;
            green = (pixel & green_mask) >> 8;
            red = (pixel & red_mask) >> 16;

            image_data_row.push_back(red);
            image_data_row.push_back(green);
            image_data_row.push_back(blue);
        }
        this->image_data.push_back(image_data_row);
        image_data_row.clear();
    }
}

bool SSImage::save_to_jpeg(const char * path, int quality){
    FILE *fp = NULL;
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPARRAY row;

    fp = fopen(path, "wb");
    if (!fp) {
        std::cout << "Failed to create file " << path << std::endl;
        return false;
    }
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, fp);
    cinfo.image_width = this->subWidth;
    cinfo.image_height = this->subHeight;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality (&cinfo, quality, true);
    jpeg_start_compress(&cinfo, true);
    for(std::vector<std::vector<unsigned char>>::size_type i = 0; i != this->image_data.size(); i++) {
        row = (JSAMPARRAY) &this->image_data[i];
        jpeg_write_scanlines(&cinfo, row, 1);
    }
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    if (fp != NULL) fclose(fp);

    return true;
};

void SSImage::setSubImage(int startX, int startY, int subWidth, int subHeight) {
    this->subInitWidth = startX;
    this->subInitHeight = startY;
    this->subWidth = subWidth;
    this->subHeight = subHeight;
}