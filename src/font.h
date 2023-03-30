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

#ifndef PLATFORMER_FONT_H
#define PLATFORMER_FONT_H
#include "SDL.h"

typedef struct Font Font;

struct Font
{
    // info
    const char *face;
    int size;
    SDL_bool bold;
    SDL_bool italic;
    const char *charset;
    SDL_bool unicode;
    int stretch_h;
    SDL_bool smooth;
    SDL_bool aa;
    struct
    {
        int up;
        int right;
        int down;
        int left;
    } padding;
    struct
    {
        int horizontal;
        int vertical;
    } spacing;
    int outline;
    
    // base
    int line_height;
    int base;
    int scale_w;
    int scale_h;
    int pages;
    int packed;
    int alpha_chnl;
    int red_chnl;
    int green_chnl;
    int blue_chnl;

    // page
    // Note: only single-page fonts are supported
    SDL_Texture **texture;

    struct
    {
        SDL_bool present;
        SDL_Rect src;
        SDL_Point offset;
        int advance;
    } chars[256];
};

#endif // PLATFORMER_FONT_H