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

#ifndef PLATFORMER_OBJECTS_MENU_ITEM_H
#define PLATFORMER_OBJECTS_MENU_ITEM_H

#include "../object_header.h"
#include "SDL.h"

typedef struct FontMetrics FontMetrics;
typedef struct LDtkEntity LDtkEntity;
typedef struct ObjectPool ObjectPool;

extern const Type MenuItem_type;

typedef struct MenuItem MenuItem;
struct MenuItem
{
    OBJECT_HEADER
    SDL_Texture *texture;
    const FontMetrics *font_metrics;
    SDL_Rect area;
    const char *text;
};

int
new_menu_item
(
    ObjectPool *object_pool,
    LDtkEntity *entity,
    SDL_Texture *texture,
    const FontMetrics *font_metrics
);

#endif // PLATFORMER_OBJECTS_MENU_IT_H