#include "flying_object.hpp"

class Blast : public FlyingObject
{
private:
    // SDL_Rect array of 10 elements
    SDL_Rect src[10];

public:
    // constructor with texture and rect
    Blast(SDL_Texture *texture,SDL_Rect c_pos) : FlyingObject(texture,c_pos,180)
    {
        frame=0;
        // setting Rect with sprites
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
        }
        
    }

    // used for animate blasts
    void animate();
    // used for rendering sprites on screen
    void childDraw(SDL_Renderer *render);
    // checks if blast is going on
    bool isAlive();

};