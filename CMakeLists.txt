cmake_minimum_required(VERSION 3.28)

project(Game)

include(FetchContent)

set(RAYLIB_VERSION 4.2.0)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.2.0.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

set(
SOURCE_FILES

    src/main.cpp
    src/entity.cpp
    src/game.cpp
    src/gui.cpp
    src/plants.cpp
    src/player.cpp 
    src/TileManger.cpp 
    src/utils.cpp 
    src/tile.cpp
    src/play.cpp
)

add_executable(Game ${SOURCE_FILES})
target_link_libraries(Game raylib)

if(WIN32)

    target_sources(Game PRIVATE Assets/Windows/app.rc)
    target_link_options(Game PRIVATE $<$<CONFIG:Release>:-mwindows>)
elseif(APPLE)

    target_link_options(Game PRIVATE $<$<CONFIG:Release>:-MACOSX_BUNDLE>)
endif()

target_compile_definitions(Game PUBLIC $<$<CONFIG:Debug>:DEBUG_ENABLED>)

if("${PLATFORM}" STREQUAL "Web")

    message(FATAL_ERROR "Do not build in this project in the Web as it doesn't work!")
endif()

if(APPLE)

    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
