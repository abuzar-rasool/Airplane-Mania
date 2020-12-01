#include "unit.hpp"

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


SDL_Rect Unit::getMover()
{
    return mover;
};

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

