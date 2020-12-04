#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>

class Menu {
    SDL_Rect frame;
    SDL_Texture *texture;

    public:

    void loadImage(SDL_Renderer * rend,std::string path);
    void customize(SDL_Renderer *renderer ,int xC, int yC, int h, int w);
    void show(SDL_Renderer *renderer );
};