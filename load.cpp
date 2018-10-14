//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include "tchar.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "main.h"
#include "init.h"
#include "load.h"
#include "game.h"
#include <string>
#include <cmath>

SDL_Texture* loadTexture(std::string path);
TTF_Font *sFont = NULL;
SDL_Rect backRect[1];
SDL_Rect wulf[1];
SDL_Rect buttonBox[1];
SDL_Rect b_s[1];
SDL_Rect text_[1];
SDL_Rect menuBackRect[1];
SDL_Color textColor = { 255, 0, 0 };

int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 100;
int TOTAL_BUTTONS = 3;

cTexture title;
cTexture dungeon_floor;
cTexture beowulf;
cTexture giantSword;
cTexture beowulfSword;
cTexture playButton;
cTexture optionsButton;
cTexture quitButton;
cTexture buttonsSprite;
cTexture menuBackground;
SDL_Rect buttonsClip[6];
player player1;

int playerW;
int playerH;

bool clip = 0;

SDL_Rect* wulfClip = &wulf[0];

SDL_RendererFlip flipType = SDL_FLIP_NONE;

int enemyHealth = 100;


cTexture::cTexture()
{
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


 		SDL_DestroyTexture(hTexture);
 		hTexture = NULL;
 		hWidth = 0;
 		hHeight = 0;

 }

bool cTexture::loadFromFile(std::string path)
{
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
	//SDL_Rect renderQuad = { x, y, hWidth, hHeight };
	SDL_Rect renderQuad = { x, y, 480, 480 };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, hTexture, clip, &renderQuad, angle, center, flip);
}

bool cTexture::collisionCheck(SDL_Rect a, SDL_Rect b)
{
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



void loadAssets()
{
	//printf("Loading image assets in loadSurface(std::string path)...\n");
	printf("Loading image assets in loadAssets()...\n");

	if (!dungeon_floor.loadFromFile("assets/dungeon_floor.jpg"))
	{
		printf("Failed to load image\n");
	}


	if(!beowulf.loadFromFile("assets/beowulf.png"))
	{
		printf("Failed to load image\n");
	}


	if(!giantSword.loadFromFile("assets/sword.png"))
	{
		printf("Failed to load image\n");
	}


	if(!playButton.loadFromFile("assets/playButton.png"))
	{
		printf("Failed to load image\n");
	}


	if(!optionsButton.loadFromFile("assets/optionsButton.png"))
	{
		printf("Failed to load image\m");
	}


	if(!quitButton.loadFromFile("assets/quitButton.png"))
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

	b_s[0].x = 0;
	b_s[0].y = 0;
	b_s[0].w = 98;
	b_s[0].h = 118;

	text_[0].x = 0;
	text_[0].y = 0;
	text_[0].w = 640;
	text_[0].h = 200;

	menuBackRect[0].x = 640;
	menuBackRect[0].y = 180;
	menuBackRect[0].w = 1280;
	menuBackRect[0].h = 720;




	sFont = TTF_OpenFont("assets/Ubuntu-L.ttf", 150);
	title.loadFromRenderedText("<light>", textColor);


	printf("Done!\n");

}


mButton::mButton()
{
	mPos.x = 0;
	mPos.y = 0;

	mButtonCurrent = 1;
}

void mButton::setPostition(int x, int y)
{
	mPos.x = x;
	mPos.y = y;
}

void mButton::render()
{
	buttonsSprite.render(mPos.x, mPos.y, &buttonsClip[mButtonCurrent], NULL, NULL, SDL_FLIP_NONE);
}

void mButton::handleMouseEvent(SDL_Event* e)
{
	 if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	 {
		 int x, y; SDL_GetMouseState( &x, &y );
		 bool inside = 1;
		  if( x < mPos.x )
			{
				inside = false;
			}  else
			if( x > mPos.x + BUTTON_WIDTH )
			{
				inside = false;
			} else
			if( y < mPos.y )
			{
				inside = false;
			} else
			if( y > mPos.y + BUTTON_HEIGHT )
			{
				inside = false;
			}

			if(!inside)
			{
				mButtonCurrent = 1;
			} else
			{
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
			mButtonCurrent = 1;
				break;

				case SDL_MOUSEBUTTONDOWN:
				mButtonCurrent = 1;
				break;

				case SDL_MOUSEBUTTONUP:
				mButtonCurrent = 1;
				break;
	    }
      }
}
}


player::player()
{
	posX = 10;
	posY = 10;

	collider.w = PLAYER_WIDTH;
	collider.h = PLAYER_HEIGHT;

	velX = 0;
	velY = 0;
}

void player::handleEvent( SDL_Event& e )
{


	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {

        switch( e.key.keysym.sym )
        {
		case SDLK_w: velY -= PLAYER_VEL;
			break;
		case SDLK_s: velY += PLAYER_VEL;
			break;
		case SDLK_a: velX -= PLAYER_VEL;
			flipType = SDL_FLIP_HORIZONTAL;
			break;
		case SDLK_d: velX += PLAYER_VEL;
			flipType = SDL_FLIP_NONE;
			break;

		    }
    }
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
		case SDLK_w: velY += PLAYER_VEL; break;
		case SDLK_s: velY -= PLAYER_VEL; break;
		case SDLK_a: velX += PLAYER_VEL; break;
		case SDLK_d: velX -= PLAYER_VEL; break;
        }
    }
}

bool player::move( SDL_Rect& box )
{

	posX += velX;
	collider.x = posX;

	if( ( posX < 0 ) || ( posX + PLAYER_WIDTH > SCREEN_WIDTH ) || checkCollision( collider, box ))
   {
	   posX -= velX;
	   collider.x = posX;
	   //clip = 1;
   }

	posY += velY;
	collider.y = posY;

	if( ( posY < 0 ) || ( posY + PLAYER_HEIGHT > SCREEN_HEIGHT ) || checkCollision( collider, box ) )
    {
        posY -= velY;
		collider.y = posY;
		//clip = 1;
    }
	return 1;
}

void player::render()
{
	beowulf.render(posX, posY, wulfClip, angle, NULL, flipType);
}

double player::getX()
{
	return posX;
}

double player::getY()
{
	return posY;
}
