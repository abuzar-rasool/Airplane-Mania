#include "menu.hpp"

void Menu::loadImage(SDL_Renderer * rend,std::string path) {
    texture = IMG_LoadTexture(rend, path.c_str());
}  

void Menu::customize(SDL_Renderer *renderer ,int xC, int yC, int h, int w) {
    frame.x = xC;
    frame.y = yC;   
    frame.h = h;
    frame.w = w;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
}

void Menu::show(SDL_Renderer *renderer ) {
    SDL_RenderCopy(renderer, texture, NULL, &frame);
}