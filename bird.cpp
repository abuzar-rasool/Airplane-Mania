#include "bird.hpp"

void Bird::animate(){
    //Bird flying animation
    if (FlyingObject::frame == 3){
        FlyingObject::frame = 0;
    }
    else{
        frame++;
    }

    Unit::src = src[frame];
        if(!scare){
        if (!FlyingObject::flip){
            if (Unit::mover.x > 750 && !flip){
                //If bird leave the screen reset it to its initial position
                flip=true;
            }
            else{
                //Bird moving from right to left of the screen if flip is false.
                Unit::mover.x += birdSpeed;
            }
        }
        else
        {
            if (Unit::mover.x < 10){
                //If bird leave the screen reset it to its initial position
                flip=false;
            }
            else{
                //Bird moving left to right of the screen if the flip is true.
                Unit::mover.x -= birdSpeed;
            }
        }
    }

    else{
        if(!flip){
            Unit::mover.x += birdSpeed;
        }
        else{
            Unit::mover.x -= birdSpeed;
        }
    }

    if(!still_flying){
        Unit::mover.y += 30;
    }
}

void Bird::crashed(){
    still_flying=false;
    src[0]=src[3];
    src[1]=src[3];
    src[2]=src[3];
    src[3]=src[3]; 
}

bool Bird::get_scared(){
    return scare;
}

void Bird::scared(){
    birdSpeed+=5;
    scare=true;
    flip=!flip;
}

void Bird::childDraw(SDL_Renderer *render){        
    animate();
    Unit::draw(render, FlyingObject::flip);
}

bool Bird::isAlive(){
    if(Unit::mover.y>580 or (Unit::mover.x<-10 || Unit::mover.x>810)){
        return false;   
    } 
    return true;
}

void Bird::setBirdSource(SDL_Rect s[4]){
    for (int i = 0; i < 4; i++)
        src[i] = s[i];
}

bool Bird::stillFlying(){
    return still_flying;
}