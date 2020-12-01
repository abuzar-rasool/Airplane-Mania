#include "SDL.h"
#include <iostream>
#pragma once
class Unit
{
protected:
    SDL_Texture *assets;
    SDL_Rect src;
    SDL_Rect mover;
    int angle = 20;

public:
    Unit(SDL_Texture *texture) : assets(texture){};
    Unit(SDL_Texture *texture, SDL_Rect initpos) : assets(texture), mover(initpos){};
    Unit(SDL_Texture *texture, SDL_Rect initpos,int a) : assets(texture), mover(initpos),angle(a){};


    //regular draw of objects the flip can be used to flip the image 
    void draw(SDL_Renderer *render, bool flip = false);

    //implements wobble animation by changing image angles
    void wobbledraw(SDL_Renderer *render);

    //360 degrees animation draw
    void rotation(SDL_Renderer *render);

    //inclined draw
    void incline(SDL_Renderer *render, int a,bool flip);


    //virtual function of Unit
    //This is overrided by every other class it is parent of this calls extra function before draw
    //is called.
    virtual void childDraw(SDL_Renderer *render) = 0;

    SDL_Rect getMover();
};