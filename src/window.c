/***********************************************************
* Bumfario: A platformer game
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

#include "window.h"

int
create_window
(
    const char *title,
    int logical_width,
    int logical_height,
    SDL_bool is_integer_scale,
    Uint32 flags,
    SDL_Window **out_window,
    SDL_Renderer **out_renderer
) {
    // Create the window
    *out_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        logical_width, logical_height,
        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | flags);
    if(*out_window == NULL)
    {
        SDL_Log("%s SDL_CreatWindow failed: %s", __func__, SDL_GetError());
        return -1;
    }

    // Create the renderer
    *out_renderer = SDL_CreateRenderer(
        *out_window,
        -1,
        SDL_RENDERER_PRESENTVSYNC);
    if(*out_renderer == NULL)
    {
        SDL_Log("%s SDL_CreateRenderer failed: %s", __func__, SDL_GetError());
        return -1;
    }

    // Set logical size and integer scale
    SDL_RenderSetLogicalSize(*out_renderer, logical_width, logical_height);
    SDL_RenderSetIntegerScale(*out_renderer, is_integer_scale);

    return 0;
}

void
embiggen_window
(
    SDL_Window *window,
    SDL_Renderer *renderer
) {
    // Get border sizes of a window, this includes small
    // borders around the edge, but also the title bar
    int top;
    int left;
    int bottom;
    int right;
    SDL_GetWindowBordersSize(
        window,
        &top, &left, &bottom, &right);
    
    // Get usable bounds of the display, which is the size
    // of the display minus things like the dock or taskbar
    SDL_Rect usable;
    SDL_GetDisplayUsableBounds(
        SDL_GetWindowDisplayIndex(window),
        &usable);
    
    // Subtract borders from the usable bounds
    usable.x += left;
    usable.w -= left + right;
    usable.y += top;
    usable.w -= top + bottom;

    int logical_width;
    int logical_height;
    SDL_RenderGetLogicalSize(renderer, &logical_width, &logical_height);

    // Get the largest integer multiple we can resize to
    int zoom = (int)SDL_min(
        usable.w / logical_width,
        usable.h / logical_height);
    
    // Resize
    SDL_SetWindowSize(
        window,
        logical_width * zoom,
        logical_height * zoom);

    // Center the window. We can't use SDL_WINDOWPOS_CENTERED
    // because that centers the window on the display, not
    // the usable display area. Also, we want to center the
    // actual window contens, not the top left of the window,
    // which includes the borders
    SDL_SetWindowPosition(
        window,
        usable.x + (usable.w - logical_width * zoom) / 2 - left,
        usable.y + (usable.h - logical_height * zoom) / 2 - top); 
}