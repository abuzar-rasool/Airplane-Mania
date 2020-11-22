#include "egg.hpp"

void Egg::childDraw(SDL_Renderer *render)
{
    Unit::wobbledraw(render);
    Unit::mover.y += 5;
};
bool Egg::dropped()
{
    if (getMover().y > 550)
    {
        return true;
    }
    else
    {
        return false;
    }
};