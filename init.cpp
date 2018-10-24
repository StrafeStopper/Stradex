
//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include "tchar.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "main.h"
#include "init.h"
#include "load.h"
#include "fileIO.h"
#include "menu.h"
#include <string>
#include <cmath>

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;


int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;



bool init()
{
	printf("Booting up SDL engine...\n");
	bool boot = 1;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL failed to initialize \n");
		boot = 0;
	}
	else {
		printf("SDL initialized!\n");
		window = SDL_CreateWindow("Light Development Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
		if(window == NULL)
		{
			printf("SDL failed to create window\n");
			boot = 0;
		} else
			printf("Window created!\n");


		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if(renderer == NULL)
		{
			printf("SDL failed to create renderer\n");
		} else
		printf("Renderer created\n");

		printf("Initializing SDL_image...\n");
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
			printf("Failed to initialize TTF\n");
			boot = 0;
		}
		else {
			printf("TTF initialized!\n");
		}

		printf("Setting render draw color...\n");
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		printf("Render draw color set!\n");



	}
	printf("SDL boot compleate!\n\n");
	return boot;
}

void close()
{
	printf("\nShutting down...\nDetroying textures and renderers...\n");
	SDL_DestroyTexture(texture);
	texture = NULL;
	dungeon_floor.free();
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
	SDL_DestroyRenderer(renderer);
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
