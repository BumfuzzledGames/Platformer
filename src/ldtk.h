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

#ifndef LDTK_H
#define LDTK_H
#include "ldtk_forward.h"
#include "../gen/ldtk_world_enum.h"
#include "SDL.h"

typedef enum
{
    LDTK_FIELD_TYPE_ArrayInt,
    LDTK_FIELD_TYPE_Int,
    LDTK_FIELD_TYPE_ArrayFloat,
    LDTK_FIELD_TYPE_Float,
    LDTK_FIELD_TYPE_ArrayBool,
    LDTK_FIELD_TYPE_Bool,
    LDTK_FIELD_TYPE_ArrayString,
    LDTK_FIELD_TYPE_String,
    LDTK_FIELD_TYPE_ArrayColor,
    LDTK_FIELD_TYPE_Color,
    LDTK_FIELD_TYPE_ArrayEnum,
    LDTK_FIELD_TYPE_Enum,
    LDTK_FIELD_TYPE_ArrayTile,
    LDTK_FIELD_TYPE_Tile,
    LDTK_FIELD_TYPE_ArrayEntityRef,
    LDTK_FIELD_TYPE_EntityRef,
    LDTK_FIELD_TYPE_ArrayPoint,
    LDTK_FIELD_TYPE_Point,
    LDTK_ENUM_TYPES
} LDtkFieldType;

typedef enum
{
    LDTK_LAYER_TYPE_IntGrid,
    LDTK_LAYER_TYPE_Entities,
    LDTK_LAYER_TYPE_Tiles,
    LDTK_LAYER_TYPE_AutoLayer,
} LDtkLayerType;

typedef enum
{
    LDTK_TILE_FLIP_NONE,
    LDTK_TILE_FLIP_X = 1,
    LDTK_TILE_FLIP_Y = 2,
} LDtkTileFlip;

struct LDtkLevel
{
    const char *identifier;
    SDL_Point world_position;
    SDL_Point dimensions;
    SDL_Color background_color;
    size_t num_fields;
    LDtkField *fields;
    size_t num_layers;
    LDtkLayer **layers;
};

struct LDtkLayer
{
    const char *identifier;
    LDtkLevel *level;
    LDtkLayerType type;
    SDL_Point size;
    int grid_size;
    float opacity;
    SDL_Point offset;
    // LAYER_TYPE_ENTITIES
    int num_entities;
    LDtkEntity **entities;

    // LAYER_TYPE_TILES and LAYER_TYPE_AutoLayer
    LDtkTileset *tileset;
    int num_tiles;
    LDtkTile *tiles;

    // LAYER_TYPE_INTEGER_GRID
    int *grid;
};

struct LDtkTile
{
    SDL_Rect src;
    SDL_Rect dst;
    int flip;
};

struct LDtkFieldTileValue
{
    LDtkTileset *tileset;
    SDL_Rect src;
};

struct LDtkField
{
    const char *identifier;
    LDtkFieldType type;
    struct
    {
        size_t length;
        union
        {
            int *ints;
            float *floats;
            SDL_bool *bools;
            const char **strings;
            SDL_Color *colors;
            LDtkTile *tiles;
            LDtkEntity **entity_refs;
            SDL_Point *points;
            void *ptr;
        };
    } value;
};

struct LDtkEntity
{
    LDtkEntityType type;
    LDtkLayer *layer;
    SDL_Point grid;
    SDL_Point pivot;
    // tags?
    // tile?
    int width;
    int height;
    SDL_Point px;
    int num_fields;
    LDtkField *fields;

    void *user;
};

struct LDtkTileset
{
    const char *identifier;
    SDL_Texture **texture;
    int uid;
    SDL_Point tile_size;
    SDL_Point texture_size;
    int padding;
    int spacing;
};

#include "../gen/ldtk_world_defs.h"

#endif // LDTK_H