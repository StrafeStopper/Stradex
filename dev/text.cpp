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


//file for handling the text stream in the engine

//box to render text in on the screen
SDL_Rect tsClip[1];



//text texture
cTexture streamedText;

//this function loads the text to be rendered to the stream
void textStream(std::string tts) /*tts stands for test to stream */
{
  sFont = TTF_OpenFont("assets/Ubuntu-R.ttf", 14);
  textColor = { 0, 0, 0 };
  streamedText.loadFromRenderedText(tts, textColor);
}





void renderTextStream(SDL_Rect camera)
{
  tsClip[0].x = 0;
  tsClip[0].y = 0;
  tsClip[0].w = 300;
  tsClip[0].h = 40;
  SDL_Rect textView;
  textView.x = 200;
  textView.y = 200;
  textView.w = 300;
  textView.h = 40;
  SDL_RenderSetViewport(renderer, &textView);
  streamedText.render(0, 0, NULL, NULL, NULL, SDL_FLIP_NONE);

}
