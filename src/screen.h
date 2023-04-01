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

typedef struct LDtkEntity LDtkEntity;
typedef struct LDtkLayer LDtkLayer;
typedef struct LDtkLevel LDtkLevel;
typedef struct ObjectPool ObjectPool;
typedef struct Screen Screen;
typedef struct SDL_Renderer SDL_Renderer;

#define SCREEN_UPDATE_ARGS float delta_time
#define SCREEN_UPDATE_ARG_NAMES delta_time

#define SCREEN_RENDER_ARGS SDL_Renderer *renderer
#define SCREEN_RENDER_ARG_NAMES renderer

#define SCREEN_LEAVE_ARGS
#define SCREEN_LEAVE_ARG_NAMES

struct Screen
{
    float time;
    int (*update)(SCREEN_UPDATE_ARGS);
    void (*render)(SCREEN_RENDER_ARGS);
    void (*leave)(SCREEN_LEAVE_ARGS);
};

void
new_screen_objects
(
    ObjectPool *object_pool,
    LDtkLevel *level,
    int (*layer_callback)(LDtkLayer *layer),
    int (*entity_callback)(LDtkEntity *entity)
);

#endif // PLATFORMER_SCREEN_H