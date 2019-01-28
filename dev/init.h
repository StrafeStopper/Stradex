
#ifndef INIT_H
#define INIT_H

//init all the needed variables
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern SDL_Surface* currentSurface;
extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern SDL_Renderer* renderer;
extern SDL_Window* textWindow;




bool init();

extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;

extern int TILE_WIDTH;
extern int TILE_HEIGHT;
const int TOTAL_TILES = 1608;
extern int TOTAL_TILE_SPRITES;

extern int TILE_BLACK;
extern int TILE_GREY;
extern int TILE_BLUE;
extern int TILE_RED;
extern int TILE_GREEN;



extern int TOTAL_ACTI;

extern int ACTI_0;
extern int ACTI_1;
extern int ACTI_2;
extern int ACTI_3;


class Tile
{
    //class wrapper for the tiling engine
    public:
		Tile( int x, int y, int tileType );

		void render( SDL_Rect& camera );

		int getType();

		SDL_Rect getBox();
		SDL_Rect tileBox;

    private:


		int PtileType;
};

class Act
{
  //wrapper class for activation tiles to work properly
  public:
    Act( int x, int y, int actiNumber);

    int getType();

    SDL_Rect getBox();
    SDL_Rect actiBox;

  private:

    int pActiType;

};

class Timer
{
  //class wrapper fror the tick timer
  //DO NOT mess with this class, it works perfectly and does not need to be changed
  //timing can be changed in the level loop
    public:
		Timer();

		void start();
		void stop();
		void pause();
		void unpause();

		Uint32 getTicks();

		bool isStarted();
		bool isPaused();

    private:

		Uint32 mStartTicks;


		Uint32 mPausedTicks;


		bool mPaused;
		bool mStarted;
};



void setTiles( Tile* tiles[] );
void setActivation( Act* acti[] );
bool touchesWall( SDL_Rect box, Tile* tiles[] );
extern Tile* tileSet[ TOTAL_TILES ];
extern Act* actiMap[ TOTAL_TILES ];
extern int bottomTile;
extern int leftTile;
extern int rightTile;

int close(Tile* tiles[]);





#endif // INIT_H
