
#ifndef INIT_H
#define INIT_H


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Surface* currentSurface;
extern SDL_Window* window;
extern SDL_Surface* screenSurface;
extern SDL_Renderer* renderer;
extern SDL_Window* textWindow;

//extern const int TOTAL_WINDOWS;

class cWindow
{
public:
    cWindow();

    bool init(int W_WIDTH, int W_HEIGHT);

    void render();

    void handleEvent( SDL_Event& e );

    void focus();

    void free();

    int getWidth();
    int getHeight();

    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();

private:
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    int pWindowID;

    int width;
    int height;

    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;
    bool shown;

};

extern cWindow gWindows[ 2 ];
bool init();
void close();



#endif // INIT_H
