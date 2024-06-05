# Platformer Game

## Overview
This is a platformer game developed using C++ and Raylib. The project is organized into platform and game folders, attempting to seperate the logic of these systems.
The project uses modern C++ features, including `std::unique_ptr` for memory management rather than new/delete.

## Features
- Player animations
- Monster behaviors
- Collision detection
- Level management

## Setup
1. **Install Dependencies**:
   - C++ compiler
   - Raylib
   - CMakeLists should build these things for you, but I'm not to the point of testing that yet :) 

2. **Build**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make

3. **Run**:

  ./Platformer

## Usage

- Use the arrow keys to control the player
- Spacebar OR up arrow to jump
