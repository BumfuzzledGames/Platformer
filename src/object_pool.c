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

#include "object_pool.h"

int
new_object_pool
(
    ObjectPool *this,
    size_t size
) {
    *this = (ObjectPool)
    {
        .memory = SDL_calloc(1, size),
        .size = size,
        .tail = 0
    };
    if(this->memory != NULL)
    {
        return 0;
    }
    return 1;
}

Object *
new_object
(
    ObjectPool *this,
    size_t object_size
) {
    if(this->tail + object_size > this->size)
    {
        this->memory = SDL_realloc(this->memory, this->size * 2);
        this->size *= 2;
    }
    this->tail += object_size;
    return (Object*)(this->memory + this->tail - object_size);
}