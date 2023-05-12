#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <string>
#include<SDL_ttf.h>
#include<SDL_image.h>
 #include <SDL.h>
 #include <bits/stdc++.h>

 using namespace std;




class Text
{
std::string str_val_;
SDL_Color text_color_;
SDL_Texture* texture_;
int width_;
int heigth_;

public:
    Text();
    ~Text();

    enum TextColor{
       RED_TEXT = 0,
       WHITE_TEXT = 1,
       BLACK_TEXT = 2,
    };
    void SetText(const std::string& text){str_val_ = text; }
    void SetColor(const int& type);
    void CreateGameText(TTF_Font* font, SDL_Surface* des );
    bool LoadFromfile(std::string path);
    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* renderer);
    void Free();
    void RenderText(SDL_Renderer* renderer, int xp, int yp,
                    SDL_Rect* clip = NULL, double angle = 0.0,
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    int GetWidth() const {return width_;}
    int GetHeigth() const {return heigth_;}
    std::string GetText() const {return str_val_;}
};

#endif
