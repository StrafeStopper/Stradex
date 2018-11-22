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
#include <string>
#include <cmath>

//comment

double y = 0;
bool fallingOff = 0;

int player_w = 50;
int player_h = 89;


const Uint8* keyState = SDL_GetKeyboardState( NULL );

SDL_Rect* backround = &backRect[0];
SDL_Rect* buttonClip = &buttonBox[0];

bool quit = 0;
SDL_Event e;

SDL_Rect startTextBox;
SDL_Rect screenSpace;
SDL_Rect wulfBox;
SDL_Rect zeroClip;

Timer stepTimer;





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


    player1.collider.x = 51;
    player1.collider.y = 550;
    flipType = SDL_FLIP_NONE;
    jumping = 0;
    player1.velY = 0;
    player1.velX = 0;
    falling = 0;

    while (!quit)
    {
      //SDL_RenderClear(renderer);

        dungeon_floor.render(0,0, backround, NULL, NULL, SDL_FLIP_NONE);



        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
    	    {
    		          quit = 1;
    		  } else
          if(e.type == SDL_KEYDOWN )
          {
            if (jumping == 1)
            {
              //do nothing
            } else
            if(PERSPECTIVE_STYLE)
            {
            if (e.key.keysym.sym == SDLK_SPACE )
            {
              //falling = 0;
              jumping = 1;
              y = player1.collider.y;
            }
          }
          }
              player1.handleEvent(e);
          }

          float timeStep = stepTimer.getTicks() / 1000.f;


          player1.move(tileSet, timeStep);

          if (PERSPECTIVE_STYLE)
          {
          if (jumping)
          {
            if(!falling)
            player1.velY -= (1);

            if (player1.collider.y <= (y - 65) || falling == 1)
            {
              falling = 1;
              //jumping = 0;
              player1.velY += (1);
            }
            if (touchesWall(player1.collider, tileSet))
            {
              jumping = 0;
              falling = 0;
              player1.velY = 0;
              player1.collider.y = tileSet[bottomTile]->getBox().y - 89;
            }
          }

          int roofTest = 0;
          roofTest = player1.roofClip();
          if(roofTest > 0)
          {
            //printf("clipping roof\n");
            if (roofTest == 10)
            {
              printf("10\n");
              jumping = 1;
              falling = 1;
              player1.velY = 0;
              player1.collider.y = tileSet[bottomTile]->getBox().y + 61;
            }
            /*jumping = 1;
            falling = 1;
            player1.velY = 0;
            player1.collider.y = tileSet[bottomTile]->getBox().y + 31;*/
          }



          if (falling == 0 && jumping == 0 && !player1.onGround())
          {
              jumping = 1;
              falling = 1;
          }
}


          stepTimer.start();

          player1.setCamera(camera);
          SDL_RenderClear(renderer);

    for( int i = 0; i < TOTAL_TILES; ++i )
      {
        tileSet[ i ]->render( camera );
      }



		player1.render(camera);


		SDL_RenderPresent(renderer);

    }
}
