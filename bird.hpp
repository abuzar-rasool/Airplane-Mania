#include "flying_object.hpp"
class Bird : public FlyingObject
{
private:
    // array of SDL_Rect for sprite animation
    SDL_Rect src[4];
    // bird speed int
    int birdSpeed = 5;

public:
    // bool for bird scare state
    bool scare=false;
    // constructors
    Bird(SDL_Texture *texture) : FlyingObject(texture){};
    Bird(SDL_Texture *texture, int s) : FlyingObject(texture), birdSpeed(s){};
    
    // animate the bird
    void animate();
    // used when bird is collided or died with flare gun
    void crashed();
    // getting the value of scare bool
    bool get_scared();
    // used when the bird is in scared state
    void scared();
    // draws the sprite on screen
    void childDraw(SDL_Renderer *render);
    // checks if a bird is alive or not
    bool isAlive();
    // set the sprite for bird 
    void setBirdSource(SDL_Rect s[4]);
    // checks if a bird is still flying
    bool stillFlying();

};

// There are total 3 types of birds in our game. Following are different child classes for each of them

// Class for Bird type #01
class Bird1 : public Bird{
public:
    // constructor with necessary parameters
    Bird1(SDL_Texture *texture) : Bird(texture, 3)
    {   
        // overwriting parent class attributes in child class
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

// Class for Bird type #02
class Bird2 : public Bird{
public:
    // constructor with necessary parameters
    Bird2(SDL_Texture *texture) : Bird(texture, 4)
    {
        
        // overwriting parent class attributes in child class
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

// Class for Bird type #03
class Bird3 : public Bird{
public:
    // constructor with necessary parameters
    Bird3(SDL_Texture *texture) : Bird(texture, 5){
        // overwriting parent class attributes in child class
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