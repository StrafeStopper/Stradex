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


SDL_Rect* textClip = &text_[0];
SDL_Rect* menuCLip = &menuBackRect[0];

bool menu()
{
  //show the menu
    bool menuLoop = 0;

    SDL_Rect titleRect;

//set the title and buttons
    titleRect.x = 320;
    titleRect.y = 30;
    titleRect.w = 640;
    titleRect.h = 150;

    //play r
    buttonsClip[ 0 ].x = 0;
    buttonsClip[ 0 ].y = 0;
    buttonsClip[ 0 ].w = BUTTON_WIDTH;
    buttonsClip[ 0 ].h = BUTTON_HEIGHT;

    //options r
    buttonsClip[ 1 ].x = 0;
    buttonsClip[ 1 ].y = 100;
    buttonsClip[ 1 ].w = BUTTON_WIDTH;
    buttonsClip[ 1 ].h = BUTTON_HEIGHT;

    //quit r
    buttonsClip[ 2 ].x = 0;
    buttonsClip[ 2 ].y = 200;
    buttonsClip[ 2 ].w = BUTTON_WIDTH;
    buttonsClip[ 2 ].h = BUTTON_HEIGHT;

    //play i
    buttonsClip[ 3 ].x = 301;
    buttonsClip[ 3 ].y = 0;
    buttonsClip[ 3 ].w = BUTTON_WIDTH;
    buttonsClip[ 3 ].h = BUTTON_HEIGHT;

    //options i
    buttonsClip[ 4 ].x = 301;
    buttonsClip[ 4 ].y = 100;
    buttonsClip[ 4 ].w = BUTTON_WIDTH;
    buttonsClip[ 4 ].h = BUTTON_HEIGHT;

    //quit i
    buttonsClip[ 5 ].x = 301;
    buttonsClip[ 5 ].y = 200;
    buttonsClip[ 5 ].w = BUTTON_WIDTH;
    buttonsClip[ 5 ].h = BUTTON_HEIGHT;


    playButton.setPosition(480, 260);
    optionsButton.setPosition(480, 400);
    quitButton.setPosition(480, 540);

    SDL_ShowWindow(window);

    while(!menuLoop)
    {
      SDL_RenderClear(renderer);

      while( SDL_PollEvent( &e ) != 0 )
      {
          if( e.type == SDL_QUIT )
        {
                menuLoop = 1;
        } else {

              if(playButton.handleMouseEvent( &e, 0 ))
              {
                //if the play button is pressed start the level
                level1();
              }

              if(optionsButton.handleMouseEvent( &e, 1 ))
              {
                //options will go hear once i do that :p
              }

              if(quitButton.handleMouseEvent( &e, 2 ))
              {
                //stop everything if the quit button is pushed
                SDL_HideWindow(window);
                close(tileSet);
                printf("SDL successfully shutdown!\n\nPress [enter] to exit...\n");
                std::cin.get();
                printf("Exiting <Light>...\n");
                exit(0);
                menuLoop = 1;

              }
          }
        }

        //render all the buttons and stuff
      menuBackground.render(0, 0, menuCLip, NULL, NULL, SDL_FLIP_NONE);
      title.render(320, 0, textClip, NULL, NULL, SDL_FLIP_NONE);
      playButton.render();
      optionsButton.render();
      quitButton.render();
      //renderBuildNumber(build_number);
      SDL_RenderPresent(renderer);
    }
      return 0;

}
