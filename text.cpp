#pragma once
#include "text.hpp"

// displays the text on screen
void Text::display(int x, int y, SDL_Renderer *renderer) const {
    _text_rect.x = x;
    _text_rect.y = y;
    SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
}

// this loads the font and customize it accordingly
SDL_Texture *Text::loadFont(SDL_Renderer *renderer,const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color) {
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