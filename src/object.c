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

#include "object.h"
#include "object_pool.h"
#include "ldtk.h"
#include "type.h"

Object *
spawn_object_from_entity
(
    ObjectPool *object_pool,
    LDtkEntity *entity
) {
    const Type *type = entity_types[entity->type];
    if(type == NULL || type->new_from_entity == NULL) return SDL_FALSE;

    Object *object = type->new_from_entity(object_pool, entity);
    if(object == NULL)
    {
        SDL_Log("%s Failed to create object from entity", __func__);
    }
    return object;
}
