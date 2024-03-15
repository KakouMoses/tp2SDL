#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

bool initSDL();
void closeSDL();
void handleInput(SDL_Event *, char *, char *, bool*, bool*, bool*);
void renderMessageBox(const char *);
void renderPasswordText(const char *, int, int, SDL_Color);