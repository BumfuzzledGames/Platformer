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

#ifndef PLATFORMER_DRAW_H
#define PLATFORMER_DRAW_H

#include "font.h"
#include "SDL.h"

typedef enum DrawTextOptions
{
    DRAW_TEXT_HCENTER = 0x01,
    DRAW_TEXT_VCENTER = 0x02,
    DRAW_TEXT_CENTER = 0x03,
} DrawTextOptions;

void
draw_text
(
    SDL_Renderer *renderer,
    const Font *font_metrics,
    const char *text,
    const SDL_Rect *dst,
    DrawTextOptions options
);

#endif // PLATFORMER_DRAW_H
