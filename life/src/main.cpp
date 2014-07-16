#include "SDL/SDL.h"
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CELL_SIZE = 8;

int main(int argc, char* args[]) {
    // setup
    SDL_Surface *screen = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("Game of Life", "Game of Life");
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

    bool tiles[SCREEN_WIDTH / CELL_SIZE][SCREEN_HEIGHT / CELL_SIZE];
    for (int i = 0; i < SCREEN_WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < SCREEN_HEIGHT / CELL_SIZE; j++) {
            tiles[i][j] = false;
        }
    }
    tiles[4][4] = true;

    SDL_Event event;
    bool play = true;

    // Main loop
    while (play) {

        // Clear the screen:
        SDL_FillRect(screen, &screen->clip_rect,
                SDL_MapRGB(screen->format, 255, 255, 255));


        for (int i = 0; i < SCREEN_WIDTH / CELL_SIZE; i++) {
            for (int j = 0; j < SCREEN_WIDTH / CELL_SIZE; j++) {
                if (tiles[i][j]) {
                    SDL_Rect rect = {i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE}; // x, y, width, height
                    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
                }
            }
        }

        SDL_Flip(screen);


        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                //Quit the program
                play = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                tiles[x / CELL_SIZE][y / CELL_SIZE] = !tiles[x / CELL_SIZE][y / CELL_SIZE];
            }
        }
    }

    // cleanup
    SDL_FreeSurface(screen);
    SDL_Quit();
    return 0;
}
