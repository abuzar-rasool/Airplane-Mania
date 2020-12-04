#include "plane.hpp"

void Plane::animate()
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

void Plane::crashed(){
    still_flying = false;
    //std::cout<<"The plane should change";
    src[0] = {46, 686, 201, 128};
    src[1] = {46, 686, 201, 128};
    src[2] = {46, 686, 201, 128};
    src[3] = {46, 686, 201, 128};
}

void Plane::childDraw(SDL_Renderer *render)
{
    animate();
    if(!still_flying){
        Unit::incline(render,10,FlyingObject::flip);
    }else{
        Unit::draw(render, FlyingObject::flip);    
    }
    
};
bool Plane::isAlive()
{
    if(Unit::mover.y>450){
        return false;   
    } 
    return true;
};
void Plane::setPlaneSource(SDL_Rect s[4])
{
    for (int i = 0; i < 4; i++)
        src[i] = s[i];
}
bool Plane::stillFlying(){
    return still_flying;
}