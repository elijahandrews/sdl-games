#include "SDL/SDL.h"

int main(int argc, char* args[]) {
    SDL_Surface *screen = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("SDL Snake", "SDL Snake");
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    SDL_Delay(2000);
    SDL_FreeSurface(screen);
    SDL_Quit();
    return 0;
}
