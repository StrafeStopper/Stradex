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

//comment

double x = 200;
double y = 200;

int wulf_w = 50;
int wulf_h = 89;


const Uint8* keyState = SDL_GetKeyboardState( NULL );

SDL_Rect* backround = &backRect[0];
SDL_Rect* buttonClip = &buttonBox[0];

bool quit = 0;
SDL_Event e;

SDL_Rect startTextBox;
SDL_Rect screenSpace;
SDL_Rect wulfBox;
SDL_Rect zeroClip;







double angle = 0;

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
  int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

   leftA = a.x;
   rightA = a.x + a.w;
   topA = a.y;
   bottomA = a.y + a.h;

   leftB = b.x;
   rightB = b.x + b.w;
   topB = b.y;
   bottomB = b.y + b.h;

   if( bottomA <= topB )
 {
     return 0;
 }

 if( topA >= bottomB )
 {
     return 0;
 }

 if( rightA <= leftB )
 {
     return 0;
 }

 if( leftA >= rightB )
 {
     return 0;
 }

if(leftB == 1100)
clip = 1;

 return 1;
}




void level1()
{
    //loadAssets();
    //menu();
    SDL_ShowWindow(window);
    SDL_RenderClear(renderer);

    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    startTextBox.x = 300;
    startTextBox.y = 200;
    startTextBox.w = 700;
    startTextBox.h = 300;

    screenSpace.x = 0;
    screenSpace.y = 0;
    screenSpace.w = SCREEN_WIDTH;
    screenSpace.h = SCREEN_HEIGHT;


    zeroClip.x = 0;
    zeroClip.y = 0;
    zeroClip.w = 0;
    zeroClip.h = 0;

    SDL_RenderClear(renderer);
    int swordLoop = 0;

    while (!quit)
    {
        SDL_RenderClear(renderer);
        dungeon_floor.render(0,0, backround, NULL, NULL, SDL_FLIP_NONE);



        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
    	    {
    		          quit = 1;
    		  }
              player1.handleEvent(e);
          }


    for( int i = 0; i < TOTAL_TILES; ++i )
      {
        tileSet[ i ]->render( camera );
      }

    player1.move(zeroClip);
    player1.setCamera(camera);
    //player1.clipStop();






		x = player1.getX();
		y = player1.getY();

		wulfBox.x = x;
		wulfBox.y = y;
		wulfBox.w = 50;
		wulfBox.h = 89;


		player1.render(camera);



		SDL_RenderPresent(renderer);
		
    }
}
