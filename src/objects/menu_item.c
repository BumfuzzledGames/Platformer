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

#include "menu_item.h"
#include "../ldtk.h"
#include "../object_pool.h"
#include "../type.h"
#include "../draw.h"

int
new_menu_item
(
    ObjectPool *object_pool,
    LDtkEntity *entity,
    SDL_Texture *texture,
    const FontMetrics *font_metrics
) {
    MenuItem *this = (MenuItem*)new_object(object_pool, sizeof(MenuItem));
    (*this) = (MenuItem)
    {
        .type = &MenuItem_type,
        .size = sizeof(MenuItem),
        .enabled = SDL_TRUE,
        .texture = texture,
        .font_metrics = font_metrics,
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
        this->texture,
        this->font_metrics,
        this->text,
        &this->area,
        DRAW_TEXT_HCENTER | DRAW_TEXT_VCENTER
    );
    SDL_RenderDrawRect(renderer, &this->area);
}

const Type MenuItem_type =
{
    .name = "MenuItem",
    .render = render,
};