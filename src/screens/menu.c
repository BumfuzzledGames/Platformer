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

static int
entity_callback
(
    LDtkEntity *entity
) {
    switch(entity->type)
    {
    case LDTK_ENTITY_MenuStart:
        start_item = (MenuItem**)
            &entity
                ->fields[LDTK_ENTITY_MenuStart_FIELD_MenuStart]
                .value
                .entity_refs[0]
                ->user;
        return 1;
    default:
        return 0;
    }
}

Screen *
menu_screen
(
    LDtkLevel *menu_level
)
{
    new_object_pool(&pool, POOL_SIZE);
    new_screen_objects(
        &pool,
        menu_level,
        NULL,
        entity_callback
    );
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