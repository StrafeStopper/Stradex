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

SDL_Texture* loadTexture(std::string path);
TTF_Font *sFont = NULL;
SDL_Rect backRect[1];
SDL_Rect spriteClips[3];
SDL_Rect wulf[1];
SDL_Rect buttonBox[1];
SDL_Rect text_[1];
SDL_Rect menuBackRect[1];
SDL_Color textColor = { 255, 0, 0 };

int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 100;
int TOTAL_BUTTONS = 3;

cTexture title;
cTexture dungeon_floor;
cTexture playerMain;
cTexture buttonsSprite;
cTexture menuBackground;
cTexture basicSprite;
SDL_Rect buttonsClip[6];
mButton playButton;
mButton optionsButton;
mButton quitButton;

enum buttonTypes
{
	//button states
	//R is regular
	//I is inside, mouse over
	BUTTON_R = 0,
	BUTTON_I = 1
};

player player1;

int playerW;
int playerH;

bool clip = 0;


SDL_Rect* wulfClip = &wulf[0];

SDL_RendererFlip flipType = SDL_FLIP_NONE;

int enemyHealth = 100;


cTexture::cTexture()
{
	//init textre for loading
	hTexture = NULL;
	hWidth = 0;
	hHeight = 0;
}
cTexture::~cTexture()
{
	free();
}



 void cTexture::free()
 {

	 //DESTROY
 		SDL_DestroyTexture(hTexture);
 		hTexture = NULL;
 		hWidth = 0;
 		hHeight = 0;

 }

bool cTexture::loadFromFile(std::string path)
{
	//load textures from image files
	//dont mess with it because it will break
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	printf("IMG_Load failed\n");
	if(renderer == NULL)
	printf("SDL Error: Renderer is broken... \n", SDL_GetError());
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if(newTexture == NULL)
	printf("Failed to create texture from surface. SDL Error: %s\n", SDL_GetError());
	hWidth = loadedSurface->w;
	hHeight = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
	hTexture = newTexture;

	return hTexture != NULL;
}

void cTexture::render(int x, int y, SDL_Rect * clip, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
	//render the texture as requested
	//dont mess with it because it will break
	SDL_Rect renderQuad = { x, y, hWidth, hHeight };
	//SDL_Rect renderQuad = { x, y, clip->w, clip->h };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, hTexture, clip, &renderQuad, angle, center, flip);
}

bool cTexture::collisionCheck(SDL_Rect a, SDL_Rect b)
{
	//duplicate collision detection function for texture instead of players
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if( bottomA <= topB )
    {
        return 0;
    }

    if( topA >= bottomB )
    {
        return 0;
    }

    if( rightA <= leftB )
    {
        return 0;
    }

    if( leftA >= rightB )
    {
        return 0;
    }

    return 1;
}

void cTexture::loadFromRenderedText(std::string textTexture, SDL_Color color)
{
	//load font for text rendering
	//dont mess with it because it'll break
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(sFont, textTexture.c_str(), textColor);
	hTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	hWidth = textSurface->w;
	hHeight = textSurface->h;
	SDL_FreeSurface(textSurface);
}


void cTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(hTexture, red, green, blue);
}

void cTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(hTexture, blending);
}

void cTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(hTexture, alpha);
}

int cTexture::getWidth() { return hWidth; }
int cTexture::getHeight() { return hHeight; }



