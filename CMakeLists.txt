cmake_minimum_required(VERSION 3.11) # Set the minimum version of CMake

project(Platformer) # Define the project name

# Find raylib
find_package(raylib 3.0 QUIET) # Let CMake search for a pre-installed raylib

if (NOT raylib_FOUND) # If there's none found, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/3.7.0.tar.gz
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(CMAKE_CXX_STANDARD 17) # Set C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")


add_executable(
        ${PROJECT_NAME}
        src/Platform/main.cpp
        src/Platform/Window.cpp
        src/Platform/Renderer.cpp
        src/Game/Management/GameStateManager.cpp
        src/Game/Entities/Player/Player.cpp
        src/Game/Entities/GameObject.cpp
        src/Game/Entities/Objects/Platform.cpp
        include/Game/Entities/Monsters/Monster.h
        src/Game/Entities/Monsters/Monster.cpp
        src/Game/Sprites/TextureManager.cpp
        include/Game/Sprites/Animation.h
        src/Game/Sprites/Animation.cpp
        include/Game/Level/Level.h
        src/Game/Level/LevelOne.cpp
        include/Game/Level/LevelOne.h
        src/Game/Level/Level.cpp
        include/Game/Entities/Monsters/Boar.h
        src/Game/Entities/Monsters/Boar.cpp
        include/Game/Entities/PhysicsConstants.h
        src/Platform/Engine.cpp
        include/Game/Entities/Objects/Tile.h
        src/Game/Entities/Objects/Tile.cpp
        include/Game/Management/TileManager.h
        src/Game/Management/TileManager.cpp
) # Create an executable with main.cpp as the source

target_link_libraries(${PROJECT_NAME} PRIVATE raylib) # Link raylib to your project

# If additional configuration is needed, set it here:
if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()
