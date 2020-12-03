#pragma once
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <SDL.h>
#include <string>

class SoundManager {
    private:
    Mix_Music *bgMusic = NULL;

    public:

    SoundManager(){
        if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			}
    }

    void LoadMusic(const std::string &musicFilneName) {
        bgMusic = Mix_LoadMUS(musicFilneName.c_str());

	if(bgMusic == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
	    }
    }

    void playMusic(int loops) {
        if( Mix_PlayingMusic() == 0 )
			{
			    Mix_PlayMusic( bgMusic, loops);
			}
    }

    ~SoundManager() {
        delete bgMusic;
        Mix_Quit();
    }
};