void loadAssets(Tile* tiles[])
{
	//load all of the textures
	printf("Loading image assets in loadAssets()...\n");

	if (!dungeon_floor.loadFromFile("assets/dungeon_floor.jpg"))
	{
		printf("Failed to load image\n");
	}


	if(!playerMain.loadFromFile("assets/beowulf.png"))
	{
		printf("Failed to load image\n");
	}

	if(!menuBackground.loadFromFile("assets/abstract_wide.jpg"))
	{
		printf("Failed to load image\n");
	}

	if(!buttonsSprite.loadFromFile("assets/buttonSprite.png"))
	{
		printf("Failed to load image\n");
	}


	if(!basicSprite.loadFromFile("assets/basicSprite.png"))
	printf("Failed to load image\n");



//sprite clips for textures
//make sure you check your numbers so textures don't get rendered cut off or missing
	backRect[0].x = 0;
	backRect[0].y = 0;
	backRect[0].w = 1280;
	backRect[0].h = 720;

	wulf[0].x = 0;
	wulf[0].y = 0;
	wulf[0].w = 50;
	wulf[0].h = 89;


	buttonBox[0].x = 0;
	buttonBox[0].y = 0;
	buttonBox[0].w = 300;
	buttonBox[0].h = 100;

	text_[0].x = 0;
	text_[0].y = 0;
	text_[0].w = 640;
	text_[0].h = 200;

	menuBackRect[0].x = 640;
	menuBackRect[0].y = 180;
	menuBackRect[0].w = 1280;
	menuBackRect[0].h = 720;


	setTiles( tiles );



	sFont = TTF_OpenFont("assets/Ubuntu-L.ttf", 150);
	title.loadFromRenderedText("STRADEX", textColor);


	printf("Done!\n");

}


mButton::mButton()
{
	//init button
	mPos.x = 0;
	mPos.y = 0;

	mButtonCurrent = 1;
}

void mButton::setPosition(int x, int y)
{
	//put the button in its place
	mPos.x = x;
	mPos.y = y;
}

void mButton::render()
{
	//render the button
	buttonsSprite.render(mPos.x, mPos.y, &buttonsClip[mButtonCurrent], NULL, NULL, SDL_FLIP_NONE);
}

bool mButton::handleMouseEvent(SDL_Event* e, int buttonName)
{
	//check for mouse events on the buttons
	//changes the look of the button as needed
	 if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	 {
		 int x, y; SDL_GetMouseState( &x, &y );
		 bool inside = 1;

		  if( x < mPos.x )
			{
				inside = 0;
			}  else
			if( x > mPos.x + BUTTON_WIDTH )
			{
				inside = 0;
			} else
			if( y < mPos.y )
			{
				inside = 0;
			} else
			if( y > mPos.y + BUTTON_HEIGHT )
			{
				inside = 0;
			}

			if(!inside)
			{
				switch(buttonName)
				{
					case 0:
					mButtonCurrent = 0;
					break;

					case 1:
					mButtonCurrent = 1;
					break;

					case 2:
					mButtonCurrent = 2;
					break;
				}

			} else
			{
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				switch(buttonName)
				{
					case 0:
					mButtonCurrent = 3;
					break;

					case 1:
					mButtonCurrent = 4;
					break;

					case 2:
					mButtonCurrent = 5;
					break;
				}
				break;

				case SDL_MOUSEBUTTONDOWN:
				switch(buttonName)
				{
					case 0:
					mButtonCurrent = 0;
					return 1;
					//level1();
					break;

					case 1:
					mButtonCurrent = 1;
					return 1;
					break;

					case 2:
					mButtonCurrent = 2;
					return 1;
					//SDL_HideWindow(window);
					//close();
					break;
				}
				break;

				case SDL_MOUSEBUTTONUP:
				switch(buttonName)
				{
					case 0:
					mButtonCurrent = 3;
					break;

					case 1:
					mButtonCurrent = 4;
					break;

					case 2:
					mButtonCurrent = 5;
					break;
				}
				break;
	    }
      }
}
return 0;
}


player::player()
{
	//init player
	posX = 100;
	posY = 100;

	collider.x = 0;
	collider.y = 0;
	collider.w = PLAYER_WIDTH;
	collider.h = PLAYER_HEIGHT;

	if (!PERSPECTIVE_STYLE)
	PLAYER_VEL *= 50;

	clip.x = 0;
	clip.y = 0;
	clip.w = 50;
	clip.h = 89;

	velX = 0;
	velY = 0;
}

SDL_Rect player::getCollider()
{
	return collider;
}



