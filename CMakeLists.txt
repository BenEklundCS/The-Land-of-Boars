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
        Platform/core/main.cpp
        Platform/core/Window.cpp
        Platform/core/Renderer.cpp
        Game/src/Level/Scene.cpp
        Game/src/Entities/Player/Player.cpp
        Game/src/Entities/GameObject.cpp
        Game/src/Entities/Objects/Platform.cpp
        Game/include/Entities/Monsters/Monster.h
        Game/src/Entities/Monsters/Monster.cpp
        Game/src/Sprites/TextureManager.cpp
        Game/include/Sprites/Animation.h
        Game/src/Sprites/Animation.cpp
        Game/include/Level/Level.h
        Game/src/Level/LevelOne.cpp
        Game/include/Level/LevelOne.h
        Game/src/Level/Level.cpp
        Game/include/Entities/Monsters/Boar.h
        Game/src/Entities/Monsters/Boar.cpp
        Game/include/PhysicsConstants.h
        Platform/core/GameManager.cpp
        Game/include/Entities/Objects/Tile.h
        Game/src/Entities/Objects/Tile.cpp
) # Create an executable with main.cpp as the source

target_link_libraries(${PROJECT_NAME} PRIVATE raylib) # Link raylib to your project

# If additional configuration is needed, set it here:
if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()
