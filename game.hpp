#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include "text.hpp"
#include <SDL_mixer.h>
#include "bird.hpp"
#include "flare.hpp"
#include "plane.hpp"
#include "blast.hpp"
#include "sound.hpp"
#include "menu.hpp"
#include "score.hpp"

using namespace std;

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    time_t runtime, pausetime;
    bool isPause = false, pauseflag = false;
    string gameState = "notRunning";
    //score variables
    int no_of_birds = 1;
    int no_of_planes = 1;
    int no_of_total_birds = 0;

    // Score Object
    Score playerScore;

    //Menu options
    Menu startMenu;
    Menu gamePausedMenu;

    //Sound managers
    SoundManager bgSound;
    SoundManager spawnBird1;
    SoundManager spawnBird2;
    SoundManager spawnPlaneSound;
    SoundManager planeCrashSound;
    SoundManager birdDied1;
    SoundManager birdDied2;
    SoundManager birdDied3;
    SoundManager BirdPlaneCollision;
    SoundManager FlareSound;
    SoundManager Cheer;
    SoundManager Score;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;
    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;

    //You may use C++ linked lists, or you can create your own.
    list<Bird*> birds;
    list<Plane*> planes;
    list<Flare*> flares;  
    list<Blast*> blasts;

public:
    //this changes the score
    void set_score(int a);
    //game is initialized
    bool init();
    //media is laoded
    bool loadMedia();
    //game closed
    void close();
    //load all the images and assets
    SDL_Texture* loadTexture( std::string path );
    //the main run loop
    void run();
    //this draws all the objects
    void drawAllObjects();
    //this spawn bird on timer randomly
    void spawnBirds();
    //this spawn planes randomly
    void spawnPlanes();
    //this vhecks for flare update
    void updateFlare();
    //this checks for collision between bird and plane
    void Check4Collision();
    //this updates the blasts frame due to plane
    void updateBlasts();
    //this updates the frames of plane while flying
    void updatePlanes();
    //this is a timer that is used for spawining and to indicate game start and game end
    void timer();
    //clears all the memeory
    void remove_all();
    //this updates the frame of the bird
    void updateBirds();
    //this is used for text rendering
    void writeText(std::string content, int font, int xCo, int yCo, SDL_Color color);
};

