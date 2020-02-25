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
#include <sstream>
#include <cmath>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

//file for handling the text stream in the engine

//box to render text in on the screen
SDL_Rect tsClip[1];

//handler vars for multiple messages
int messageCount = 0;
std::string currentMessages[6];

//text texture
cTexture streamedText[6];
cTexture buildText;


//this function loads the text to be rendered to the stream
void textStream(std::string tts) /*tts stands for text to stream */
{
  for (int i = 0; i < 6; i++)
  {
    if (tts == textBuffer[i-1 || i == 0])
    {
      //do nothing
    } else
    textBuffer[i] = tts;
  }

  sFont = TTF_OpenFont("assets/Ubuntu-R.ttf", 14);
  textColor = { 0, 0, 0 };
  streamedText[messageCount].loadFromRenderedText(tts, textColor);

}





void renderTextStream(SDL_Rect camera)
{
  tsClip[0].x = 0;
  tsClip[0].y = 0;
  tsClip[0].w = 300;
  tsClip[0].h = 40;
  SDL_Rect textView;
  textView.x = 100;
  textView.y = 650;
  textView.w = 300;
  textView.h = 40;
  SDL_RenderSetViewport(renderer, &textView);
  streamedText[messageCount].render(0, 0, NULL, NULL, NULL, SDL_FLIP_NONE);

}

void renderBuildNumber(int b)
{
  std::string bs = patch::to_string(b);
  SDL_Rect textView;
  textView.x = SCREEN_WIDTH - 130;
  textView.y = 30;
  textView.w = 129;
  textView.h = 15;
  sFont = TTF_OpenFont("assets/Ubuntu-R.ttf", 14);
  textColor = { 255, 255, 255 };
  buildText.loadFromRenderedText("Build number:  " + bs, textColor);
  SDL_RenderSetViewport(renderer, &textView);
  buildText.render(0, 0, NULL, NULL, NULL, SDL_FLIP_NONE);
  SDL_RenderSetViewport(renderer, &screenSpace);
}
