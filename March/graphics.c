#include "graphics.h"

graphics_t *graphics_init(int width, int height)
{
    graphics_t *graphics = malloc(sizeof(graphics_t));

    /* Initialize SDL. */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        graphics_free(graphics);
        return NULL;
    }

    /* Create a window. */
    graphics->window = SDL_CreateWindow("march", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN);
    if (graphics->window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        graphics_free(graphics);
        return NULL;
    }

    /* Create a renderer. */
    graphics->renderer = SDL_CreateRenderer(graphics->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (graphics->renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
        graphics_free(graphics);
        return NULL;
    }
    SDL_SetRenderDrawColor(graphics->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    /* Initialize SDL_image. */
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        fprintf(stderr, "IMG_Init error: %s\n", IMG_GetError());
        graphics_free(graphics);
        return NULL;
    }

    return graphics;
}

int graphics_texture_load(graphics_t *graphics, int id, char *path)
{
    if (id >= TEXTURE_COUNT)
    {
        fprintf(stderr, "graphics_texture_load: id %d >= %d\n", id, TEXTURE_COUNT);
        return 0;
    }

    if (graphics->textures[id] != NULL)
    {
        fprintf(stderr, "graphics_texture_load: trying to load on top of another texture (id %d)\n", id);
        return 0;
    }

    SDL_Surface *loaded_surface = IMG_Load(path);
    if (loaded_surface == NULL)
    {
        fprintf(stderr, "graphics_texture_load: error loading image %s: %s\n", path, IMG_GetError());
        return 0;
    }

    SDL_Texture *new_texture = SDL_CreateTextureFromSurface(graphics->renderer, loaded_surface);
    SDL_FreeSurface(loaded_surface);
    if (new_texture == NULL)
    {
        fprintf(stderr, "graphics_texture_load: error creating texture: %s\n", SDL_GetError());
        return 0;
    }
    
    graphics->textures[id] = new_texture;
    return 1;
}

void graphics_free(graphics_t *graphics)
{
    /* Free all textures */
    for (int i = 0; i < TEXTURE_COUNT; i++)
        SDL_DestroyTexture(graphics->textures[i]);

    SDL_DestroyRenderer(graphics->renderer);
    SDL_DestroyWindow(graphics->window);

    free(graphics);
}
