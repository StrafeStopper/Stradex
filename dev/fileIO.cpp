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


bool PERSPECTIVE_STYLE;

using namespace std;

//int settings[100];

int loadSettings(std::string path)
{
  //loads the settings
  //change the for loop limit number to allow for more settings
  //hard to comment something that is being chnaged and added to so frequently
  //this doesnt really need to be chnaged because the settings file has all the chnaging you need

  printf("Loading settings...\n");
  fstream map;
  map.open(path.c_str());
  for (int i = 0; i < 100; i++)
  map >> settings[i];
  printf("Done!\n");
  map.close();
  printf("Applying settings...\n");
  player1.PLAYER_VEL = settings[2];
  PERSPECTIVE_STYLE = settings[3];
  printf("Done!\n");
}

int loadBuildNumber(std::string path)
{
  int build;
  printf("Loading raw text file...\n");
  fstream file;
  file.open(path.c_str(), ios::in);
  file >> build;
  cout << build << endl;
  file.close();
  file.open(path.c_str(), ios::out | ios::trunc);
  build++;
  file << build;
  cout << build << endl;
  printf("Done\n");
  file.close();
  return build;


}
