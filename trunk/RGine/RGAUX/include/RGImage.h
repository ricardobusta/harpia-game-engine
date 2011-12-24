#ifndef RGIMAGE_H
#define RGIMAGE_H

/** load image using SDL functions. */

#include "SDL/SDL_image.h"

#include <string>
using namespace std;

class RGImage
{
    public:
        RGImage();
        virtual ~RGImage();

        int load(string filename);
    protected:
    private:
        SDL_Surface *image;
};

#endif // RGIMAGE_H
