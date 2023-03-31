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

#include "menu.h"
#include "../ldtk.h"
#include "../object.h"
#include "../object_pool.h"
#include "../objects/tile_layer.h"
#include "../objects/menu_item.h"
#include "../screen.h"
#include "../type.h"

#define POOL_SIZE (1024 * 1024)

static Screen screen;
static ObjectPool pool;
static MenuItem **start_item;

Screen *
menu_screen
(
    LDtkLevel *menu_level
)
{
    new_object_pool(&pool, POOL_SIZE);

    // Instantiate objects
    for
    (
        size_t layer_index = menu_level->num_layers - 1,
        counter = menu_level->num_layers;
        counter > 0;
        layer_index--, counter--
    ) {
        LDtkLayer *layer = menu_level->layers[layer_index];

        // If it has tiles, spawn a TileLayer object
        if(layer->num_tiles != 0)
        {
            new_tile_layer(&pool, layer);
        }

        // If it has entities, spawn entity objects
        for
        (
            size_t entity_index = 0;
            entity_index < layer->num_entities;
            entity_index++
        ) {
            LDtkEntity *entity = layer->entities[entity_index];
            switch(entity->type)
            {
            case LDTK_ENTITY_MenuStart:
                start_item = (MenuItem**)
                    &entity->
                    fields[LDTK_ENTITY_MenuStart_FIELD_MenuStart].
                    value.
                    entity_refs[0]->
                    user;
                break;
            default:
                {
                    const Type *entity_type = entity_to_object[entity->type];
                    if(entity_type && entity_type->new_from_entity)
                    {
                        Object *object = entity_type->new_from_entity
                        (
                            &pool,
                            entity
                        );
                        if(object == NULL)
                        {
                            SDL_Log
                            (
                                "%s Failed to create object from entity",
                                __func__
                            );
                        }
                        else
                        {
                            entity->user = object;
                        }
                    }
                }
            }
        }
    }
    return &screen;
}

static int
update
(
    SCREEN_UPDATE_ARGS
) {
    (void)delta_time;
    return 1;
}

static void
render
(
    SCREEN_RENDER_ARGS
) {
    for (
        Object *obj = (Object*)pool.memory;
        obj < (Object*)(pool.memory + pool.tail);
        obj = (Object*)((Uint8*)obj + obj->size)
    ) {
        if(obj->type->render) obj->type->render(obj, renderer);
    }
}

static Screen screen =
{
    .update = update,
    .render = render,
};