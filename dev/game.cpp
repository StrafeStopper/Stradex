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

//comment2

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
  //duel axis collision detection
  //checks x and y axis from 2 rects for a clip

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

 return 1;
}

void activate()
{
  //triggered when 'e' is pressed while the player is standing in an activatable tile
  int actiType = player1.activationTile(player1.collider, actiMap);

  if (actiType == ACTI_1)
  {
    //opens trigger ACTI_1
    printf("ACTI_1\n");
  } else if (actiType == ACTI_2)
  {
    //opens trigger ACTI_2
    printf("ACTI_2\n" );
  } else if (actiType == ACTI_3)
  {
    //opens trigger ACTI_3
    printf("ACTI_3\n" );
  } else
  {
    //printf("Oh shit something really bad happened \n");
  }
}


void level1()
{
    //start point for the main level

    //init a few level specific things
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

        //dungeon_floor.render(0,0, backround, NULL, NULL, SDL_FLIP_NONE);


        //check for events like quitting, button pushes etc
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
              jumping = 1;
              y = player1.collider.y;
            }
          }
          }
              //check movement
              player1.handleEvent(e);
          }

          //set physics ticks for frame independent movement
          //change the number for different physics speed
          //it works fine like this so try not to change it
          float timeStep = stepTimer.getTicks() / 1000.f;

          //move the player and check for collision
          player1.move(tileSet, timeStep);


          //if perspective is set to platform handle jumping
          if (PERSPECTIVE_STYLE)
          {
          if (jumping)
          {
            //I don't remember exactly how I got this working but I did. Try not to mess with it because it works fine
            //changing ANYTHING in this will probably break physics, please try to leave it alone
            if(!falling)
            {
              //this is the jumping speed, changing it will probably break some physics
              player1.velY -= (1);
            }

            if (player1.collider.y <= (y - 65) || falling == 1)
            {
              //if the player jumps 65 pixels above where it started, start falling
              falling = 1;

              //fall speed, try not to change this either, it will probably break some physics
              player1.velY += (1);
            }
            if (touchesWall(player1.collider, tileSet))
            {
              //while falling, if the player touches the ground, stop faling and teleport exactly on top of the ground
              //the telportation is simply a failsafe if the player fell into the ground, so it sets them back on top
              jumping = 0;
              falling = 0;
              player1.velY = 0;
              player1.collider.y = tileSet[bottomTile]->getBox().y - 89;
            }
          }

          int roofTest = 0;
          //detects roof collision and if the player can be safly teleported down to the ground if clipped
          //this doesnt work very well yet
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
              //if the player is not falling or jumping already
              //and the player is not on the ground, fall until the ground is hit
              jumping = 1;
              falling = 1;
          }
}

          //start the tick timer
          //dont mess with this
          stepTimer.start();

          //move the camera acording to player movement
          player1.setCamera(camera);
          SDL_RenderClear(renderer);

    for( int i = 0; i < TOTAL_TILES; ++i )
      {
        //render all of the level's tiles
        tileSet[ i ]->render( camera );
      }




    //render the player inside the camera view
		player1.render(camera);


    //print text to the screen
    //textStream("text stream test");
    //textStream("test 2");
    
    renderTextStream(camera);
    SDL_RenderSetViewport(renderer, &screenSpace);
    renderBuildNumber(build_number);
    SDL_RenderSetViewport(renderer, &screenSpace);

    //show the completed render
		SDL_RenderPresent(renderer);

    }
}
