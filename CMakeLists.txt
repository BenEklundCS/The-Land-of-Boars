cmake_minimum_required(VERSION 3.11)

project(Platformer) # Define the project name

# Find raylib
find_package(raylib 3.0 QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/3.7.0.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# Group related files into variables
set(PLATFORM_SOURCES
        src/Platform/main.cpp
        src/Platform/Window.cpp
        src/Platform/Renderer.cpp
        src/Platform/Engine.cpp
)

set(GAME_MANAGEMENT_SOURCES
        src/Game/Management/GameStateManager.cpp
        src/Game/Management/TileManager.cpp
)

set(GAME_ENTITIES_SOURCES
        src/Game/Entities/Player/Player.cpp
        src/Game/Entities/GameObject.cpp
        src/Game/Entities/Objects/Platform.cpp
        src/Game/Entities/Objects/Tile.cpp
        src/Game/Entities/Monsters/Monster.cpp
        src/Game/Entities/Monsters/Boar.cpp
)

set(GAME_LEVEL_SOURCES
        src/Game/Level/LevelOne.cpp
        src/Game/Level/Level.cpp
)

set(GAME_SPRITES_SOURCES
        src/Game/Sprites/TextureManager.cpp
        src/Game/Sprites/Animation.cpp
)

set(GAME_HEADERS
        include/Game/Entities/Monsters/Monster.h
        include/Game/Sprites/Animation.h
        include/Game/Level/Level.h
        include/Game/Level/LevelOne.h
        include/Game/Entities/Monsters/Boar.h
        include/Game/Entities/PhysicsConstants.h
        include/Game/Entities/Objects/Tile.h
        include/Game/Management/TileManager.h
)

# Combine all sources
set(SOURCES
        ${PLATFORM_SOURCES}
        ${GAME_MANAGEMENT_SOURCES}
        ${GAME_ENTITIES_SOURCES}
        ${GAME_LEVEL_SOURCES}
        ${GAME_SPRITES_SOURCES}
        ${GAME_HEADERS}
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()
