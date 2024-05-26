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

add_executable(
        ${PROJECT_NAME}
        main.cpp
        Renderer/Window.cpp
        Renderer/Renderer.cpp
        Level/LevelScene.cpp
        Entities/Player/Player.cpp
        Entities/GameObject.cpp
        Entities/Objects/Platform.cpp
        Entities/Monsters/Monster.h
        Entities/Monsters/Monster.cpp
        Sprites/TextureManager.cpp
        Sprites/Animation.h
        Sprites/Animation.cpp
        Level/Level.h
        Level/LevelOne.cpp
        Level/LevelOne.h
        Level/Level.cpp
        Entities/Monsters/Boar.h
        Entities/Monsters/Boar.cpp
        Entities/PhysicsConstants.h
) # Create an executable with main.cpp as the source

target_link_libraries(${PROJECT_NAME} PRIVATE raylib) # Link raylib to your project

# If additional configuration is needed, set it here:
if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
            LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()
