#include "unit.hpp"
#pragma once

class Egg: public Unit{
public:
    Egg(SDL_Texture* t):Unit(t){}
    Egg(SDL_Texture* t, SDL_Rect m):Unit(t,m){
        Unit::src = {228,14,132,174};
    }
    
    //overide of virtual function of Unit
    void childDraw(SDL_Renderer* render);
    
    //check if the egg has reached the bottom of the screen.
    bool dropped();
};
