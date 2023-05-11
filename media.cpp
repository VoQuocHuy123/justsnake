#include "media.h"
#include<iostream>
using namespace std;
LTexture::LTexture(){
    mRender = NULL , mFont = NULL , mTexture = NULL;
}

LTexture::LTexture( SDL_Renderer * newRender, TTF_Font * newFont){
    mRender = newRender , mFont = newFont;
    mTexture = NULL;
    mWidth = mHeight = 0 ;
}

LTexture::~LTexture(){
    SDL_DestroyTexture(mTexture);
}

void LTexture::setColor(const Uint8 &red,const Uint8 &green,const Uint8 &blue ){
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setAlpha(const Uint8 &alpha ){
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::loadImage(const string &path,const int &r,const int &g,const int &b){
    SDL_Surface * loadSurface = IMG_Load(path.c_str());

    if(loadSurface == NULL){
        cout << "loi o media.cpp , ham Ltexture::loadImage, dong 25\n";
    } else {
        /// lam mat mau background cua hinh anh
        SDL_SetColorKey(loadSurface , SDL_TRUE, SDL_MapRGB(loadSurface->format,
                                                           r, g, b));

        mTexture = SDL_CreateTextureFromSurface(mRender, loadSurface);

        if(mTexture == NULL){
            cout << "loi o media.cpp , ham Ltexture::loadImage, dong 34 \n";
        } else {
            mWidth = loadSurface->w , mHeight = loadSurface->h;
        }

        SDL_FreeSurface(loadSurface);
    }
}

void LTexture::loadText(const string &text,const SDL_Color &textColor){
    SDL_Surface * loadSurface = TTF_RenderText_Solid(mFont , text.c_str(), textColor);

    if(loadSurface == NULL){
        cout << "loi o media.cpp , ham Ltexture::loadText, dong 47\n";
    } else {
        mTexture = SDL_CreateTextureFromSurface(mRender, loadSurface);
        if(mTexture == NULL){
            cout << "loi o media.cpp , ham Ltexture::loadText, dong 51\n";
        } else {
            mWidth = loadSurface->w, mHeight = loadSurface->h;
        }

        SDL_FreeSurface(loadSurface);
    }
}

void LTexture::render(const int &x,const int &y,  SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( mRender, mTexture, clip, &renderQuad, angle, center, flip );
}

/*LSound::~LSound(){
    Mix_FreeChunk(mSou);
}

LSound::LSound(const string &path){
    mSou = Mix_LoadWAV(path.c_str());
    if(mSou == NULL)
        cout << "loi o media.cpp, ham lSound::lSound, dong 86\n" ;
}

void LSound::playSound(){
    Mix_PlayChannel(-1, mSou, 0);
    /// -1 tuc la phat am thanh o kenh bat ky , 0 tuc la khong lap lai
}

LMusic::~LMusic(){
    Mix_FreeMusic(mMus);
}

LMusic::LMusic(const string &path){
    mMus = Mix_LoadMUS(path.c_str());
    if(mMus == NULL)
        cout << "loi o media.cpp , ham lmusic::lMusic , dong 108\n" ;
}

void LMusic::playMusic(){
    if(Mix_PlayingMusic() == 0){ /// nhac chua chay thi phat nhac
        Mix_PlayMusic(mMus, -1) ;
        /// -1 tuc la lap vo han
    }
}

void LMusic::stopMusic(){
    Mix_HaltMusic();
}

bool bling::isDead(){
    return bool(mFrame > 10) ;
}

void bling::reset(mPoint &other){
    td.x = other.x - 5 + (rand() % 25) ;
    td.y = other.y - 5 + (rand() % 25) ; /// lam nnay de vi tri phan bo bat ky [ x - 5 , x + 20 ]

    mFrame = rand() % 5 ; /// de nhap nhay

    id = rand() % 3 ; /// random color
}

bling::~bling(){

}

bling::bling(){
    mFrame = 11 ;
}

void bling::render( SDL_Renderer * newRender, mPoint &other,const bool &ok){
    static LTexture * c[4] ;
    if(ok){
        for(int i = 0;i < 4;i ++)
            c[i] = new LTexture(newRender, NULL);

        c[0]->loadImage("data/image/red.bmp", CYAN.r, CYAN.g, CYAN.b);
        c[1]->loadImage("data/image/green.bmp", CYAN.r, CYAN.g, CYAN.b);
        c[2]->loadImage("data/image/blue.bmp", CYAN.r, CYAN.g, CYAN.b);
        c[3]->loadImage("data/image/shimmer.bmp", CYAN.r, CYAN.g, CYAN.b);
    }

    if(isDead())
        reset(other);

    c[id]->render(td.x , td.y) ;
    if(mFrame % 2)
        c[3]->render(td.x , td.y);

    mFrame ++ ;
}

Dot::~Dot(){
    pic->~LTexture();
}

Dot::Dot(const string &path,mPoint &other,SDL_Renderer * &newRender,const int &r,const int &g ,const int &b){
    td.x = other.x;
    td.y = other.y;
    vx = vy = 0.0 ;
    pic = new LTexture(newRender, NULL);
    pic->loadImage(path, r, g, b) ;
}

bool Dot::dichuyen(const int &w  ,const int &h ){ /// di chuyen xong thi xem con trong bang khong
    td.x += int(vx) ;
    td.y += int(vy);
    return td.isInside(w, h);
}

bool Dot::vacham(Dot * &other){
    int l1 = td.x , r1 = l1 + pic->mWidth , l2 = other->td.x , r2 = l2 + other->pic->mWidth;
    if((r1 < l2) || (r2 < l1)) return 0;

    l1 = td.y , r1 = l1 + pic->mHeight , l2 = other->td.y , r2 = l2 + other->pic->mHeight;
    if((r1 < l2) || (r2 < l1)) return 0;

    return 1;
}

void Dot::render(const double &angle){
    pic->render(td.x, td.y, NULL, angle, NULL, SDL_FLIP_NONE);
}

LButton::LButton(SDL_Renderer * &newRender, TTF_Font * f[] , mPoint &other,const vector<string> & V){
    a = mOut;
    td.x = other.x , td.y = other.y;
    n = int(V.size());

    b = new LTexture [n] ;

    for(int i = 0 ;i < n;i ++){
        if(i < 2){
            b[i].mFont = f[0] , b[i].mRender = newRender;
            b[i].loadText(V[i] , i < 1 ? PINK : YELLOW);
        }
        else{
            b[i].mFont = f[1], b[i].mRender = newRender;
            b[i].loadText(V[i] , (V[i] == "ON" || V[i] == "OFF") ? ORANGE : CYAN);
        }
    }
}

LButton::~LButton(){
    delete [] b;
}

void LButton::handleEvent(SDL_Event &e,bool & ok,bool & ok2){
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
        int x, y ;
        SDL_GetMouseState(&x, &y);

        bool inside = 1 ;
        if(x < td.x || x > td.x + w || y < td.y || y > td.y + h)
            inside = 0;

        if(! inside)
            a = mOut;
        else {
            if(a == mDown);
            else {
                a = mIn ;
                if(e.type == SDL_MOUSEBUTTONDOWN)
                    a = mDown ;
            }
        }
    } else if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
            case SDLK_0 :
                ok2 = 0;
                break;

            case SDLK_1 :
                ok2 = 1;
                break ;

            case SDLK_y :
                ok = 1;
                break;

            case SDLK_n :
                ok = 0;
                break ;

            default :
                break;
        }
    }
}

void LButton::render(const bool &ok1 , bool &ok , bool &ok2){
    if(a != mDown){
        (a == mIn) ? b[1].render(td.x , td.y) : b[0].render(td.x , td.y);
    } else {
        int h2 = 0 ;
        for(int i = 2 ; i < n - (ok1 ? 2 : 0);i ++){
            b[i].render(td.x , td.y + h2);

            if(ok1){
                if(i == 2)
                    b[ok ? n - 2 : n - 1].render(td.x + b[i].mWidth , td.y + h2) ;
                else
                    b[ok2 ? n - 2 : n - 1].render(td.x + b[i].mWidth , td.y + h2) ;
            }

            h2 += b[i].mHeight ;
        }
    }
}*/

