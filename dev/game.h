#ifndef GAME_H
#define GAME_H


extern int player_w;
extern int player_h;

extern bool checkCollision(SDL_Rect a, SDL_Rect b);
extern 	double x;
extern	double y;

extern const Uint8* keyState;

extern bool quit;

extern SDL_Event e;

extern SDL_Rect camera;

extern void level1();
extern void activate();


extern const Uint8* keyState;

extern double angle;

extern SDL_Rect screenSpace;

extern float timeStep;

extern int roofTest;



#endif //GAME_H
