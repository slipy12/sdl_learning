#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//Texture wrapper class
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path, SDL_Renderer* renderer );

        //Deallocates texture
        void free();

        //Renders texture at given point
        void render( int x, int y, SDL_Renderer* renderer );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};