//#pragma once

#ifndef LOAD_H
#define LOAD_H

extern SDL_RendererFlip flipType;
extern int playerW;
extern int playerH;

extern bool clip;

extern int enemyHealth;

extern int BUTTON_WIDTH;
extern int BUTTON_HEIGHT;
extern int TOTAL_BUTTONS;



class cTexture {
	//texture wrapper class
public:
	cTexture();
	~cTexture();

	bool loadFromFile(std::string path);

	void free();

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	bool collisionCheck(SDL_Rect a, SDL_Rect b);

	void loadFromRenderedText(std::string text, SDL_Color textColor);

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void setBlendMode(SDL_BlendMode blending);

	void setAlpha(Uint8 alpha);

	int getWidth();

	int getHeight();

private:
	SDL_Texture * hTexture;
	int hWidth;
	int hHeight;
};

class player
{
	//player wrapper class
public:
	static const int PLAYER_WIDTH = 50;
	static const int PLAYER_HEIGHT = 89;

	double PLAYER_VEL = settings[2];

	player();

	void handleEvent( SDL_Event& e );

	bool move( Tile *tiles[], float timeStep );
	bool onGround();
	int roofClip();

	bool activationTile( SDL_Rect box, Tile* tiles[] );

	double getX();
	double getY();

	SDL_Rect getCollider();

	void setCamera( SDL_Rect& camera );

	void render(SDL_Rect& camera);

	void clipStop();

	SDL_Rect collider;
	SDL_Rect clipCheck;
	double posX, posY;
	double velX, velY;

private:


	SDL_Rect clip;




};


class mButton
{
	//button wrapper class
public:
	mButton();
	void setPosition(int x, int y);
	bool handleMouseEvent(SDL_Event* e, int buttonName);
	void render();

private:
	SDL_Point mPos;
	int mButtonCurrent;
};




extern bool jumping;
extern bool falling;


//all of the textres and stuff
extern SDL_Texture* loadTexture(std::string path);
extern TTF_Font *sFont;
extern SDL_Rect spriteClips[3];
extern SDL_Rect backRect[1];
extern SDL_Rect buttonBox[1];
extern SDL_Rect text_[1];
extern SDL_Rect menuBackRect[1];
extern SDL_Color textColor;
extern cTexture dungeon_floor;
extern cTexture playerMain;
extern cTexture title;
extern player player1;
extern cTexture menuBackground;
extern cTexture buttonsSprite;
extern SDL_Rect buttonsClip[6];
extern mButton playButton;
extern mButton optionsButton;
extern mButton quitButton;
extern cTexture basicSprite;




void loadAssets(Tile* tiles[]);

#endif //LOAD_H
