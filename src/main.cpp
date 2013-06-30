#include "SDL/SDL.h"
#include <iostream>
#include "timer.h"
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
  snake_segment_rectangle.x = 0;
  snake_segment_rectangle.y = 200;
  snake_segment_rectangle.w = 33;
  snake_segment_rectangle.h = 33;

  Timer delta_timer; // used to calculate velocity
  delta_timer.Start();
  Timer fps_timer; // used to measure the fps once per second
  int frames = 0; // number of frames that have passed in the last second
  fps_timer.Start();

  // Main loop
  while(true) {

    // Clear the screen:
    SDL_FillRect(screen, &screen->clip_rect,
                 SDL_MapRGB(screen->format, 182, 220, 156));

    // Move by 120 pixels / second, regardless of framerate
    snake_segment_rectangle.x += 440 * (delta_timer.GetTicks() / 1000.f);
    if (snake_segment_rectangle.x >= SCREEN_WIDTH)
      break; // stop when we hit a wall
    SDL_BlitSurface(snake_segment_sprite, NULL, screen,
                    &snake_segment_rectangle);

    delta_timer.Start();
    SDL_Flip(screen);

    // Print the FPS to the command line once per second
    frames ++;
    if (fps_timer.GetTicks() > 1000) {
      cout << frames / (fps_timer.GetTicks() / 1000.f) << "\n";
      frames = 0;
      fps_timer.Start();
    }
  }

  // cleanup
  SDL_FreeSurface(screen);
  SDL_FreeSurface(snake_segment_sprite);
  SDL_Quit();
  return 0;
}
