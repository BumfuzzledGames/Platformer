cmake_minimum_required(VERSION 3.0.0)
project(Platformer VERSION 0.1.0)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(MAKE_DIRECTORY gen)

set(SRC
    src/draw.c
    src/ldtk.c
    src/main.c
    src/objects/tile_layer.c
    src/objects/menu_item.c
    src/object_pool.c
    src/texture.c
    src/util.c
    src/window.c
)
set_source_files_properties(
    ${SRC}
    PROPERTIES
    COMPILE_FLAGS
    "-Wall -Wextra -Wconversion -Wsign-conversion -Werror"
)

set(DATA
    background.png
    characters.png
    tilemap.png
    BasicHandwriting_0.png
    BasicHandwriting.fnt
    world.ldtk
)
set(DATA_SRC "")
foreach(DATA_FILE ${DATA})
    get_filename_component(DATA_FILE_EXT ${DATA_FILE} EXT)
    if(${DATA_FILE_EXT} STREQUAL ".fnt")
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/gen/${DATA_FILE}.c
            COMMAND ruby src/fnt2c.rb data/${DATA_FILE} gen/${DATA_FILE}.c
            MAIN_DEPENDENCY data/${DATA_FILE}
            DEPENDS src/fnt2c.rb
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
        list(APPEND DATA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/gen/${DATA_FILE}.c)
    elseif(${DATA_FILE_EXT} STREQUAL ".ldtk")
        add_custom_command(
            OUTPUT 
                ${CMAKE_CURRENT_SOURCE_DIR}/gen/ldtk_world_defs.h
                ${CMAKE_CURRENT_SOURCE_DIR}/gen/ldtk_world_enum.h 
                ${CMAKE_CURRENT_SOURCE_DIR}/gen/ldtk_world.c
            COMMAND ruby src/ldtk2c.rb data/${DATA_FILE} gen/ldtk_world_defs.h
            COMMAND ruby src/ldtk2c.rb data/${DATA_FILE} gen/ldtk_world_enum.h
            COMMAND ruby src/ldtk2c.rb data/${DATA_FILE} gen/ldtk_world.c
            MAIN_DEPENDENCY data/${DATA_FILE}
            DEPENDS
                ${CMAKE_CURRENT_SOURCE_DIR}/src/ldtk2c.rb
                ${CMAKE_CURRENT_SOURCE_DIR}/src/ldtk_world_defs.h.erb
                ${CMAKE_CURRENT_SOURCE_DIR}/src/ldtk_world_enum.h.erb
                ${CMAKE_CURRENT_SOURCE_DIR}/src/ldtk_world.c.erb
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
        list(APPEND DATA_SRC
            ${CMAKE_CURRENT_SOURCE_DIR}/gen/ldtk_world_defs.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gen/ldtk_world_enum.h
            ${CMAKE_CURRENT_SOURCE_DIR}/gen/ldtk_world.c)
    else()
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/gen/${DATA_FILE}.c
            COMMAND bin2c data/${DATA_FILE} gen/${DATA_FILE}.c
            MAIN_DEPENDENCY data/${DATA_FILE}
            DEPENDS bin2c
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )
        list(APPEND DATA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/gen/${DATA_FILE}.c)
    endif()
endforeach()

add_executable(bin2c src/bin2c.c)
add_executable(Platformer ${SRC} ${DATA_SRC} ${LDTK_SRC})
target_link_libraries(
    Platformer
    SDL2::SDL2main SDL2::SDL2
    SDL2_image
)