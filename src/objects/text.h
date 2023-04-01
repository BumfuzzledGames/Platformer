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

#ifndef PLATFORMER_OBJECTS_TEXT_H
#define PLATFORMER_OBJECTS_TEXT_H

#include "../object.h"
#include "../font.h"
#include "../draw.h"
#include "SDL.h"

typedef struct Font Font;

extern const Type Text_type;

typedef struct Text Text;
struct Text
{
    Object Object;
    const Font *font;
    SDL_Color color;
    SDL_Rect area;
    const char *text;
    DrawTextOptions draw_options;
};

Text *
new_text
(
    ObjectPool *object_pool,
    size_t size_override,
    const Font *font,
    const SDL_Color *color,
    const SDL_Rect *area,
    const char *text,
    DrawTextOptions draw_options
);

void
render_text_object
(
    void *object,
    RENDER_ARGS
);

#endif // PLATFORMER_OBJECTS_TEXT_H