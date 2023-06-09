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

#ifndef PLATFORMER_TYPE_H
#define PLATFORMER_TYPE_H

#include "ldtk.h"
#include "SDL.h"

typedef struct Object Object;
typedef struct ObjectPool ObjectPool;
typedef struct Type Type;

#define UPDATE_ARGS float delta_time
#define UPDATE_ARG_NAMES delta_time
#define RENDER_ARGS SDL_Renderer *renderer
#define RENDER_ARG_NAMES renderer

extern const Type *entity_types[LDTK_NUM_ENTITY_TYPES];

struct Type
{
    const char *name;
    const Type *parent;
    Object *(*new_from_entity)(ObjectPool *object_pool, LDtkEntity *entity);
    void (*update)(void *object, UPDATE_ARGS);
    void (*render)(void *object, RENDER_ARGS);
};

#endif // PLATFORMER_TYPE_H
