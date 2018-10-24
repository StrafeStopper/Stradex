#ifndef GAME_H
#define GAME_H


extern int wulf_w;
extern int wulf_h;

extern bool checkCollision(SDL_Rect a, SDL_Rect b);
extern 	double x;
extern	double y;

extern const Uint8* keyState;

extern bool quit;

extern SDL_Event e;



extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;

extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern int TOTAL_TILES;
extern int TOTAL_TILE_SPRITES;

extern int TILE_GREY;
extern int TILE_BROWN;
extern int TILE_BLUE;


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


extern void level1();









extern const Uint8* keyState;

extern double angle;






#endif //GAME_H
