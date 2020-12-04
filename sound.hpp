#pragma once
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <SDL.h>
#include <string>

class SoundManager {
    private:
    Mix_Music *bgMusic = NULL;
    Mix_Chunk * chunk = NULL;

    public:

    SoundManager(){
        if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 ) {
                printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			}
    }

    void LoadMusic(const std::string &musicFilneName);
    void LoadSoundEffect(const std::string &soundFileName);
    void playMusic();
    void pauseMusic();
    void playSoundEffect();

    ~SoundManager(){
        Mix_FreeChunk(chunk);
        Mix_FreeMusic(bgMusic);
        bgMusic = nullptr;
        chunk = nullptr;
        Mix_Quit();
    }
};