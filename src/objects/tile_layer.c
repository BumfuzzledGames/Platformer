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

#include "../type.h"
#include "../ldtk.h"
#include "tile_layer.h"
#include "../object_pool.h"

int
new_tile_layer
(
    ObjectPool *object_pool,
    LDtkLayer *ldtk_layer
) {
    TileLayer *this = (TileLayer*)new_object(object_pool, sizeof(TileLayer));
    *this = (TileLayer)
    {
        .type = &TileLayer_type,
        .size = sizeof(TileLayer),
        .enabled = SDL_TRUE,
        .ldtk_layer = ldtk_layer,
    };
    return 0;
}

static void
render
(
    void *this_
    RENDER_ARGS
) {
    TileLayer *this = this_;
    for(int t = 0; t < this->ldtk_layer->num_tiles; t++)
    {
        SDL_RenderCopy
        (
            renderer,
            *this->ldtk_layer->tileset->texture,
            &this->ldtk_layer->tiles[t].src,
            &this->ldtk_layer->tiles[t].dst
        );
    }
}

const Type TileLayer_type =
{
    .name = "TileLayer",
    .render = render,
};