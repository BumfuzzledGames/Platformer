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

#include "ldtk.h"
#include "object_pool.h"
#include "object.h"
#include "objects/tile_layer.h"
#include "screen.h"

void
new_screen_objects
(
    ObjectPool *object_pool,
    LDtkLevel *level,
    int (*layer_callback)(LDtkLayer *layer),
    int (*entity_callback)(LDtkEntity *entity)
) {
    for
    (
        size_t layer_index = level->num_layers - 1, counter = 0;
        counter < level->num_layers;
        layer_index--, counter++
    ) {
        LDtkLayer *layer = level->layers[layer_index];

        // Skip this layer if the callback handled it
        if(layer_callback && layer_callback(layer)) continue;

        // If this layer has tiles, spawn a TileLayer object
        if(layer->num_tiles != 0)
        {
            new_tile_layer(object_pool, layer);
        }

        // Spawn entity objects
        for
        (
            size_t entity_index = 0;
            entity_index < layer->num_entities;
            entity_index++
        ) {
            LDtkEntity *entity = layer->entities[entity_index];

            // Skip this entity if the callback handled it
            if(entity_callback && entity_callback(entity)) continue;
            spawn_object_from_entity(object_pool, entity);
        }
    }
}