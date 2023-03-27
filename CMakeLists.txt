cmake_minimum_required(VERSION 3.0.0)
project(Platformer VERSION 0.1.0)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(SRC
    src/main.c
)
set_source_files_properties(
    "${SRC}"
    PROPERTIES
    COMPILE_FLAGS
    "-Wall -Wextra -Wconversion -Wsign-conversion -Werror"
)

set(THIRD_PARTY_SRC
#    src/cJSON.c
)

set(DATA
)
set(DATA_OBJ "")
foreach(DATA_FILE ${DATA})
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILE}.o"
        COMMAND ld -r -b binary -o "${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILE}.o" "${DATA_FILE}"
        MAIN_DEPENDENCY "${DATA_FILE}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    list(APPEND DATA_OBJ "${CMAKE_CURRENT_BINARY_DIR}/${DATA_FILE}.o")
endforeach()

add_executable(Platformer ${SRC} ${THIRD_PARTY_SRC} ${DATA_OBJ})
target_link_libraries(
    Platformer
    SDL2::SDL2main SDL2::SDL2
    SDL2_image
)