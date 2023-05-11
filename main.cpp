// DO NOT CHANGE THIS FILE

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "SDL_utils.h"
#include "Game.h"
#include "Gallery.h"
#include "text.h"
#include "constants.h"
#include <bits/stdc++.h>



using namespace std;


#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

Gallery* gallery = nullptr;
Mix_Music *gMusic = NULL;


Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

bool loadMedia()
{

	bool success = true;


	gMusic = Mix_LoadMUS( "C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\theme\\Lobby-Time.mp3" );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}


	gScratch = Mix_LoadWAV( "C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\theme\\scratch.wav" );
	if( gScratch == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gHigh = Mix_LoadWAV( "C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\theme\\high.wav" );
	if( gHigh == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMedium = Mix_LoadWAV( "C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\theme\\medium.wav" );
	if( gMedium == NULL )
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gLow = Mix_LoadWAV( "C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\theme\\low.wav" );
	if( gLow == NULL )
	{
		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	return success;
}


int main(int argc, char* argv[])
{

    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    gallery = new Gallery(renderer);

    SDL_RenderPresent(renderer);
    Game game(BOARD_WIDTH, BOARD_HEIGHT);
    SDL_Event e;
    TTF_Font* font_ = TTF_OpenFont("C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\font\\ThaleahFat.ttf",15);
    SDL_Texture* bkgr = IMG_LoadTexture(renderer,"C:\\Users\\HP\\OneDrive\\Documents\\lastver\\snakebyme\\game20232\\data\\7.png");
    SDL_RenderCopy(renderer, bkgr, NULL, NULL);
    SDL_RenderPresent(renderer);
    renderSplashScreen();
    auto start = CLOCK_NOW();
    if( font_ == NULL ) printf("TTF_Init: %s\n", TTF_GetError());
    renderGamePlay(renderer, game, gallery, font_);

    while (game.isGameRunning()) {
        while (SDL_PollEvent(&e)) {
            interpretEvent(e, game);
            if( e.type == SDL_KEYDOWN && loadMedia() )
            {
                switch( e.key.keysym.sym )
                {

                    case SDLK_1:
                    Mix_PlayChannel( -1, gHigh, 0 );
                    break;


                    case SDLK_2:
                    Mix_PlayChannel( -1, gMedium, 0 );
                    break;


                    case SDLK_3:
                    Mix_PlayChannel( -1, gLow, 0 );
                    break;


                    case SDLK_4:
                    Mix_PlayChannel( -1, gScratch, 0 );
                    break;

                    case SDLK_9:

                       if( Mix_PlayingMusic() == 0 )
                       {

                           Mix_PlayMusic( gMusic, -1 );
                       }

                       else
                       {

                          if( Mix_PausedMusic() == 1 )
                          {

                              Mix_ResumeMusic();
                          }

                          else
                          {

                              Mix_PauseMusic();
                          }
                        }
                        break;

                    case SDLK_0:

                        Mix_HaltMusic();
							break;
                }
            }
        }
        auto end = CLOCK_NOW();
        ElapsedTime elapsed = end-start;
        if (elapsed.count() > STEP_DELAY) {
            game.nextStep();
            renderGamePlay(renderer, game, gallery, font_);

            start = end;
        }
        SDL_Delay(1);
    }
    renderGameOver(renderer, game);
    updateRankingTable(game);

    delete gallery;
    quitSDL(window, renderer);
    return 0;
}

