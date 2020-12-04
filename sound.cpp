#include "sound.hpp"

void SoundManager::LoadMusic(const std::string &musicFilneName) {
    bgMusic = Mix_LoadMUS(musicFilneName.c_str());
    if(bgMusic == NULL){
        printf("Unable to load music: %s \n", Mix_GetError());
    }
}

void SoundManager::LoadSoundEffect(const std::string &soundFileName) {
    chunk = Mix_LoadWAV(soundFileName.c_str());
}

void SoundManager::playMusic() {
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic(bgMusic, -1);
    }
}

void SoundManager::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void SoundManager::playSoundEffect() {
    Mix_PlayChannel(-1, chunk, 0);
}