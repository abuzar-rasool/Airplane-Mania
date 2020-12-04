#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>

class Menu {
    SDL_Rect frame;
    SDL_Texture *texture;

    public:

    // loads images using image file path
    void loadImage(SDL_Renderer * rend,std::string path);
    // customizes image's position and size
    void customize(SDL_Renderer *renderer ,int xC, int yC, int h, int w);
    // shows the image on screen
    void show(SDL_Renderer *renderer );
};