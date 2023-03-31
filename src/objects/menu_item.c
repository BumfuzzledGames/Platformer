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

#include "../draw.h"
#include "../ldtk.h"
#include "../object_pool.h"
#include "../type.h"
#include "menu_item.h"

extern SDL_Texture *data_BasicHandwriting_0_png;
extern Font data_BasicHandwriting_fnt;

static int
new_from_entity
(
    ObjectPool *object_pool,
    LDtkEntity *entity
) {
    MenuItem *this = (MenuItem*)new_object(object_pool, sizeof(MenuItem));
    *this = (MenuItem)
    {
        .type = &MenuItem_type,
        .size = sizeof(MenuItem),
        .enabled = SDL_TRUE,
        .font = &data_BasicHandwriting_fnt,
        .area =
        {
            .x = entity->px.x,
            .y = entity->px.y,
            .w = entity->width,
            .h = entity->height,
        },
        .text = entity->fields[LDTK_ENTITY_MenuItem_FIELD_Text].value.strings[0],
    };
    return 0;
}

static void
render
(
    void *this_
    RENDER_ARGS
) {
    MenuItem *this = this_;
    draw_text
    (
        renderer,
        this->font,
        this->text,
        &this->area,
        DRAW_TEXT_HCENTER | DRAW_TEXT_VCENTER
    );
    SDL_RenderDrawRect(renderer, &this->area);
}

const Type MenuItem_type =
{
    .name = "MenuItem",
    .new_from_entity = new_from_entity,
    .render = render,
};
