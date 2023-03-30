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

#include "draw.h"

void
draw_text
(
    SDL_Renderer *renderer,
    const Font *font,
    const char *text,
    const SDL_Rect *dst,
    DrawTextOptions options
) {
    SDL_Point pos = { dst->x, dst->y };
    if(options & DRAW_TEXT_HCENTER)
    {
        int text_width = 0;
        for(const char *c = text; *c; c++)
        {
            if(font->chars[(unsigned)*c].present)
            {
                text_width += font->chars[(unsigned)*c].src.w;
            }
            else
            {
                text_width += font->chars[(unsigned)'?'].src.w;
            }
        }

        pos.x = dst->x + (dst->w - text_width) / 2;
    }
    if(options & DRAW_TEXT_VCENTER)
    {
        pos.y = dst->y + (dst->h - font->line_height) / 2;
    }

    for(const char *c = text; *c; c++)
    {
        if(*c == ' ')
        {
            pos.x += font->chars[(unsigned)'m'].src.w / 2;
        }
        else
        {
            char displayed_char = *c;
            if(!font->chars[(unsigned)*c].present)
            {
                displayed_char = '?';    
            }
            #define C font->chars[(unsigned)displayed_char]
            (void)renderer;
            SDL_RenderCopy(
                renderer,
                *font->texture,
                &C.src,
                &(SDL_Rect)
                {
                    pos.x + C.offset.x, pos.y + C.offset.y,
                    C.src.w, C.src.h
                }
            );
            pos.x += C.advance;
            #undef C
        }
    }
}