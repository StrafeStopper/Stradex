#include <stdio.h>
#include <stdlib.h>
#include "tchar.h"
#include <iostream>
#include <fstream>
#include "SDL2/i686-w64-mingw32/include/SDL2/SDL.h"
#include <iostream>
#include "SDL2/i686-w64-mingw32/include/SDL2/SDL_image.h"
#include "SDL2/i686-w64-mingw32/include/SDL2/SDL_ttf.h"
#include "main.h"
#include "init.h"
#include "load.h"
#include "game.h"
#include "fileIO.h"
#include "menu.h"
#include "text.h"
#include <string>
#include <cmath>

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

//default screen size, it is changed by the settings on launch anyway so this doesn't matter
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;


int bottomTile = 0;
int leftTile = 0;
int rightTile = 0;


bool init()
{
	//INIT ALL THE THINGS
	printf("Booting up SDL engine...\n");
	bool boot = 1;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//if it failed for some reason
		printf("SDL failed to initialize \n");
		boot = 0;
	}
	else {
		printf("SDL initialized!\n");
		//create the window
		//the first value is the window name, change as you please
		//the last value are SDL flags for various things such as redering api
		//it works fine with default flags, opengl has a few issues, change at your own risk
		window = SDL_CreateWindow("STRADEX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings[0], settings[1], SDL_WINDOW_HIDDEN /*| SDL_WINDOW_OPENGL*/);
		if(window == NULL)
		{
			printf("SDL failed to create window\n");
			boot = 0;
		} else
			printf("Window created!\n");

		//create renderer
		//do not change the first 2 values
		//last value is rendering flags
		//change as you dare but it works fine as is

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if(renderer == NULL)
		{
			printf("SDL failed to create renderer\n");
		} else
		printf("Renderer created\n");

		printf("Initializing SDL_image...\n");
		//int image libraries with png support
		//dont add any more flags
		//the default SDL engine supports most formats
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("Failed to initialize SDL_image\n");
			boot = 0;
		}
		else {
			printf("SDL_image initialized!\n");
		}

		printf("Initializing TTF...\n");

		if (TTF_Init() == -1)
		{
			//init ttf for text rendering
			printf("Failed to initialize TTF\n");
			boot = 0;
		}
		else {
			printf("TTF initialized!\n");
		}

		printf("Setting render draw color...\n");
		//render backround color for empty scences
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		printf("Render draw color set!\n");



	}
	printf("SDL boot compleate!\n\n");
	return boot;
}



//a few level and tile vars
int LEVEL_WIDTH = 2010;
int LEVEL_HEIGHT = 720;

int TILE_WIDTH = 30;
int TILE_HEIGHT = 30;

int TOTAL_TILE_SPRITES = 5;

int TILE_BLACK = 0;
int TILE_GREY = 1;
int TILE_BLUE = 2;
int TILE_RED = 3;
int TILE_GREEN = 4;


Tile::Tile( int x, int y, int tileType )
{
	//construct the tile class
    tileBox.x = x;
    tileBox.y = y;

    tileBox.w = TILE_WIDTH;
    tileBox.h = TILE_HEIGHT;

    PtileType = tileType;
}

void Tile::render( SDL_Rect& camera )
{
		//render the tile if its in the cameras view
    if( checkCollision( camera, tileBox ) )
    {
        basicSprite.render( tileBox.x - camera.x, tileBox.y - camera.y, &spriteClips[ PtileType ] );
    }
}

int Tile::getType()
{
    return PtileType;
}

SDL_Rect Tile::getBox()
{
    return tileBox;
}


int TOTAL_ACTI = 4;

int ACTI_0 = 0;
int ACTI_1 = 1;
int ACTI_2 = 2;
int ACTI_3 = 3;

Act::Act(int x, int y, int actiNumber)
{
	actiBox.x = x;
	actiBox.y = y;
	actiBox.w = TILE_WIDTH;
	actiBox.h = TILE_HEIGHT;

	pActiType = actiNumber;
}

SDL_Rect Act::getBox()
{
	return actiBox;
}

int Act::getType()
{
	return pActiType;
}

Act* actiMap[ TOTAL_TILES ];

void setActivation( Act* acti[] )
{
	//load activation map and set the locations
		printf("Setting activation tiles...\n");
		int x = 0, y = 0;

		std::ifstream map( "maps/level1_acti.map" );


		for( int i = 0; i < TOTAL_TILES; ++i )
		{

			int actiNumber = -1;

			map >> actiNumber;

			if( map.fail() )
			{
				printf( "Error loading map: Unexpected end of file\n" );
				break;
			}

			if( ( actiNumber >= 00 ) && ( actiNumber < TOTAL_ACTI ) )
			{
				acti[ i ] = new Act( x, y, actiNumber );
			}
			else
			{
				printf( "Error loading map: Invalid acti type at %d\n", i );
				break;
			}

			x += TILE_WIDTH;

			if( x >= LEVEL_WIDTH )
			{
				x = 0;

				y += TILE_HEIGHT;
			}
	}

		map.close();


}

