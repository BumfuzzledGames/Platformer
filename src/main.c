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

#include "draw.h"
#include "font.h"
#include "ldtk.h"
#include "object_pool.h"
#include "object.h"
#include "objects/menu_item.h"
#include "objects/tile_layer.h"
#include "SDL_image.h"
#include "SDL.h"
#include "texture.h"
#include "type.h"
#include "window.h"

#define GAME_WIDTH (1920/4)
#define GAME_HEIGHT (1080/4)

extern SDL_Texture *data_BasicHandwriting_0_png_texture;
extern Font data_BasicHandwriting_fnt;

int
main
(
    [[maybe_unused]] int argc,
    [[maybe_unused]] char *argv[]
) {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("%s Failed to initialize SDL: %s", __func__, SDL_GetError());
        return -1;
    }

    // Initialize IMG
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_Log("%s Failed to initialize SDL_image: %s", __func__, IMG_GetError());
        return -1;
    }

    // Create the window and embiggen it
    SDL_Window *window;
    SDL_Renderer *renderer;
    if(create_window(
        "Platformer",
        GAME_WIDTH, GAME_HEIGHT,
        SDL_TRUE,
        0,
        &window, &renderer
    )) {
        SDL_Log("%s Failed to create window", __func__);
        return -1;
    }
    embiggen_window(window, renderer);

    // Load textures
    if(load_textures(renderer))
    {
        SDL_Log("%s Failed to load textures\n", __func__);
        return -1;
    }

    LDtkLevel *level = ldtk_levels[LDTK_LEVEL_Menu_0];

    ObjectPool pool;
    new_object_pool(&pool, 1024);

    for(int lay = (int)level->num_layers - 1; lay >= 0; lay--)
    {
        if(level->layers[lay]->num_tiles != 0)
        {
            new_tile_layer
            (
                &pool,
                level->layers[lay]
            );
        }
        if(level->layers[lay]->num_entities != 0)
        {
            for(size_t e = 0; e < level->layers[lay]->num_entities; e++)
            {
                const Type *entity_type = entity_to_object[level->layers[lay]->entities[e]->type];
                if(entity_type && entity_type->new_from_entity)
                {
                    if(entity_type->new_from_entity(&pool, level->layers[lay]->entities[e]))
                    {
                        SDL_Log("Failed to create entity!");
                    }
                }
            }
        }
    }

    while(1)
    {
        for(SDL_Event e; SDL_PollEvent(&e);) if(e.type == SDL_QUIT) goto done;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (
            Object *obj = (Object*)pool.memory;
            obj < (Object*)(pool.memory + pool.tail);
            obj = (Object*)((Uint8*)obj + obj->size)
        ) {
            if(obj->type->render) obj->type->render(obj, renderer);
        }
        SDL_RenderPresent(renderer);
    }

done:
    SDL_Quit();
    return 0;
}
