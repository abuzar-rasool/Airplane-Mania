#include "flare.hpp"

// animate flare sprite position
void Flare::animate(){
    //move up to the blast point
    if(collide==false){
        Unit::mover.y-=40;
        Unit::mover.w+=1;
        Unit::mover.h+=1;
    }else{
        Unit::mover.w+=15;
        Unit::mover.h+=15;
        if(frame<9)
            frame++;
    }
}

// checks for collision
void Flare::collisionhappen(){
    collide=true;
}

// renders the flare sprites
void Flare::childDraw(SDL_Renderer *render){
    animate();
    Unit::src = src[frame];     
    Unit::rotation(render);
};

// checks if flare is going on
bool Flare::isAlive(){
    if(frame==9){
        return false;
    }else{
        return true;
    }
}