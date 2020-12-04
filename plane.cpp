#include "plane.hpp"

// this func animates plane using plane sprites
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

    // if plane is on screen then move it
    if (Unit::mover.x  < 800){
        Unit::mover.x += planespeed;
    }
    // if plane is not flying then it's falling
    if (still_flying == false){
        Unit::mover.y += planespeed+5;
    }
}

// calls when plane got collision
void Plane::crashed(){
    still_flying = false;
    //std::cout<<"The plane should change";
    // mapping plane sprites
    src[0] = {46, 686, 201, 128};
    src[1] = {46, 686, 201, 128};
    src[2] = {46, 686, 201, 128};
    src[3] = {46, 686, 201, 128};
}


// this renders the plane on screen/renderer
void Plane::childDraw(SDL_Renderer *render)
{
    animate();
    if(!still_flying){
        Unit::incline(render,10,FlyingObject::flip);
    }else{
        Unit::draw(render, FlyingObject::flip);    
    }
    
};

// checks if a plane is alive means no collision
bool Plane::isAlive()
{
    if(Unit::mover.y>450){
        return false;   
    } 
    return true;
};

// set the relevant sprite to display
void Plane::setPlaneSource(SDL_Rect s[4])
{
    for (int i = 0; i < 4; i++)
        src[i] = s[i];
}

// checks if flare is going on
bool Plane::stillFlying(){
    return still_flying;
}