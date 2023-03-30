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
#include "SDL.h"
#include "font_metrics.h"

typedef enum DrawTextOptions
{
    DRAW_TEXT_HCENTER = 0b0001,
    DRAW_TEXT_VCENTER = 0b0010,
} DrawTextOptions;

void
draw_text
(
    SDL_Renderer *renderer,
    SDL_Texture *texture,
    const FontMetrics *font_metrics,
    const char *text,
    const SDL_Rect *dst,
    DrawTextOptions options
);

#endif // PLATFORMER_DRAW_H