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

using namespace std;

//int settings[100];

int loadSettings(std::string path)
{
  printf("Loading settings...\n");
  fstream map;
  map.open(path.c_str());
  for (int i = 0; i < 100; i++)
  map >> settings[i];
  printf("Done!\n");
  map.close();
  printf("Applying settings...\n");
  player1.PLAYER_VEL = settings[2];
  printf("Done!\n");
}
