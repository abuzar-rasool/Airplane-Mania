#include "pigeon.hpp"



void Pigeon::animate()
{
    if (frame==2)
    {
        frame = 0;
    }
    else
    {
        frame++;
    }

    //grow
    if (getMover().w < 50 && getMover().h < 50)
    {
        Unit::mover.w += 1;
        Unit::mover.h += 1;
        baby = true;
    }
    else
    {
        baby = false;
    }
    //Vertical movement
    if (getMover().y > 0)
    {
        Unit::mover.y -= 5;
    }

    if (getMover().x >= 700)
    {
        flip = true;
    }
    else if (getMover().x < 100)
    {
        flip = false;
    }

    if (flip)
    {
        Unit::mover.x -= 5;
    }
    else
    {
        Unit::mover.x += 5;
    }

    Unit::src = src[frame];
}

void Pigeon::childDraw(SDL_Renderer *render)
{
    animate();
    Unit::draw(render, flip);
};

bool Pigeon::layEgg()
{
    int result = (rand() % 99) + 0;
    if (result <= 1 && !baby)
    {
        eggsLaid++;
        return true;
    }
    else
    {
        return false;
    }
};
bool Pigeon::isAlive()
{
    if (eggsLaid >= 4)
    {
        return false;
    }
    else
    {
        return true;
    }
};
