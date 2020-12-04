#pragma once
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <SDL.h>
#include <string>

// this class manages all sounds of the game
class SoundManager {
    private:
    Mix_Music *bgMusic = NULL;
    Mix_Chunk * chunk = NULL;

    public:

    // constructor which initializes sound library
    SoundManager(){
        if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 ) {
                printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			}
    }

    // loads audio file using audio path
    void LoadMusic(const std::string &musicFilneName);
    // loads audio file using audio path
    void LoadSoundEffect(const std::string &soundFileName);
    // plays bg music
    void playMusic();
    // pauses music
    void pauseMusic();
    // plays soundEffect audio
    void playSoundEffect();

    // deconstructor [deletes all objects and vars]
    ~SoundManager(){
        Mix_FreeChunk(chunk);
        Mix_FreeMusic(bgMusic);
        bgMusic = nullptr;
        chunk = nullptr;
        Mix_Quit();
    }
};