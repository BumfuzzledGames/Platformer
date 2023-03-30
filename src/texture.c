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
#include "SDL_image.h"
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

int
load_textures
(
    SDL_Renderer *renderer
) {
    for(int t = 0; t < (int)SDL_arraysize(textures); t++)
    {
        SDL_Log("Loading %s...", textures[t].name);

        SDL_RWops *rw = SDL_RWFromConstMem
        (
            textures[t].memory,
            (int)*textures[t].size
        );

        *textures[t].texture = IMG_LoadTexture_RW
        (
            renderer,
            rw,
            1
        );
        if(*textures[t].texture == NULL)
        {
            SDL_Log
            (
                "%s Failed to load texture '%s' %s",
                __func__,
                textures[t].name,
                IMG_GetError()
            );
            return -1;
        }
    }
    return 0;
}