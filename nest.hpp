#include "unit.hpp"
#pragma once
class Nest: public Unit{
public:
    Nest(SDL_Texture* texture, SDL_Rect m):Unit(texture,m){
        src={176,200,269,206};
    };
    //overide of virtual function of Unit
    void childDraw(SDL_Renderer* render);
};
