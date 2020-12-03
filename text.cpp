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


class Text {
    private:
    SDL_Texture* _text_texture = nullptr;
    mutable SDL_Rect _text_rect;

    public:

    void display(int x, int y, SDL_Renderer *renderer) const {
        _text_rect.x = x;
        _text_rect.y = y;
        SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
    }

    static SDL_Texture *loadFont(SDL_Renderer *renderer,const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color) {
        TTF_Init();
        TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);

        if (!font) {
            std::cerr << "failed to load to font\n";
        }
        auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
        if (!text_surface){
            std::cerr << "failed to create text surface\n";
        }
        auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (!text_surface) {
            std::cerr << "failed to create text texture\n";
        }
        SDL_FreeSurface(text_surface);
        TTF_CloseFont(font);
        return text_texture;
    }

    Text(SDL_Renderer* renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color){
        _text_texture = loadFont(renderer, font_path, font_size, message_text, color);
        SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
    }
};