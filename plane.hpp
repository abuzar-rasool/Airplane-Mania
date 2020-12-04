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


        if (Unit::mover.x  < 800){
            Unit::mover.x += planespeed;
        }
        if (still_flying == false){
            Unit::mover.y += planespeed+5;
        }
    }
    
    void crashed(){
        still_flying = false;
        //std::cout<<"The plane should change";
        src[0] = {46, 686, 201, 128};
        src[1] = {46, 686, 201, 128};
        src[2] = {46, 686, 201, 128};
        src[3] = {46, 686, 201, 128};
    }

    void childDraw(SDL_Renderer *render)
    {
        animate();
        if(!still_flying){
            Unit::incline(render,10,FlyingObject::flip);
        }else{
            Unit::draw(render, FlyingObject::flip);    
        }
        
    };
    bool isAlive()
    {
        if(Unit::mover.y>450){
         return false;   
        } 
        return true;
    };
    void setPlaneSource(SDL_Rect s[4])
    {
        for (int i = 0; i < 4; i++)
            src[i] = s[i];
    }
    bool stillFlying(){
        return still_flying;
    }
};