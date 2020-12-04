#include "unit.hpp"

// draw us used for render images
void Unit::draw(SDL_Renderer *render, bool flip)
{
    if (flip)
    {
        SDL_RenderCopyEx(render, assets, &src, &mover, 180, NULL, SDL_FLIP_VERTICAL);
    }
    else
    {
        SDL_RenderCopy(render, assets, &src, &mover);
    }
};

// this creates a wobble effect and then render it
void Unit::wobbledraw(SDL_Renderer *render)
{

    if (angle == 20)
    {
        SDL_RenderCopyEx(render, assets, &src, &mover, angle, NULL, SDL_FLIP_VERTICAL);
        angle = -20;
    }
    else
    {
        SDL_RenderCopyEx(render, assets, &src, &mover, angle, NULL, SDL_FLIP_HORIZONTAL);
        angle = 20;
    }
};


// this is used for tilting the image and then rendering it
void Unit::incline(SDL_Renderer *render, int a,bool flip)
{
    if (flip)
    {
        SDL_RenderCopyEx(render, assets, &src, &mover, -a, NULL, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        SDL_RenderCopyEx(render, assets, &src, &mover, a, NULL, SDL_FLIP_NONE);
    }
    
}


//  get MOver returns the SDL_Rect
SDL_Rect Unit::getMover()
{
    return mover;
};

// this func rotates the sprite and then render it
void Unit::rotation(SDL_Renderer *render){
     
     if (angle == 180)
    {
        SDL_RenderCopyEx(render, assets, &src, &mover, angle, NULL, SDL_FLIP_VERTICAL);
        angle = -180;
    }
    else
    {
        SDL_RenderCopyEx(render, assets, &src, &mover, angle, NULL, SDL_FLIP_HORIZONTAL);
        angle = 180;
    }
};

