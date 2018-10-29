
#ifndef INIT_H
#define INIT_H


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
const int TOTAL_TILES = 40000;
extern int TOTAL_TILE_SPRITES;

extern int TILE_BLACK;
extern int TILE_GREY;
extern int TILE_BLUE;
extern int TILE_RED;
extern int TILE_GREEN;


class Tile
{
    public:
		Tile( int x, int y, int tileType );

		void render( SDL_Rect& camera );

		int getType();

		SDL_Rect getBox();

    private:
		SDL_Rect tileBox;

		int PtileType;
};




void setTiles( Tile* tiles[] );
bool touchesWall( SDL_Rect box, Tile* tiles[] );
extern Tile* tileSet[ TOTAL_TILES ];

int close(Tile* tiles[]);



#endif // INIT_H
