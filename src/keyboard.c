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

#include "keyboard.h"

Uint8 current[SDL_NUM_SCANCODES];
Uint8 previous[SDL_NUM_SCANCODES];

void
init_keyboard
(
    void
) {
    SDL_memset(current, 0, sizeof(current));
    SDL_memset(previous, 0, sizeof(previous));
}

void
update_keyboard
(
    void
) {
    int num_keys;
    const Uint8 *keyboard = SDL_GetKeyboardState(&num_keys);
    SDL_memcpy(previous, current, sizeof(previous));
    SDL_memcpy(current, keyboard, (size_t)num_keys);
}

SDL_bool
is_key_pressed
(
    SDL_KeyCode key
) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
    return !!current[scancode];
}

SDL_bool
was_key_just_pressed
(
    SDL_KeyCode key
) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
    return !!current[scancode] && !previous[scancode];
}

SDL_bool
was_key_just_released
(
    SDL_KeyCode key
) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
    return !current[scancode] && !previous[scancode];
}
