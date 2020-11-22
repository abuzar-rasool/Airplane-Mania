#pragma once
#include "unit.hpp"
#include <iostream>
class Pigeon : public Unit
{
    int eggsLaid;    //no. of eggs laid
    bool baby;       // is it a baby pigeon?
    SDL_Rect src[3]; // three textures, to make the fly animation
    int frame;
    int flip = false;

public:
    Pigeon(SDL_Texture *texture, SDL_Rect position, bool isBaby) : Unit(texture, position), baby(isBaby)
    {
        //Set 3 image sources
        src[0] = {0, 0, 160, 133};
        src[1] = {0, 133, 160, 133};
        src[2] = {0, 266, 160, 133};
        frame = 0;
    };
    //This is the main function responsible of movement of the pigeon on the screen.
    //It also helps the baby pigeons grows!
    void animate();
    
    //overide of virtual function of Unit
    void childDraw(SDL_Renderer *render);

    //Checks that pigeon should lay egg or not on 2% probablity
    bool layEgg();

    //If pigeon has laid more than 4 eggs then kill it.
    bool isAlive();
};