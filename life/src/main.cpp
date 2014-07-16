#include "SDL/SDL.h"
#include <iostream>
#include <unistd.h>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CELL_SIZE = 1;
const int CELL_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int CELL_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

bool tiles[CELL_WIDTH][CELL_HEIGHT];
bool nextTiles[CELL_WIDTH][CELL_HEIGHT];

// Modulous operator that correctly handles negative values
int mod(int a, int b) {
    return (a % b + b) % b;
}

int countNeighbors(int x, int y) {
    return
        tiles[mod(x - 1, CELL_WIDTH)][mod(y - 1, CELL_HEIGHT)] +
        tiles[mod(x - 1, CELL_WIDTH)][y] +
        tiles[mod(x - 1, CELL_WIDTH)][mod(y + 1, CELL_HEIGHT)] +
        tiles[x][mod(y - 1, CELL_HEIGHT)] +
        tiles[x][mod(y + 1, CELL_HEIGHT)] +
        tiles[mod(x + 1, CELL_WIDTH)][mod(y - 1, CELL_HEIGHT)] +
        tiles[mod(x + 1, CELL_WIDTH)][y] +
        tiles[mod(x + 1, CELL_WIDTH)][mod(y + 1, CELL_HEIGHT)];
}


int main(int argc, char* args[]) {
    // setup
    SDL_Surface *screen = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("Game of Life", "Game of Life");
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

    SDL_Event event;
    bool play = true;
    bool step = false;
    bool forceStep = false;

    // Main loop
    while (play) {

        // Compute step
        if (forceStep || step) {
            // TODO: be more efficient with next_tiles -- this copying probably isn't necessary
            // Make temporary tiles for this iteration
            for (int i = 0; i < CELL_WIDTH; i++) {
                for (int j = 0; j < CELL_HEIGHT; j++) {
                    nextTiles[i][j] = tiles[i][j];
                }
            }

            // Computes changes
            for (int i = 0; i < CELL_WIDTH; i++) {
                for (int j = 0; j < CELL_HEIGHT; j++) {
                    int neighbors = countNeighbors(i, j);
                    if (tiles[i][j]) {
                        // Alive cell
                        if (neighbors < 2) {
                            nextTiles[i][j] = false;
                        } else if (neighbors > 3) {
                            nextTiles[i][j] = false;
                        }
                    } else {
                        // Dead cell
                        if (neighbors == 3) {
                            nextTiles[i][j] = true;
                        }
                    }
                }
            }

            // Copy changes into current tiles
            for (int i = 0; i < CELL_WIDTH; i++) {
                for (int j = 0; j < CELL_HEIGHT; j++) {
                    tiles[i][j] = nextTiles[i][j];
                }
            }
            usleep(100 * 1000);  // TODO: Do this properly
            step = false;
        }

        // Clear the screen:
        SDL_FillRect(screen, &screen->clip_rect,
                SDL_MapRGB(screen->format, 255, 255, 255));


        for (int i = 0; i < CELL_WIDTH; i++) {
            for (int j = 0; j < CELL_HEIGHT; j++) {
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
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    step = true;
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    forceStep = !forceStep;
                }
            }
        }
    }

    // cleanup
    SDL_FreeSurface(screen);
    SDL_Quit();
    return 0;
}
