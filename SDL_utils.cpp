

#include <iostream>
#include <SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "Game.h"
#include "constants.h"
#include "Gallery.h"
#include "text.h"
#include <bits/stdc++.h>
#include "media.h"
using namespace std;

const SDL_Color WHITE = {255, 255, 255};

SDL_Rect but_start;
Mix_Chunk* gclick= NULL;


//*****************************************************
// Các hàm chung về khởi tạo và huỷ SDL

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    ///Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    ///Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    if (TTF_Init() != 0){
        cout<<"DKM"<<TTF_GetError();
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void printText(SDL_Renderer* renderer,string text,int x, int y,TTF_Font* font,SDL_Color textColor)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(),textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = SCREEN_WIDTH - 850;
    dest.h = 15;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
 	SDL_FreeSurface(surface);
}

void draw_menu(SDL_Renderer* renderer)
{
    but_start ={470,280,400,110};
    SDL_Texture* bg;
    bg=IMG_LoadTexture(renderer,"C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\data\\7.png");
    gclick= Mix_LoadWAV("C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\theme\\scratch.wav");
    SDL_RenderCopy(renderer,bg,NULL,NULL);
    SDL_RenderPresent(renderer);
}

void run_menu(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor)
{

    int mouseX, mouseY;
    SDL_Event e;
    while(1)
    {
        SDL_PollEvent(&e);
        draw_menu(renderer);
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_start.x&&mouseX<=but_start.x+but_start.w&&mouseY>=but_start.y&&mouseY<=but_start.y+but_start.h)
        {
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
    }
    //cout<<e_dame;
}

void draw_score(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, int score)
{
    // Set score:
    string text3 = "SCORE : ";
    string temp = to_string(score);

    text3 = text3 + temp;

    printText(renderer,text3,0,0,font,textColor);
    SDL_RenderPresent(renderer);
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}


SDL_Texture* LoadTexture(std::string path,SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        cout<< "Unable to load image" << path << " SDL_image Error " << IMG_GetError <<endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            cout<< "Unable to create texture from " << path << "SDL_Error " << SDL_GetError << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
// moved from main.cpp
float generateRandomNumber()
{
    return (float) rand() / RAND_MAX;
}

void renderSplashScreen()
{
    cout << "Press any key to start game" << endl;
    waitUntilKeyPressed();
}

void drawCell(SDL_Renderer* renderer, int left, int top, Position pos, SDL_Texture* texture)
{
	SDL_Rect cell;
	cell.x = left + pos.x * CELL_SIZE + 5;
	cell.y = top + pos.y * CELL_SIZE + 5;
	cell.w = CELL_SIZE-10;
	cell.h = CELL_SIZE-10;
	SDL_RenderCopy(renderer, texture, NULL, &cell);
}

void drawCherry(SDL_Renderer* renderer, int left, int top, Position pos, Gallery* gallery)
{
    SDL_Texture* apple = LoadTexture("C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\data\\10.png", renderer);
    drawCell(renderer, left, top, pos, apple);
}

void drawSnake(SDL_Renderer* renderer, int left, int top, vector<Position> pos, Gallery* gallery)
{
	// snake's head
	drawCell(renderer, left, top, pos[pos.size()-1], gallery->getImage(PIC_SNAKE_HEAD));

	// snake's body
    for (int i = pos.size() - 2; i >= 0; i--) {
        SDL_Texture* texture = gallery->getImage(
			pos[i].y == pos[i+1].y ? PIC_SNAKE_HORIZONTAL : PIC_SNAKE_VERTICAL);
        drawCell(renderer, left, top, pos[i], texture);
    }
}

void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells)
{
    SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
    SDL_RenderDrawLine(renderer, left, top, left, top + cells * CELL_SIZE);
}

void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells)
{
    SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
    SDL_RenderDrawLine(renderer, left, top, left + cells * CELL_SIZE, top);
}

void renderGamePlay(SDL_Renderer* renderer, const Game& game, Gallery* gallery, TTF_Font* font)
{
    int top = 0, left = 0, gscore = game.getScore();

    SDL_SetRenderDrawColor(renderer, BOARD_COLOR.r, BOARD_COLOR.g, BOARD_COLOR.b, 0);
    SDL_RenderClear(renderer);


    for (int x = 0; x <= BOARD_WIDTH; x++)
        drawVerticalLine(renderer, left + x*CELL_SIZE, top, BOARD_HEIGHT);
    for (int y = 0; y <= BOARD_HEIGHT; y++)
        drawHorizontalLine(renderer, left, top+y * CELL_SIZE, BOARD_WIDTH);
    SDL_Texture* bkgr = LoadTexture("C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\data\\6.png", renderer);
    SDL_RenderCopy(renderer, bkgr, NULL, NULL);

    draw_score(renderer, font, WHITE, gscore);
    drawCherry(renderer, left, top, game.getCherryPosition(), gallery);
    drawSnake(renderer, left, top, game.getSnakePositions(), gallery);
    SDL_RenderPresent(renderer);
}

void renderGameOver(SDL_Renderer* renderer, const Game& game)
{
    SDL_Texture* endbk = LoadTexture("C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\data\\over.png", renderer);
    SDL_RenderCopy(renderer, endbk, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
}

void interpretEvent(SDL_Event e, Game& game)
{
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        	case SDLK_UP: game.processUserInput(UP); break;
        	case SDLK_DOWN: game.processUserInput(DOWN); break;
        	case SDLK_LEFT: game.processUserInput(LEFT); break;
        	case SDLK_RIGHT: game.processUserInput(RIGHT); break;
        }
    }
					//Handle key press
}


void updateRankingTable(const Game& game)
{

}
