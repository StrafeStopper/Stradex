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
	init();
	loadAssets();
	//menu();
	loadText();


	///printf("Light:~# ");
	//std::cin >> command;


/*while(cmdLoop)
{
	if(command == "level1")
	{
		cmdLoop = 0;
		level1();
		command = " ";
	}
	else
	if( command == "init")
	{
		cmdLoop = 0;
	 	init();
		loadAssets();
		command = " ";
	}
	else
	if(command == "close")
	{
		cmdLoop = 0;
		close();
		command = " ";
	}
	else
	{
		cmdLoop = 1;
		printf("Command: \"");
		std::cout << command;
		printf("\" not recognized\n");
		command = " ";
		printf("Light:~# ");
		std::cin >> command;
	}
		menu();
}*/


	close();
	printf("SDL successfully shutdown!\n\nPress [enter] to exit...\n");
	std::cin.get();
	printf("Exiting <Light>...\n");
	return 0;
}
