#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>

#include "pigeon.hpp"
#include "egg.hpp"
#include "nest.hpp"
#include "bird.hpp"
#include "flare.hpp"
#include "plane.hpp"
#include "blast.hpp"

using namespace std;

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;


    int no_of_birds = 1;
    int no_of_planes = 1;
    int no_of_total_birds = 0;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;

    //You may use C++ linked lists, or you can create your own.
    list<Unit*> pigeons;
    list<Unit*> eggs;
    list<Nest*> nests;   
    list<Bird*> birds;
    list<Plane*> planes;
    list<Flare*> flares;  
    list<Blast*> blasts;

public:
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
    void updateEggs();
    void updatePigeons();
    void drawAllObjects();
    void spawnBirds();
    void spawnPlanes();
    void updateFlare();
    void Check4Collision();
    void updateBlasts();
    void updatePlanes();
    void updateBirds();
};

