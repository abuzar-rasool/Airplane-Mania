#include "flying_object.hpp"
class Bird : public FlyingObject
{
private:
    SDL_Rect src[4];
    int birdSpeed = 5;

public:
    bool scare=false;
    Bird(SDL_Texture *texture) : FlyingObject(texture){};
    Bird(SDL_Texture *texture, int s) : FlyingObject(texture), birdSpeed(s){};
    
    void animate();
    void crashed();
    bool get_scared();
    void scared();
    void childDraw(SDL_Renderer *render);
    bool isAlive();
    void setBirdSource(SDL_Rect s[4]);
    bool stillFlying();

};

class Bird1 : public Bird{
public:
    Bird1(SDL_Texture *texture) : Bird(texture, 3)
    {
        SDL_Rect src[4];
        src[0] = {41, 30, 87, 85};
        src[1] = {157, 46, 87, 85};
        src[2] = {41, 161, 87, 85};
        src[3] = {157, 161, 87, 85};
        Bird::setBirdSource(src);
        Unit::mover.x = 800;
        FlyingObject::flip = true;
    };
};

class Bird2 : public Bird{
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
        Unit::mover.x = 800;

        Bird::setBirdSource(src);
        FlyingObject::flip = true;
    };
};

class Bird3 : public Bird{
public:
    Bird3(SDL_Texture *texture) : Bird(texture, 5){
        SDL_Rect src[4] ;
        src[0] = {300, 133, 87, 85};
        src[1] = {416, 45, 87, 85};
        src[2] = {300, 172, 87, 85};
        src[3] = {416, 171, 87, 85};
        Bird::setBirdSource(src);
        Unit::mover.x = 800;
        FlyingObject::flip = true;
    };
};