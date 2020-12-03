#pragma once
#include <SDL.h>
#include <string>

class Menu {
    SDL_Rect frame;
    SDL_Renderer * renderer;

    public:

    void customize(SDL_Renderer *renderer ,int xC, int yC, int h, int w) {
        frame.x = xC;
        frame.y = yC;
        frame.y = h;
        frame.w = w;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    }

    void show() {
        SDL_RenderFillRect( renderer, &frame);
        SDL_RenderPresent(renderer);
    }

};