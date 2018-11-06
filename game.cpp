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

double x = 300;
double y = 300;

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
    player1.collider.y = 599;
    flipType = SDL_FLIP_NONE;
    jumping = 0;
    currentJumpForce = 0.0f;
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
            if (e.key.keysym.sym == SDLK_SPACE )
            {
              //falling = 0;
              jumping = 1;
              y = player1.collider.y;
              //currentJumpForce = jumpForce;
            }
          }
              player1.handleEvent(e);
          }

          float timeStep = stepTimer.getTicks() / 1000.f;

        /*  if (jumping)
          {
              //printf("jump\n" );

              player1.velY -= currentJumpForce * timeStep * 4;

              if (player1.velY <= fallSpeed)
              {
                currentJumpForce = fallSpeed;
                player1.velY += gravity * timeStep * 4;
              } else {
                //currentJumpForce = fallSpeed;
              }

              if(touchesWall(player1.collider, tileSet))
              {
                player1.velY = 0;
                player1.collider.y -= 2;
                jumping = 0;
                currentJumpForce = 0.0;

              }
          }*/



          if (jumping)
          {

            player1.velY -= (300 * timeStep);
            if (player1.collider.y <= (y - 75) || falling == 1)
            {
              falling = 1;
              //jumping = 0;
              player1.velY += (800 * timeStep);
            }
            if (touchesWall(player1.collider, tileSet))
            {
              jumping = 0;
              falling = 0;
              player1.velY = 0;
              player1.collider.y -= 1;
            }
          }

          player1.move(tileSet, timeStep);

          stepTimer.start();

          player1.setCamera(camera);
          SDL_RenderClear(renderer);

    for( int i = 0; i < TOTAL_TILES; ++i )
      {
        tileSet[ i ]->render( camera );
      }


    //player1.clipStop();






		//x = player1.getX();
		//y = player1.getY();



		player1.render(camera);


		SDL_RenderPresent(renderer);

    }
}
