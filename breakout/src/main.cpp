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

  int snake_vel_x = 440;
  int snake_vel_y = 440;

  Timer delta_timer; // used to calculate velocity
  delta_timer.Start();
  Timer fps_timer; // used to measure the fps once per second
  int frames = 0; // number of frames that have passed in the last second
  fps_timer.Start();
  SDL_Event event;
  bool play = true;

  // Main loop
  while(play) {

    // Clear the screen:
    SDL_FillRect(screen, &screen->clip_rect,
        SDL_MapRGB(screen->format, 182, 220, 156));

    if(SDL_PollEvent(&event)) {
    /*   /1* if(event.type == SDL_KEYDOWN) { *1/ */
    /*   /1*   switch(event.key.keysym.sym) { *1/ */
    /*   /1*     case SDLK_UP: message = upMessage; break; *1/ */
    /*   /1*     case SDLK_DOWN: message = downMessage; break; *1/ */
    /*   /1*     case SDLK_LEFT: message = leftMessage; break; *1/ */
    /*   /1*     case SDLK_RIGHT: message = rightMessage; break; *1/ */
    /*   /1*   } *1/ */
    /*   /1* } *1/ */
      if(event.type == SDL_QUIT) {
        //Quit the program
        play = false;
      }
    }

    // Move by 120 pixels / second, regardless of framerate
    snake_segment_rectangle.x += snake_vel_x * (delta_timer.GetTicks() / 1000.f);
    snake_segment_rectangle.y += snake_vel_y * (delta_timer.GetTicks() / 1000.f);

    if (snake_segment_rectangle.x + snake_segment_rectangle.w >= SCREEN_WIDTH || snake_segment_rectangle.x <= 0)
      snake_vel_x = -snake_vel_x; // change directions when we hit a wall
    if (snake_segment_rectangle.y + snake_segment_rectangle.h >= SCREEN_HEIGHT || snake_segment_rectangle.y <= 0)
      snake_vel_y = -snake_vel_y;

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
