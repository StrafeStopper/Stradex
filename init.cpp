
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
//#include <conio.h>
//#include <Windows.h>
#include <string>
#include <cmath>

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
cWindow gWindows[ 2 ];


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int TOTAL_WINDOWS = 2;

cWindow::cWindow()
{
	pWindow = NULL;
	pWindowID = -1;
	mouseFocus = 0;
	keyboardFocus = 0;
	fullScreen = 0;
	minimized = 0;
	width = 0;
	height = 0;
}

bool cWindow::init(int W_WIDTH, int W_HEIGHT)
{
	pWindow = SDL_CreateWindow("Light Development Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
	if(pWindow != NULL)
	{
		mouseFocus = 1;
		keyboardFocus = 1;
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;

		shown = true;
	}
	return pWindow != NULL;
}


void cWindow::handleEvent(SDL_Event& e)
{
	if(e.type == SDL_WINDOWEVENT)
	{

		switch(e.window.event)
		{
	            case SDL_WINDOWEVENT_SHOWN:
	            shown = true;
	            break;

	            case SDL_WINDOWEVENT_HIDDEN:
	            shown = false;
	            break;

	            case SDL_WINDOWEVENT_SIZE_CHANGED:
	            width = e.window.data1;
	            height = e.window.data2;
	            SDL_RenderPresent( pRenderer );
	            break;

	            case SDL_WINDOWEVENT_EXPOSED:
	            SDL_RenderPresent( pRenderer );
	            break;

	            case SDL_WINDOWEVENT_ENTER:
	            mouseFocus = true;
	            break;

	            case SDL_WINDOWEVENT_LEAVE:
	            mouseFocus = false;
	            break;

	            case SDL_WINDOWEVENT_FOCUS_GAINED:
	            keyboardFocus = true;
	            break;

	            case SDL_WINDOWEVENT_FOCUS_LOST:
	            keyboardFocus = false;
	            break;

	            case SDL_WINDOWEVENT_MINIMIZED:
	            minimized = true;
	            break;

	            case SDL_WINDOWEVENT_MAXIMIZED:
	            minimized = false;
	            break;

	            case SDL_WINDOWEVENT_RESTORED:
	            minimized = false;
	            break;

				case SDL_WINDOWEVENT_CLOSE:
				SDL_HideWindow( pWindow );
				break;
		}
	}
}


int cWindow::getWidth()
{
    return width;
}

int cWindow::getHeight()
{
    return height;
}

bool cWindow::hasMouseFocus()
{
    return mouseFocus;
}

bool cWindow::hasKeyboardFocus()
{
    return keyboardFocus;
}

bool cWindow::isMinimized()
{
    return minimized;
}

void cWindow::focus()
{
	if(!shown)
	{
		SDL_ShowWindow(pWindow);
	}
	SDL_RaiseWindow(pWindow);
}

void cWindow::render()
{
		SDL_RenderClear(pRenderer);
		SDL_RenderPresent(pRenderer);

}
void cWindow::free()
{
	SDL_DestroyWindow(pWindow);

	mouseFocus = false;
	keyboardFocus = false;
	width = 0;
	height = 0;
}

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
		window = SDL_CreateWindow("Light Development Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
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
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	printf("SDL surfaces, textures, and renderers freed from memory!\nDestroying SDL window...\n");
	//SDL_DestroyWindow(window);

	gWindows[0].free();
	gWindows[1].free();
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
