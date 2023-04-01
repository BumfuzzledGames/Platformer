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
#include "../keyboard.h"
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
static MenuItem **current_item;

static void
go_to_menu_item
(
    MenuItem **next_item
) {
    (*current_item)->selected = SDL_FALSE;
    (*current_item)->Text.color = (SDL_Color){ 255, 255, 255, 255 };
    current_item = next_item;
    (*current_item)->selected = SDL_TRUE;
    (*current_item)->Text.color = (SDL_Color){ 0, 255, 255, 255 };
}


static int
entity_callback
(
    LDtkEntity *entity
) {
    switch(entity->type)
    {
    case LDTK_ENTITY_MenuStart:
        current_item = (MenuItem**)
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
    current_item = NULL;
    new_object_pool(&pool, POOL_SIZE);
    new_objects_from_level(
        &pool,
        menu_level,
        NULL,
        entity_callback
    );

    if(current_item == NULL)
    {
        SDL_Log("%s Menu has no start item!", __func__);
        return NULL;
    }
    go_to_menu_item(current_item);
    return &screen;
}

static int
update
(
    UPDATE_ARGS
) {
    update_objects(&pool, UPDATE_ARG_NAMES);

    if(was_key_just_pressed(SDLK_UP) && (*current_item)->up)
    {
        go_to_menu_item((*current_item)->up);
    }
    if(was_key_just_pressed(SDLK_DOWN) && (*current_item)->down)
    {
        go_to_menu_item((*current_item)->down);
    }
    if(was_key_just_pressed(SDLK_LEFT) && (*current_item)->left)
    {
        go_to_menu_item((*current_item)->left);
    }
    if(was_key_just_pressed(SDLK_RIGHT) && (*current_item)->right)
    {
        go_to_menu_item((*current_item)->right);
    }
    return 1;
}

static void
render
(
    RENDER_ARGS
) {
    render_objects(&pool, RENDER_ARG_NAMES);
}

static Screen screen =
{
    .update = update,
    .render = render,
};