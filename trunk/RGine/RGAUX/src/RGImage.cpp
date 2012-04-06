#include "RGImage.h"

RGImage::RGImage()
{
}

RGImage::~RGImage()
{
    if(image != NULL){
        SDL_FreeSurface( image );
    }
}

int RGImage::load(string filename){
    if(image != NULL){
        SDL_FreeSurface( image );
    }
    image = NULL;

    SDL_Surface* loadedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        image = SDL_DisplayFormat( loadedImage );

        SDL_FreeSurface( loadedImage );
    }

    return 0;
}
