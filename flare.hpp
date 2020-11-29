#include "flying_object.hpp"

class Flare : public FlyingObject
{
private:
    SDL_Rect src[10];
    bool collide = false;
public:
    Flare(SDL_Texture *texture,SDL_Rect c_pos) : FlyingObject(texture,c_pos,180)
    {
        frame=0;
        SDL_Rect t_src[10] = {{881, 48, 38, 44},
               {859, 233, 77, 77},
               {844, 420, 104, 103},
               {844, 616, 100, 111},
               {831, 812, 121, 120},
               {700, 29, 108, 117},
               {701, 241, 103, 95},
               {701, 434, 100, 109},
               {693, 630, 112, 118},
               {688, 827, 118, 125}};
        for(int i=0;i<10;i++){
            src[i]=t_src[i];
        };
        
    };
    void animate()
    {
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
    void collisionhappen(){
        collide=true;
    }
    void childDraw(SDL_Renderer *render)
    {
        animate();
        Unit::src = src[frame];     
        Unit::rotation(render);
    };
    bool isAlive()
    {
       if(frame==9){
           return false;
       }else{
           return true;
       }
    };

};