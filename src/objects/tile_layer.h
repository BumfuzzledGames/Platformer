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
#ifndef PLATFORMER_OBJECTS_TILE_LAYER_H
#define PLATFORMER_OBJECTS_TILE_LAYER_H
#include "../object_header.h"
#include "SDL.h"

typedef struct ObjectPool ObjectPool;
typedef struct TileLayer TileLayer;
typedef struct LDtkLayer LDtkLayer;

extern const Type TileLayer_type;

struct TileLayer
{
    OBJECT_HEADER
    LDtkLayer *ldtk_layer;
};

int
new_tile_layer
(
    ObjectPool *object_pool,
    LDtkLayer *ldtk_layer
);

#endif // PLATFORMER_OBJECTS_TILE_LAYER_H