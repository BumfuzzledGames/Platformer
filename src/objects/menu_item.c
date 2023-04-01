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

static Object *
new_from_entity
(
    ObjectPool *object_pool,
    LDtkEntity *entity
) {
    // Create the Text object
    MenuItem *this = (MenuItem*)new_text
    (
        object_pool,
        sizeof(MenuItem),
        &data_BasicHandwriting_fnt,
        &(SDL_Color){ 255, 255, 255, 255 },
        &(SDL_Rect)
        {
            .x = entity->px.x,
            .y = entity->px.y,
            .w = entity->width,
            .h = entity->height,
        },
        entity->fields[LDTK_ENTITY_MenuItem_FIELD_Text].value.strings[0],
        DRAW_TEXT_CENTER
    );
    if(this == NULL)
    {
        SDL_Log("%s Failed to create MenuItem", __func__);
        return NULL;
    }

    // Make it a MenuItem object
    this->Text.Object.type = &MenuItem_type;
    this->selected = SDL_FALSE;
    if(entity->fields[LDTK_ENTITY_MenuItem_FIELD_Up].value.entity_refs[0])
    {
        this->up = (MenuItem**)&entity->fields[LDTK_ENTITY_MenuItem_FIELD_Up].value.entity_refs[0]->user;
    }
    if(entity->fields[LDTK_ENTITY_MenuItem_FIELD_Down].value.entity_refs[0])
    {
        this->down = (MenuItem**)&entity->fields[LDTK_ENTITY_MenuItem_FIELD_Down].value.entity_refs[0]->user;
    }
    if(entity->fields[LDTK_ENTITY_MenuItem_FIELD_Left].value.entity_refs[0])
    {
        this->left = (MenuItem**)&entity->fields[LDTK_ENTITY_MenuItem_FIELD_Left].value.entity_refs[0]->user;
    }
    if(entity->fields[LDTK_ENTITY_MenuItem_FIELD_Right].value.entity_refs[0])
    {
        this->right = (MenuItem**)&entity->fields[LDTK_ENTITY_MenuItem_FIELD_Right].value.entity_refs[0]->user;
    }

    return &this->Text.Object;
}

const Type MenuItem_type =
{
    .name = "MenuItem",
    .parent = &Text_type,
    .new_from_entity = new_from_entity,
};
