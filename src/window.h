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

/** @defgroup WINDOW Window
 * @brief Provides functions for creating and manipulating
 * windows.
 * 
 * @{
*/

#ifndef PLATFORMER_WINDOW_H
#define PLATFORMER_WINDOW_H

#include "SDL.h"

/** Create a window
 * 
 * @returns 0 on success
*/
int
create_window
(
    const char *title,              /**< Window title */
    int logical_width,              /**< Logical width */
    int logical_height,             /**< Logical height */
    SDL_bool is_integer_scale,      /**< Lock to integer scales? */
    Uint32 flags,                   /**< Additional flags */
    SDL_Window **out_window,        /**< Output window pointer */
    SDL_Renderer **out_renderer     /**< Output renderer pointer */
);

/** Make window more embiggened
 *
 * Embiggen a window to the largest size givent he usable
 * area of the current display. Takes taskbars and docks
 * into account, as well as window decorations. Centers
 * content of window in available space.
*/
void
embiggen_window
(
    SDL_Window *window,             /**< The window to embiggen */
    SDL_Renderer *SDL_Renderer      /**< The window's renderer */
);

#endif // PLATFORMER_WINDOW_H

/** @} */
