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

#ifndef PLATFORMER_OBJECT_POOL_H
#define PLATFORMER_OBJECT_POOL_H

#include "type.h"
#include "SDL.h"

typedef struct Object Object;
typedef struct ObjectPool ObjectPool;
typedef struct LDtkLevel LDtkLevel;
typedef struct LDtkLayer LDtkLayer;
typedef struct LDtkEntity LDtkEntity;

// How do I know that value of this for various platforms?
#define OBJECT_POOL_ALIGN 16

#define FOREACH_OBJECT_IN_POOL(POOL, OBJ)                   \
    for                                                     \
    (                                                       \
        Object *OBJ = (Object*)POOL->memory;                \
        OBJ < (Object*)(POOL->memory + POOL->tail);         \
        OBJ = (Object*)((Uint8*)OBJ + OBJ->size)            \
    )

struct ObjectPool
{
    Uint8 *memory;
    size_t size;
    size_t tail;
};

int
new_object_pool
(
    ObjectPool *this,
    size_t size
);

Object *
new_object
(
    ObjectPool *this,
    size_t object_size,
    size_t size_override,
    size_t *out_size
);

void
new_objects_from_level
(
    ObjectPool *this,
    LDtkLevel *level,
    int (*layer_callback)(LDtkLayer *layer),
    int (*entity_callback)(LDtkEntity *entity)
);

void
update_objects
(
    ObjectPool *this,
    UPDATE_ARGS
);

void render_objects
(
    ObjectPool *this,
    RENDER_ARGS
);

#endif // PLATFORMER_OBJECT_POOL_H
