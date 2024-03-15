#include "handler.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    window = SDL_CreateWindow("Formulaire de connexion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void handleInput(SDL_Event *event, char *loginText, char *passwordText, bool *loginActive, bool *passwordActive, bool *loggedIn) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= 10 + 20 + 200 && mouseX <= 10 + 20 + 200 + 200 && mouseY >= 120 && mouseY <= 120 + 40) {
            // Clique sur le bouton "Connexion"
            *loggedIn = true;
        } else if (mouseX >= 10 + 20 + 200 && mouseX <= 10 + 20 + 200 + 200 && mouseY >= 10 && mouseY <= 10 + 40) {
            *loginActive = true;
            *passwordActive = false;
        } else if (mouseX >= 10 + 20 + 200 && mouseX <= 10 + 20 + 200 + 200 && mouseY >= 60 && mouseY <= 60 + 40) {
            *loginActive = false;
            *passwordActive = true;
        }
    }

    if (*loginActive && event->type == SDL_TEXTINPUT) {
        strcat(loginText, event->text.text);
    } else if (*passwordActive && event->type == SDL_TEXTINPUT) {
        strcat(passwordText, event->text.text);
    } else if (event->type == SDL_KEYDOWN) {
        if (*loginActive && event->key.keysym.sym == SDLK_BACKSPACE && strlen(loginText) > 0) {
            loginText[strlen(loginText) - 1] = '\0';
        } else if (*passwordActive && event->key.keysym.sym == SDLK_BACKSPACE && strlen(passwordText) > 0) {
            passwordText[strlen(passwordText) - 1] = '\0';
        }
    }
}

void renderText(const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface != NULL) {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture != NULL) {
            SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

void renderMessageBox(const char *username) {
    SDL_Color bgColor = { 255, 255, 255, 255 };
    SDL_Color textColor = { 0, 0, 0, 255 };

    char message[256];
    snprintf(message, sizeof(message), "Connexion réussie pour : %s", username);

    int messageWidth, messageHeight;
    TTF_SizeText(font, message, &messageWidth, &messageHeight);

    SDL_Rect messageRect = { (WINDOW_WIDTH - messageWidth) / 2, (WINDOW_HEIGHT - messageHeight) / 2, messageWidth, messageHeight };

    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &messageRect);

    SDL_SetRenderDrawColor(renderer, textColor.r, textColor.g, textColor.b, textColor.a);
    SDL_RenderDrawRect(renderer, &messageRect);

    renderText(message, messageRect.x, messageRect.y, textColor);
}

void renderPasswordText(const char *password, int x, int y, SDL_Color color) {
    // Le caractère de remplacement pour les caractères du mot de passe
    const char maskChar = '*';
    int passwordLength = strlen(password);
    char maskedPassword[passwordLength + 1];

    // Remplace chaque caractère du mot de passe par le caractère de masquage
    memset(maskedPassword, maskChar, passwordLength);
    maskedPassword[passwordLength] = '\0';

    renderText(maskedPassword, x, y, color);
}
