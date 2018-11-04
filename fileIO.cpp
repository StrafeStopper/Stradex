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

int loadText(std::string path)
{
  fstream map;

  map.open("settings/window_size.txt");
  int t1, t2;
  map >> t1;
  map >> t2;

  SCREEN_WIDTH = t1;
  SCREEN_HEIGHT = t2;
  //cout << t1 << endl << t2 << endl;
  map.close();
}
