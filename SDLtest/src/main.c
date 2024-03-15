
#include <stdio.h>
#include <SDL.h>
#include <handler.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

int main(int argc, char *argv[]) {
    if (!initSDL()) {
        printf("Failed to initialize!\n");
        return -1;
    }

    font = TTF_OpenFont("arial.ttf", 28);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    char loginInputText[256] = "";
    char passwordInputText[256] = "";

    bool loginActive = false;
    bool passwordActive = false;
    bool loggedIn = false;

    bool cursorVisible = true;
    Uint32 lastCursorToggle = 0;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else {
                handleInput(&e, loginInputText, passwordInputText, &loginActive, &passwordActive, &loggedIn);
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - lastCursorToggle;

        if (elapsedTime > 500) {
            cursorVisible = !cursorVisible;
            lastCursorToggle = currentTime;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Color textColor = { 0, 0, 0, 255 };


        // Render Login Label
        renderText("Login:", 10, 10, textColor);

        // Render Login Text Field
        SDL_Rect loginRect = { (WINDOW_WIDTH - 200) / 2, 10, 200, 40 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &loginRect);
        renderText(loginInputText, loginRect.x + 5, loginRect.y + (loginRect.h - TTF_FontLineSkip(font)) / 2, textColor);
        if (loginActive && cursorVisible) {
            int cursorX = loginRect.x + TTF_FontLineSkip(font) + 5;
            SDL_RenderDrawLine(renderer, cursorX, loginRect.y, cursorX, loginRect.y + loginRect.h);
        }

        // Render Password Label
        renderText("Mot de passe:", 10, 60, textColor);



// Render Password Text Field
SDL_Rect passwordRect = { 10 + 20 + 200, 60, 200, 40 };
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
SDL_RenderDrawRect(renderer, &passwordRect);
renderPasswordText(passwordInputText, passwordRect.x + 5, passwordRect.y + (passwordRect.h - TTF_FontLineSkip(font)) / 2, textColor);

        if (passwordActive && cursorVisible) {
            int cursorX = passwordRect.x + TTF_FontLineSkip(font) + 5;
            SDL_RenderDrawLine(renderer, cursorX, passwordRect.y, cursorX, passwordRect.y + passwordRect.h);
        }

        // Render Connexion Button
        SDL_Rect buttonRect = { (WINDOW_WIDTH - 200) / 2, 120, 200, 40 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &buttonRect);
        int textWidth, textHeight;
        TTF_SizeText(font, "Connexion", &textWidth, &textHeight);
        renderText("Connexion", buttonRect.x + (buttonRect.w - textWidth) / 2, buttonRect.y + (buttonRect.h - textHeight) / 2, textColor);

        if (loggedIn) {
    renderMessageBox(loginInputText);
}

        SDL_RenderPresent(renderer);
    }

    closeSDL();

    return 0;
}

/*{
    SDL_Window *window = NULL;
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              500, 500, SDL_WINDOW_SHOWN);
    if (NULL == window)
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
    else
    {
        SDL_Delay(5000);
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}
*/
