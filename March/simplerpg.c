#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "graphics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv)
{
    graphics_t *graphics = graphics_init(SCREEN_WIDTH, SCREEN_HEIGHT);

    /* Load texture */
    graphics_texture_load(graphics, 0, "textures/Character Boy.png");

    SDL_Event event;
    int quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;

            default:
                break;
            }
        }

        /* Clear screen */
        SDL_RenderClear(graphics->renderer);

        /* Render texture */
        SDL_RenderCopy(graphics->renderer, graphics->textures[0], NULL, NULL);

        /* Update screen */
        SDL_RenderPresent(graphics->renderer);
    }

    graphics_free(graphics);
    return 0;
}
