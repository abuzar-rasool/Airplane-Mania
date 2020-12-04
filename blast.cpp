#include "blast.hpp"

// this func used to animate blast by changing the coordinates
void Blast::animate(){
    Unit::mover.w+=5;
    Unit::mover.h+=5;
    if(frame<9) frame++;
}

// this fucn is used to draw the blast sprite on screen
void Blast::childDraw(SDL_Renderer *render){
    animate();
    Unit::src = src[frame];     
    Unit::rotation(render);
}

// this func checks if a blast is ongoing or not
bool Blast::isAlive(){
    if(frame==9){
        return false;
    }else{
        return true;
    }
}
