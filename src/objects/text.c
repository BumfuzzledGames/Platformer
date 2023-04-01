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

#include "text.h"
#include "../draw.h"
#include "../type.h"
#include "../object_pool.h"

Text *
new_text
(
    ObjectPool *object_pool,
    size_t size_override,
    const Font *font,
    const SDL_Color *color,
    const SDL_Rect *area,
    const char *text,
    DrawTextOptions draw_options
) {
    size_t this_size;
    Text *this = (Text*)new_object
    (
        object_pool,
        sizeof(Text),
        size_override,
        &this_size
    );
    if(this == NULL)
    {
        SDL_Log("%s Failed to allocate object", __func__);
        return NULL;
    }

    *this = (Text)
    {
        .Object =
        {
            .type = &Text_type,
            .size = this_size,
            .enabled = SDL_TRUE,
        },
        .font = font,
        .color = *color,
        .area = *area,
        .text = text,
        .draw_options = draw_options,
    };
    return this;
}

static void
render
(
    void *this_,
    RENDER_ARGS
) {
    Text *this = this_;
    SDL_SetTextureColorMod
    (
        *this->font->texture,
        this->color.r, this->color.g, this->color.b
    );
    SDL_SetTextureAlphaMod
    (
        *this->font->texture,
        this->color.a
    );

    draw_text
    (
        renderer,
        this->font,
        this->text,
        &this->area,
        DRAW_TEXT_CENTER
    );
}

const Type Text_type =
{
    .name = "Text",
    .render = render,
};