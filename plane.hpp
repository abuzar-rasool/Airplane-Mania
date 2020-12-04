#include "flying_object.hpp"
class Plane : public FlyingObject
{
private:
    SDL_Rect src[4];
    int planespeed = 5;    
public:
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
    
    void animate();
    void crashed();
    void childDraw(SDL_Renderer *render);
    bool isAlive();
    void setPlaneSource(SDL_Rect s[4]);
    bool stillFlying();
};