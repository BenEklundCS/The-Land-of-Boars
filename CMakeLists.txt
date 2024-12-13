cmake_minimum_required(VERSION 3.11)
project(The_Land_of_Boars)

# Set C++ standard and debugging flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
endif()

# Platform-specific configuration
if (WIN32)
    # Windows configuration: Raylib 4.5 and custom DLL handling
    find_package(raylib 4.5 QUIET)
    if (NOT raylib_FOUND)
        include(FetchContent)
        FetchContent_Declare(
                raylib
                URL https://github.com/raysan5/raylib/archive/refs/tags/4.5.0.tar.gz
                DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )
        FetchContent_MakeAvailable(raylib)
    endif()
elseif (UNIX)
    # Linux configuration: Raylib 3.7 with debugging flags
    find_package(raylib 3.0 QUIET)
    if (NOT raylib_FOUND)
        include(FetchContent)
        FetchContent_Declare(
                raylib
                URL https://github.com/raysan5/raylib/archive/refs/tags/3.7.0.tar.gz
        )
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# FetchContent for ImGUI (same for both platforms)
include(FetchContent)
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG master
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(imgui)

# FetchContent for rlImGui (same for both platforms)
FetchContent_Declare(
        rlimgui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG main
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(rlimgui)

# Group related files into variables
set(PLATFORM_SOURCES
        src/Platform/main.cpp
        src/Platform/Window.cpp
        src/Platform/Renderer.cpp
        src/Platform/Engine.cpp
        src/Platform/GUI.cpp
)

set(GAME_MANAGEMENT_SOURCES
        src/Game/Management/GameStateManager.cpp
        src/Game/Management/TileManager.cpp
        src/Game/Management/InputManager.cpp
        src/Game/Management/SoundManager.cpp
)

set(GAME_EVENTS_SOURCES
        src/Game/Events/Commands/PlayerCommands.cpp
        src/Game/Events/Commands/Command.cpp
        src/Game/Events/Observers/Observer.cpp
        src/Game/Events/Observers/Subject.cpp
)

set(GAME_ENTITIES_SOURCES
        src/Game/Entities/Player/Player.cpp
        src/Game/Entities/GameObject.cpp
        src/Game/Entities/Objects/Platform.cpp
        src/Game/Entities/Objects/Tile.cpp
        src/Game/Entities/Monsters/Monster.cpp
        src/Game/Entities/Monsters/Boar.cpp
        src/Game/Entities/Objects/MovingPlatform.cpp
        src/Game/Entities/Objects/Tree.cpp
        src/Game/Entities/Effects/ParticleCone.cpp
        src/Game/Entities/Monsters/Bee.cpp
        src/Game/Entities/Monsters/Snail.cpp
)

set(GAME_LEVEL_SOURCES
        src/Game/Level/LevelOne.cpp
        src/Game/Level/Level.cpp
        src/Game/Level/LevelLoader.cpp
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
        include/Game/Entities/Monsters/Snail.h
        include/Game/Entities/PhysicsConstants.h
        include/Game/Entities/Objects/Tile.h
        include/Game/Management/TileManager.h
        include/Game/Events/Commands/PlayerCommands.h
        include/Game/Events/Observers/Subject.h
        include/Game/Entities/Objects/Tree.h
        include/Game/Level/LevelLoader.h
)

# Combine all sources
set(SOURCES
        ${PLATFORM_SOURCES}
        ${GAME_MANAGEMENT_SOURCES}
        ${GAME_ENTITIES_SOURCES}
        ${GAME_LEVEL_SOURCES}
        ${GAME_SPRITES_SOURCES}
        ${GAME_HEADERS}
        ${GAME_EVENTS_SOURCES}
        ${rlimgui_SOURCE_DIR}/rlImGui.cpp
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        src/Game/Entities/CollisionHandler.cpp
        include/Platform/Globals.h
        include/Game/Entities/uiElements/HealthBar.h
        src/Game/Entities/uiElements/HealthBar.cpp
        src/Game/Entities/uiElements/StartButton.cpp
        include/Game/Entities/uiElements/StartButton.h
)

# Define executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Windows-specific settings for executable, now below target definition
if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE YES
            #LINK_FLAGS "/ENTRY:mainCRTStartup"
    )

    # Post-build DLL handling for Windows in Debug mode
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:raylib>
                $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
endif()

# Include directories for ImGui and rlImGui
target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_SOURCE_DIR} ${rlimgui_SOURCE_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
# Set policy to avoid warnings
cmake_policy(SET CMP0135 NEW)

# Include directories for rlImGui configurations
include_directories(${rlimgui_SOURCE_DIR}/include)