void player::handleEvent( SDL_Event& e )
{

//check for player button events to allow movement
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {

        switch( e.key.keysym.sym )
        {
//if a key is pressed or released , add velocity accordingly
		case SDLK_w:
			if (!PERSPECTIVE_STYLE)
			velY -= PLAYER_VEL;
			break;

		case SDLK_s:
			if (!PERSPECTIVE_STYLE)
			velY += PLAYER_VEL;
			break;

		case SDLK_a:
			velX -= PLAYER_VEL;
			flipType = SDL_FLIP_HORIZONTAL;
			break;

		case SDLK_d:
			velX += PLAYER_VEL;
			flipType = SDL_FLIP_NONE;
			break;

		case SDLK_q:
			menu();
			break;

		    }
    }
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {

		case SDLK_w:
			if (!PERSPECTIVE_STYLE)
			velY += PLAYER_VEL;
			break;

		case SDLK_s:
			if (!PERSPECTIVE_STYLE)
			velY -= PLAYER_VEL;
			break;

		case SDLK_a: velX = 0; break;
		case SDLK_d: velX = 0; break;
        }
    }
}

bool jumping = 0;
bool falling = 0;

bool player::move( Tile *tiles[], float timeStep )
{
//move the player and check if it touches a wall or level bounds
	if (!PERSPECTIVE_STYLE)
		collider.x += velX * timeStep;
	else if(PERSPECTIVE_STYLE)
		collider.x += velX;

	if (!PERSPECTIVE_STYLE)
	{
		if( ( collider.x < 0 ) || ( collider.x + PLAYER_WIDTH > LEVEL_WIDTH ) || touchesWall( collider, tiles ))
	   	collider.x -= velX * timeStep;
	}

	if (PERSPECTIVE_STYLE)
	{
		if( ( collider.x < 0 ) || ( collider.x + PLAYER_WIDTH > LEVEL_WIDTH ) || touchesWall( collider, tiles ))
	   	collider.x -= velX;
	}

	if (!PERSPECTIVE_STYLE)
		collider.y += velY * timeStep;
	else if (PERSPECTIVE_STYLE)
		collider.y += velY;

	if (PERSPECTIVE_STYLE)
	{
		if( ( collider.y < 0 ) || ( collider.y + PLAYER_HEIGHT > LEVEL_HEIGHT ) /*|| touchesWall( collider, tiles )*/ )
		{
			collider.y -= velY;
		}
	}

	if (!PERSPECTIVE_STYLE)
	{
		if ( ( collider.y < 0 ) || ( collider.y + PLAYER_HEIGHT > LEVEL_HEIGHT ) || touchesWall( collider, tiles ) )
		collider.y -= velY * timeStep;
	}

	return 1;
}



bool player::onGround()
{
	//check if the player is on the ground
		clipCheck = collider;
		clipCheck.y += 1;
		if (touchesWall(clipCheck, tileSet))
		return 1;
		else
		return 0;

}

int player::roofClip()
{
	//check if the player is touches the roof while jumping
	clipCheck = collider;
	clipCheck.y -= 2;
	if(touchesWall(clipCheck, tileSet))
	{
		clipCheck = collider;
		clipCheck.y += 32;
		if(!touchesWall(clipCheck, tileSet))
		{
			//(rg) pair r = touched roof. g = ground is 30 pixels (or less) below
			//10 roof is touched and ground is not below
			return 10;
		} else {
			//11 roof is touched and ground is below
			return 11;
		}
	}
	else
	{
		//00 roof is not touched and ground is N/A
		return 00;
	}
}

void player::clipStop()
{
	//hard stop the player
	//just for testing
	velY = 0;
	velX = 0;
}

void player::render(SDL_Rect& camera)
{
	//render the player after movement
	playerMain.render( (int)collider.x - camera.x, (int)collider.y - camera.y, &clip, NULL, NULL, flipType );
}

void player::setCamera(SDL_Rect& camera)
{
	//set the camera after the player moves 
	camera.x = ( collider.x + PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( collider.y + PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;


	if( camera.x < 0 )
	{
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

double player::getX()
{
	return posX;
}

double player::getY()
{
	return posY;
}
