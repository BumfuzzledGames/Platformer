/***********************************************************
* A platformer game
* (C) 2023 Bumfuzzled Games <bumfuzzled.games@gmail.com>
* 
* This program is free software: you can redistribute it
* and/or modify it under the terms of the GNU General
* Public License as published by the Free Software
* Foundation, either version 3 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A
* PARTICULAR PURPOSE.  See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU General Public
* License along with this program.  If not, see
* <https://www.gnu.org/licenses/>.
**********************************************************/

#include "stb_image.h"
#include "texture.h"

#define XTEXTURE(T)                                         \
    SDL_Texture *T##_texture;                               \
    extern unsigned char T[];                               \
    extern size_t T##_size;
#include "resources.x"

static struct
{
    const char *name;
    SDL_Texture **texture;
    unsigned char *memory;
    size_t *size;
} textures[] =
{
#define XTEXTURE(T)                                         \
    {                                                       \
        .name = #T,                                         \
        .texture = &T##_texture,                            \
        .memory = T,                                        \
        .size = &T##_size,                                  \
    },
#include "resources.x"
};

static SDL_Texture *
load_texture
(
    SDL_Renderer *renderer,
    unsigned char *mem,
    size_t mem_size
) {
    void *data = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    int width, height, bytes_per_pixel;
    data = stbi_load_from_memory
    (
        mem, (int)mem_size,
        &width, &height, &bytes_per_pixel,
        0
    );
    if(data == NULL)
    {
        SDL_Log("%s Failed to load image: %s", __func__, stbi_failure_reason());
        goto cleanup;
    }

    surface = SDL_CreateRGBSurfaceFrom
    (
        data,
        width, height,
        bytes_per_pixel * 8,
        (width * bytes_per_pixel + 3) & ~3,
#       if SDL_BYTEORDER == SDL_LIL_ENDIAN
        0x000000FF,
        0x0000FF00,
        0x00FF0000,
        bytes_per_pixel == 4 ? 0xFF000000 : 0
#       else
        0xFF000000 >> (bytes_per_pixel == 4 ? 0 : 8),
        0x00FF0000 >> (bytes_per_pixel == 4 ? 0 : 8),
        0x0000FF00 >> (bytes_per_pixel == 4 ? 0 : 8),
        bytes_per_pixel == 4 ? 0x000000FF : 0
#       endif
    );
    if(surface == NULL)
    {
        SDL_Log("%s Failed to create surface: %s", __func__, SDL_GetError());
        goto cleanup;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL)
    {
        SDL_Log("%s Failed to create surface: %s", __func__, SDL_GetError());
        goto cleanup;
    }

cleanup:
    SDL_FreeSurface(surface);
    stbi_image_free(data);
    return texture;
}

int
load_textures
(
    SDL_Renderer *renderer
) {
    for(int t = 0; t < (int)SDL_arraysize(textures); t++)
    {
        *textures[t].texture = load_texture
        (
            renderer,
            textures[t].memory, *textures[t].size
        );
        if(*textures[t].texture == NULL)
        {
            return -1;
        }
    }
    return 0;
}
