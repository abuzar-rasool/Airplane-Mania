#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>

// Text class used for displaying all the texts of the game
class Text {
    private:
    SDL_Texture* _text_texture = nullptr;
    mutable SDL_Rect _text_rect;

    public:
    // constructor for Text with font file, font size, font color, and position
    Text(SDL_Renderer* renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color){
        _text_texture = loadFont(renderer, font_path, font_size, message_text, color);
        SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
    }

    // displays the text on screen
    void display(int x, int y, SDL_Renderer *renderer) const;
    static SDL_Texture *loadFont(SDL_Renderer *renderer,const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);

    
};