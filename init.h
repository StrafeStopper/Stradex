
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
void close();



#endif // INIT_H
