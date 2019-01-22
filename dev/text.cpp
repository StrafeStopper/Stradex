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

//this function loads the text to be rendered to the stream
void textStream(std::string tts) /*tts stands for test to stream */
{
  tsFont = TTF_OpenFont("assets/Ubuntu-R.ttf", 11);
  streamedText.loadFromRenderedText(tts, textColor);
}



tsClip[0].x = 0;
tsClip[0].y = 0;
tsClip[0].w = 100;
tsClip[0].h = 40;

void renderTextStream()
{
  SDL_Rect textView;
  textView.x = camera.x + 40;
  textView.y = camera.y + 660;
  textView.w = 100;
  textView.h = 40;
  SDL_RenderSetViewport(renderer, &textView);
  streamedText.render(10, 25, tsClip, NULL, NULL, SDL_FLIP_NONE);
}
