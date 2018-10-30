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
#include "game.h"
#include "fileIO.h"
#include "menu.h"
#include <string>
#include <cmath>

SDL_Texture* texture = NULL;


Uint8 r = 255;
Uint8 g = 255;
Uint8 b = 255;



bool startT = 1;

double degrees = 0;

std::string command;
bool cmdLoop = 1;





int main(int argc, char* args[])
{
	printf("Welcome to the <Light> development project!\nCreated and developed by Strafe_Stopper\nUsing the SDL graphic rendering API in C++\nBooting up C++ libraries...\nDone!\n");
	//loadText("settings/window_size.txt");
	init();
	loadAssets(tileSet);
	menu();


	close(tileSet);
	printf("SDL successfully shutdown!\n\nPress [enter] to exit...\n");
	std::cin.get();
	printf("Exiting <Light>...\n");
	return 0;
}
