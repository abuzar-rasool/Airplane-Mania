#include "flying_object.hpp"
class Plane : public FlyingObject
{
private:
    SDL_Rect src[4];
    int planespeed = 5;

public:
    Plane(SDL_Texture *texture) : FlyingObject(texture){};
    Plane(SDL_Texture *texture, int s) : FlyingObject(texture), planespeed(s){};
    void animate()
    {
        //Plane flying animation
        if (FlyingObject::frame == 3)
        {
            FlyingObject::frame = 0;
        }
        else
        {
            frame++;
        }
        Unit::src = src[frame];

        if (!FlyingObject::flip)
        {

            if (Unit::mover.x > 800)
            {
                //If Plane leave the screen reset it to its initial position
                Unit::mover.x = 0;
            }
            else
            {

                //Plane moving from right to left of the screen if flip is false.
                Unit::mover.x += planespeed;
            }
        }
        else
        {

            if (Unit::mover.x < 0)
            {
                //If plane leave the screen reset it to its initial position
                Unit::mover.x = 800;
            }
            else
            {
                //Plane moving left to right of the screen if the flip is true.
                Unit::mover.x -= planespeed;
            }
        }
    }
    void childDraw(SDL_Renderer *render)
    {
        animate();
        Unit::draw(render, FlyingObject::flip);
    };
    bool isAlive()
    {
        return true;
    };
    void setPlaneSource(SDL_Rect s[4])
    {
        for (int i = 0; i < 4; i++)
            src[i] = s[i];
    }
};

class Plane_flying : public Plane
{
public:
    Plane_flying(SDL_Texture *texture) : Plane(texture, 3)
    {
        SDL_Rect src[4];
        src[0] = {46, 882, 205, 131};
        src[1] = {42, 1070, 205, 131};
        src[2] = {46, 882, 205, 131};
        src[3] = {42, 1070, 205, 131};
        Unit::mover.h = 45;
        Unit::mover.w = 70;
        Plane::setPlaneSource(src);
    };
};

class Plane_crashed : public Plane
{

public:
    Plane_crashed(SDL_Texture *texture) : Plane(texture, 4)
    {
        SDL_Rect src[1];
        src[0] = {41, 157, 87, 85};
        Plane::setPlaneSource(src);
    };
};