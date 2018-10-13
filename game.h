#ifndef GAME_H
#define GAME_H


extern int wulf_w;
extern int wulf_h;

extern bool checkCollision(SDL_Rect a, SDL_Rect b);
extern 	double x;
extern	double y;

extern const Uint8* keyState;

extern bool quit;


extern void level1();
extern int menu();

extern const Uint8* keyState;

extern double angle;






#endif //GAME_H
