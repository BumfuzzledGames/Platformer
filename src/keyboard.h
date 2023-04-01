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

#ifndef PLATFORMER_KEYBOARD_H
#define PLATFORMER_KEYBOARD_H

#include "SDL.h"

void
init_keyboard
(
    void
);

void
update_keyboard
(
    void
);

SDL_bool
is_key_pressed
(
    SDL_KeyCode key
);

SDL_bool
was_key_just_pressed
(
    SDL_KeyCode key
);

SDL_bool
was_key_just_released
(
    SDL_KeyCode key
);

#endif // PLATFORMER_KEYBOARD_H