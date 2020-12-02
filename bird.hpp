#include "flying_object.hpp"
class Bird : public FlyingObject
{
private:
    SDL_Rect src[4];
    int birdSpeed = 5;

public:
    Bird(SDL_Texture *texture) : FlyingObject(texture){};
    Bird(SDL_Texture *texture, int s) : FlyingObject(texture), birdSpeed(s){};
    void animate()
    {
        
        //Bird flying animation
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

            if (Unit::mover.x > 750 && !flip)
            {
                //If bird leave the screen reset it to its initial position
                flip=true;
            }
            else
            {

                //Bird moving from right to left of the screen if flip is false.
                Unit::mover.x += birdSpeed;
            }
        }
        else
        {

            if (Unit::mover.x < 10)
            {
                //If bird leave the screen reset it to its initial position
                flip=false;
            }
            else
            {
                //Bird moving left to right of the screen if the flip is true.
                Unit::mover.x -= birdSpeed;
            }
        }

        if(!still_flying){
            Unit::mover.y += 30;
        }
    }

    void crashed(){
        still_flying=false;
        src[0]=src[3];
        src[1]=src[3];
        src[2]=src[3];
        src[3]=src[3]; 
    }

    void childDraw(SDL_Renderer *render)
    {
         
        animate();

        Unit::draw(render, FlyingObject::flip);
    };
    bool isAlive()
    {
        if(Unit::mover.y>580){
         return false;   
        } 
        return true;
    };
    void setBirdSource(SDL_Rect s[4])
    {
        for (int i = 0; i < 4; i++)
            src[i] = s[i];
    }
    bool stillFlying(){
        return still_flying;
    }

};

class Bird1 : public Bird
{
public:
    Bird1(SDL_Texture *texture) : Bird(texture, 3)
    {
        SDL_Rect src[4];
        src[0] = {41, 30, 87, 85};
        src[1] = {157, 46, 87, 85};
        src[2] = {41, 161, 87, 85};
        src[3] = {157, 161, 87, 85};
        Bird::setBirdSource(src);
    };
};

class Bird2 : public Bird
{

public:
    Bird2(SDL_Texture *texture) : Bird(texture, 4)
    {
        SDL_Rect src[4];
        src[0] = {41, 350, 88, 57};
        src[1] = {157, 366, 88, 41};
        src[2] = {41, 481, 87, 64};
        src[3] = {155, 481, 90, 42};

        Unit::mover.w=60;
         Unit::mover.h=32;

        Bird::setBirdSource(src);
    };
};

class Bird3 : public Bird
{
public:
    Bird3(SDL_Texture *texture) : Bird(texture, 5)
    {
        SDL_Rect src[4] ;
        src[0] = {300, 133, 87, 85};
        src[1] = {416, 45, 87, 85};
        src[2] = {300, 172, 87, 85};
        src[3] = {416, 171, 87, 85};
        Bird::setBirdSource(src);
    };
};