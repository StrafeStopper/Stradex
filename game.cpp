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

//comment

double x = 20;
double y = 20;

int wulf_w = 50;
int wulf_h = 89;


const Uint8* keyState = SDL_GetKeyboardState( NULL );

SDL_Rect* backround = &backRect[0];
SDL_Rect* buttonClip = &buttonBox[0];
SDL_Rect* textClip = &text_[0];
SDL_Rect* menuCLip = &menuBackRect[0];

bool quit = 0;
SDL_Event e;

SDL_Rect startTextBox;
SDL_Rect screenSpace;
SDL_Rect wulfBox;
SDL_Rect swordBox;



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


int menu()
{


    bool menuLoop = 0;

    SDL_Rect titleRect;

    titleRect.x = 320;
    titleRect.y = 30;
    titleRect.w = 640;
    titleRect.h = 150;
/*
    SDL_Rect buttonsRect[3];

    buttonsRect[0].x = 480;
    buttonsRect[0].y = 260;
    buttonsRect[0].w = 300;
    buttonsRect[0].h = 100;

    buttonsRect[1].x = 480;
    buttonsRect[1].y = 400;
    buttonsRect[1].w = 300;
    buttonsRect[1].h = 100;

    buttonsRect[2].x = 480;
    buttonsRect[2].y = 540;
    buttonsRect[2].w = 300;
    buttonsRect[2].h = 100;
    */

    SDL_ShowWindow(window);

    while(!menuLoop)
    {
      SDL_RenderClear(renderer);
      menuBackground.render(0, 0, menuCLip, NULL, NULL, SDL_FLIP_NONE);
      title.render(320, 0, textClip, NULL, NULL, SDL_FLIP_NONE);
      playButton.render(480, 260, buttonClip, NULL, NULL, SDL_FLIP_NONE);
      optionsButton.render(480, 400, buttonClip, NULL, NULL, SDL_FLIP_NONE);
      quitButton.render(480, 540, buttonClip, NULL, NULL, SDL_FLIP_NONE);
      SDL_RenderPresent(renderer);
    }


}


void level1()
{
    loadAssets();
    menu();
    SDL_ShowWindow(window);
    SDL_RenderClear(renderer);
    startTextBox.x = 300;
    startTextBox.y = 200;
    startTextBox.w = 700;
    startTextBox.h = 300;

    screenSpace.x = 0;
    screenSpace.y = 0;
    screenSpace.w = SCREEN_WIDTH;
    screenSpace.h = SCREEN_HEIGHT;


    swordBox.x = 1100;
    swordBox.y = 600;
    swordBox.w = 63;
    swordBox.h = 64;



    SDL_RenderClear(renderer);
    int swordLoop = 0;

    while (!quit)
    {
        SDL_RenderSetViewport(renderer, &screenSpace);
        SDL_RenderClear(renderer);
        dungeon_floor.render(0,0, backround, NULL, NULL, SDL_FLIP_NONE);


        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
    	    {
    		          quit = 1;
    		  }
              for( int i = 0; i < TOTAL_BUTTONS; ++i )
              {
                buttonsRect[ i ].handleMouseEvent( &e );
              }

              player1.handleEvent(e);
          }



    player1.move(swordBox);

		x = player1.getX();
		y = player1.getY();

		wulfBox.x = x;
		wulfBox.y = y;
		wulfBox.w = 50;
		wulfBox.h = 89;





    SDL_RenderSetViewport(renderer, &screenSpace);

		player1.render();



		SDL_RenderPresent(renderer);
		SDL_Delay(1);
    }
}
