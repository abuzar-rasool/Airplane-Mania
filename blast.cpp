#include "blast.hpp"

void Blast::animate(){
    Unit::mover.w+=5;
    Unit::mover.h+=5;
    if(frame<9) frame++;
}

void Blast::childDraw(SDL_Renderer *render){
    animate();
    Unit::src = src[frame];     
    Unit::rotation(render);
}

bool Blast::isAlive(){
    if(frame==9){
        return false;
    }else{
        return true;
    }
}
