#include "SDL/SDL.h"
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;

int main(int argc, char* args[]) {
  // setup
  SDL_Surface *screen = NULL;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption("SDL Snake", "SDL Snake");
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

  // Load the snake segment and convert it to SDL's display
  // format so we don't have to do it every time we blit
  SDL_Surface *temp = SDL_LoadBMP("gfx/snake_segment.bmp");
  SDL_Surface *snake_segment_sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  // Set up a rectangle for the snake sprite and its inital position
  SDL_Rect snake_segment_rectangle;
  snake_segment_rectangle.x = 200;
  snake_segment_rectangle.y = 200;
  snake_segment_rectangle.w = 33;
  snake_segment_rectangle.h = 33;

  // Fill the screen white

  // Main loop
  while(true) {
    SDL_FillRect(screen, &screen->clip_rect,
                 SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    snake_segment_rectangle.x += 10;
    if (snake_segment_rectangle.x >= SCREEN_WIDTH)
      break;
    SDL_BlitSurface(snake_segment_sprite, NULL, screen,
                    &snake_segment_rectangle);
    SDL_Delay(1000/FPS);
    SDL_Flip(screen);
  }

  // cleanup
  SDL_FreeSurface(screen);
  SDL_Quit();
  return 0;
}