void setTiles( Tile* tiles[] )
{
	//load map file and set the tiles
		printf("Setting map tiles...\n");
    int x = 0, y = 0;

    std::ifstream map( "maps/level1.map" );


		for( int i = 0; i < TOTAL_TILES; ++i )
		{

			int tileType = -1;

			map >> tileType;

			if( map.fail() )
			{
				printf( "Error loading map: Unexpected end of file\n" );
				break;
			}

			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}
			else
			{
				printf( "Error loading map: Invalid tile type at %d\n", i );
				break;
			}

			x += TILE_WIDTH;

			if( x >= LEVEL_WIDTH )
			{
				x = 0;

				y += TILE_HEIGHT;
			}

		//load tiles from texture
			spriteClips[ TILE_BLACK ].x = 0;
			spriteClips[ TILE_BLACK ].y = 0;
			spriteClips[ TILE_BLACK ].w = TILE_WIDTH;
			spriteClips[ TILE_BLACK ].h = TILE_HEIGHT;

			spriteClips[ TILE_GREY ].x = 30;
			spriteClips[ TILE_GREY ].y = 0;
			spriteClips[ TILE_GREY ].w = TILE_WIDTH;
			spriteClips[ TILE_GREY ].h = TILE_HEIGHT;

			spriteClips[ TILE_BLUE ].x = 60;
			spriteClips[ TILE_BLUE ].y = 0;
			spriteClips[ TILE_BLUE ].w = TILE_WIDTH;
			spriteClips[ TILE_BLUE ].h = TILE_HEIGHT;

			spriteClips[ TILE_RED ].x = 90;
			spriteClips[ TILE_RED ].y = 0;
			spriteClips[ TILE_RED ].w = TILE_WIDTH;
			spriteClips[ TILE_RED ].h = TILE_HEIGHT;

			spriteClips[ TILE_GREEN ].x = 120;
			spriteClips[ TILE_GREEN ].y = 0;
			spriteClips[ TILE_GREEN ].w = TILE_WIDTH;
			spriteClips[ TILE_GREEN ].h = TILE_HEIGHT;

	}

    map.close();


}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
	//check if the player touces a wall
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if( ( tiles[ i ]->getType() == TILE_BLACK )/* && ( tiles[ i ]->getType() <= TILE_BLACK ) */)
        {
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
								bottomTile = i;
                return 1;
            }
        }
    }

    return 0;
}

    Tile* tileSet[ TOTAL_TILES ];


//DO NOT mess with the timer
//I will not comment this beacause no one should need to understand or touch this
		Timer::Timer()
		{
		    mStartTicks = 0;
		    mPausedTicks = 0;

		    mPaused = false;
		    mStarted = false;
		}

		void Timer::start()
		{
		    mStarted = true;

		    mPaused = false;

		    mStartTicks = SDL_GetTicks();
			mPausedTicks = 0;
		}

		void Timer::stop()
		{
		    mStarted = false;

		    mPaused = false;

			mStartTicks = 0;
			mPausedTicks = 0;
		}

		void Timer::pause()
		{
		    if( mStarted && !mPaused )
		    {
		        mPaused = true;

		        mPausedTicks = SDL_GetTicks() - mStartTicks;
				mStartTicks = 0;
		    }
		}

		void Timer::unpause()
		{
		    if( mStarted && mPaused )
		    {
		        mPaused = false;

		        mStartTicks = SDL_GetTicks() - mPausedTicks;

		        mPausedTicks = 0;
		    }
		}

		Uint32 Timer::getTicks()
		{
			Uint32 time = 0;

		    if( mStarted )
		    {
		        if( mPaused )
		        {
		            time = mPausedTicks;
		        }
		        else
		        {
		            time = SDL_GetTicks() - mStartTicks;
		        }
		    }

		    return time;
		}

		bool Timer::isStarted()
		{
		    return mStarted;
		}




int close(Tile* tiles[])
{
	//shut everything down
	//doesnt need to be changed because it just destroys all of the things
	printf("\nShutting down...\nDestroying textures and renderers...\n");
	SDL_DestroyTexture(texture);
	texture = NULL;
	playerMain.free();
	title.free();
	menuBackground.free();
	buttonsSprite.free();

	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] == NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

	//SDL_DestroyRenderer(renderer);
	renderer = NULL;
	printf("SDL surfaces, textures, and renderers freed from memory!\nDestroying SDL window...\n");
	SDL_DestroyWindow(window);
	printf("SDL window detroyed!\n");
	printf("Shutting down TTF...\n");
	title.free();
	TTF_CloseFont(sFont);
	sFont = NULL;
	printf("TTF shut down!\n");
	printf("Quitting SDL subsystems...\n");

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	printf("All SDL subsystems shutdown!\n");
}
