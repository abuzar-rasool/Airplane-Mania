#include "sound.hpp"

// this func load the music files 
void SoundManager::LoadMusic(const std::string &musicFilneName) {
    bgMusic = Mix_LoadMUS(musicFilneName.c_str());
    if(bgMusic == NULL){
        printf("Unable to load music: %s \n", Mix_GetError());
    }
}

// this func loads sound effects files
void SoundManager::LoadSoundEffect(const std::string &soundFileName) {
    chunk = Mix_LoadWAV(soundFileName.c_str());
}

// this plays musics on infinite loop
void SoundManager::playMusic() {
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic(bgMusic, -1);
    }
}

// this is used to pause bg music
void SoundManager::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

// this is used for playing sound effects
void SoundManager::playSoundEffect() {
    Mix_PlayChannel(-1, chunk, 0);
}