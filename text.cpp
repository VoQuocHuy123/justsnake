
#include "text.h"
#include<string>
#include<SDL_ttf.h>
Text::Text()
{
   text_color_.r = 255;
   text_color_.g = 255;
   text_color_.b = 255;
   texture_ = NULL;
}

Text::~Text()
{

}
void Text::SetColor(const int& type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        text_color_ = color;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color = {255, 255, 255};
        text_color_ = color;
    }
    else
    {
        SDL_Color color = {0, 0, 0};
        text_color_ = color;
    };
}
bool Text::LoadFromRenderText(TTF_Font* font, SDL_Renderer* renderer){
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,str_val_.c_str(),text_color_);
    if(text_surface){
        texture_ = SDL_CreateTextureFromSurface(renderer, text_surface);
        width_ = text_surface->w;
        heigth_= text_surface->h;

        SDL_FreeSurface(text_surface);
    }

    return texture_ != NULL;

}


void Text::Free()
{
    if(texture_!=NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void Text::RenderText(SDL_Renderer* renderer, int xp, int yp,
                      SDL_Rect* clip, double angle, SDL_Point* center,
                      SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {xp,yp,width_,heigth_};
    if(clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, texture_, clip, &renderQuad, angle, center, flip);
}
