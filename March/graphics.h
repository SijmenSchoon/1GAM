#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define TEXTURE_COUNT 1024 

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *textures[TEXTURE_COUNT];
} graphics_t;

graphics_t *graphics_init(int width, int height);
int graphics_texture_load(graphics_t *graphics, int id, char *path);
void graphics_free(graphics_t *graphics);

#endif
