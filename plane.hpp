#include "flying_object.hpp"
class Plane : public FlyingObject
{
private:
    SDL_Rect src[4];
    int planespeed = 5;    
public:

    // constructor with texture parameter and then it initiales a plane sprite with relevant coordinates and everythign
    Plane(SDL_Texture *texture) : FlyingObject(texture){
        SDL_Rect src[4];        
        src[0] = {46, 882, 205, 131};
        src[1] = {42, 1070, 205, 131};
        src[2] = {46, 882, 205, 131};
        src[3] = {42, 1070, 205, 131};
        Unit::mover.h = 45;
        Unit::mover.w = 70;
        Unit::mover.x = 0;
        FlyingObject::flip = false;
        Plane::setPlaneSource(src);
        planespeed=3;
    };
    Plane(SDL_Texture *texture, int s) : FlyingObject(texture), planespeed(s){};
    
    // used for animating plane
    void animate();
    // used when a plane have collision
    void crashed();
    // used for creating plane
    void childDraw(SDL_Renderer *render);
    // checks if a plane is still alive means no collisions
    bool isAlive();
    // setting the relevant sprite
    void setPlaneSource(SDL_Rect s[4]);
    // checks for plane if it's still flying
    bool stillFlying();
};