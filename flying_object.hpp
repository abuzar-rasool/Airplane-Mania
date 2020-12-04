#pragma once
#include "unit.hpp"
#include <iostream>
class FlyingObject : public Unit
{
protected:
    bool flip;
    int frame = 0;
    bool still_flying = true;
    bool randomBool()
    {
        return rand() > (RAND_MAX / 2);
    }

public:
    // constructor for flyingobject class that takes texture, width, and height
    FlyingObject(SDL_Texture *texture, int width = 40, int height = 40) : Unit(texture)
    {   
        // getting random bool value
        flip = randomBool();
        // getting random position between 0 and 400
        int rend_pos_y = rand() % 400;
        SDL_Rect spawn_position;

        // checking for flip condition
        if (flip)
        {
            spawn_position = {800, rend_pos_y, width, height};
        }
        else
        {
            spawn_position = {0, rend_pos_y, width, height};
        }
        Unit::mover = spawn_position;
    };

    // overloaded constructor
    FlyingObject(SDL_Texture *texture,SDL_Rect spawn_position,int angle=0,int width = 40, int height = 40) : Unit(texture,spawn_position,angle)
    {
        flip = false;
    };
    
    virtual void animate() = 0;
    virtual void childDraw(SDL_Renderer *render) = 0;
    virtual bool isAlive() = 0;
};