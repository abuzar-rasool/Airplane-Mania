#include "menu.hpp"

// load image using the image path
void Menu::loadImage(SDL_Renderer * rend,std::string path) {
    texture = IMG_LoadTexture(rend, path.c_str());
}  

// set the position and size of the image
void Menu::customize(SDL_Renderer *renderer ,int xC, int yC, int h, int w) {
    frame.x = xC;
    frame.y = yC;   
    frame.h = h;
    frame.w = w;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
}

// this shows the menu on screen
void Menu::show(SDL_Renderer *renderer ) {
    SDL_RenderCopy(renderer, texture, NULL, &frame);
}