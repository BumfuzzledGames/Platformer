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

#ifndef PLATFORMER_SCREEN_H
#define PLATFORMER_SCREEN_H

#include "type.h"

typedef struct LDtkEntity LDtkEntity;
typedef struct LDtkLayer LDtkLayer;
typedef struct LDtkLevel LDtkLevel;
typedef struct ObjectPool ObjectPool;
typedef struct Screen Screen;
typedef struct SDL_Renderer SDL_Renderer;

struct Screen
{
    float time;
    int (*update)(UPDATE_ARGS);
    void (*render)(RENDER_ARGS);
    void (*leave)();
};

#endif // PLATFORMER_SCREEN_H