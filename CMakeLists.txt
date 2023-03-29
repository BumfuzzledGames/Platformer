cmake_minimum_required(VERSION 3.0.0)
project(Platformer VERSION 0.1.0)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(LDTK_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/ldtk_world_enum.h
    ${CMAKE_CURRENT_BINARY_DIR}/ldtk_world_defs.h
    ${CMAKE_CURRENT_BINARY_DIR}/ldtk_world.c
)
set(SRC
    src/ldtk.c
    src/main.c
    src/texture.c
    src/util.c
    src/window.c
    ${LDTK_SRC}
)
set_source_files_properties(
    ${SRC}
    PROPERTIES
    COMPILE_FLAGS
    "-Wall -Wextra -Wconversion -Wsign-conversion -Werror"
)
set_source_files_properties(
    ${SRC}
    PROPERTIES
    COMPILE_FLAGS
    "-I${CMAKE_CURRENT_BINARY_DIR} -I${CMAKE_CURRENT_SOURCE_DIR}/src"
)
foreach(F ${LDTK_SRC})
    add_custom_command(
        OUTPUT ${F}
        COMMAND ruby src/ldtk2c.rb data/world.ldtk ${F}
        MAIN_DEPENDENCY data/world.ldtk
        DEPENDS src/ldtk2c.rb src/ldtk_world_defs.h.erb src/ldtk_world_enum.h.erb src/ldtk_world.c.erb
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endforeach()

set(DATA
    data/background.png
    data/characters.png
    data/tilemap.png
    data/world.ldtk
)
set(DATA_OBJ "")
foreach(DATA_FILE ${DATA})
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILE}.c"
        COMMAND bin2c ${DATA_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILE}.c"
        MAIN_DEPENDENCY ${DATA_FILE}
        DEPENDS bin2c
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    list(APPEND DATA_SRC "${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILE}.c")
endforeach()

add_executable(bin2c src/bin2c.c)
add_executable(Platformer ${SRC} ${DATA_SRC})
target_link_libraries(
    Platformer
    SDL2::SDL2main SDL2::SDL2
    SDL2_image
)