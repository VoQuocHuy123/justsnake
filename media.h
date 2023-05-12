#ifndef MEDIA_H
#define MEDIA_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
using namespace std;

class LTexture{
public :

    SDL_Renderer * mRender ;
    TTF_Font * mFont ;
    SDL_Texture * mTexture ;
    int mWidth , mHeight ;

    LTexture();

    LTexture( SDL_Renderer * newRender, TTF_Font * newFont) ;

    ~LTexture();

    void loadImage(const string &path,const int &r,const int &g,const int &b);

    void loadText(const string &text,const SDL_Color &textColor);

    void setAlpha(const Uint8 &alpha );

    void setColor(const Uint8 &red,const Uint8 &green,const Uint8 &blue );

    void render(const int &x, const int &y , SDL_Rect * clip = NULL, double angle = 0.0 ,
                 SDL_Point * center = NULL,  SDL_RendererFlip flip = SDL_FLIP_NONE);
};

/*class LSound {
public :

    Mix_Chunk * mSou ;

    ~LSound();

    LSound(const string &path);

    void playSound();
};

class LMusic{
public :

    Mix_Music * mMus ;

    ~LMusic();

    LMusic(const string &path);

    void playMusic();

    void stopMusic();
};

class bling{ /// for enemy
public :

    mPoint td;
    int   mFrame , id ; /// id de random xem vao mau nao

    bling();

    ~bling();

    bool isDead();

    void reset(mPoint &other);

    void render( SDL_Renderer * newRender, mPoint &other,const bool &ok);
};

class Dot{
public :

    mPoint td ;
    double  vx, vy ;
    LTexture * pic;

    Dot(const string &path,mPoint &other, SDL_Renderer * &newRender,const int &r,const int &g,const int &b);

    ~Dot();

    bool dichuyen(const int &w  ,const int &h );

    bool vacham(Dot * &other);

    void render(const double &angle);
};

class LButton{
public :

    mouseStatus a ;
    mPoint td;
    LTexture * b;
    int w, h, n ;

    LButton(SDL_Renderer * &newRender, TTF_Font * f[] , mPoint &other,const vector<string> & V);

    ~LButton();

    void handleEvent(SDL_Event &e,bool & ok,bool & ok2);

    void render(const bool &ok1, bool &ok, bool &ok2);
};*/

#endif
