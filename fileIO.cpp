#include <stdio.h>
#include <stdlib.h>
#include "tchar.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "main.h"
#include "init.h"
#include "load.h"
#include "game.h"
#include "fileIO.h"
#include <string>
#include <cmath>


void loadText()
{
  std::ifstream map("assets/text.txt");

  if (map == NULL)
  printf("Failed to load text file\n");

  std::string textOutput;
  map >> textOutput;

  std::cout << textOutput  << std::endl;
}
