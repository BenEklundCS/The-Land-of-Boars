# The Land of Boars

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://cplusplus.com/) 
[![Raylib](https://img.shields.io/badge/Raylib-FA8B00?style=for-the-badge&logo=raylib&logoColor=white)](https://www.raylib.com/) 
[![ImGui](https://img.shields.io/badge/ImGui-009DFF?style=for-the-badge&logo=imgui&logoColor=white)](https://github.com/ocornut/imgui) 

## Overview
**The Land of Boars** is a platformer game built in **C++** using the **Raylib** graphics library. This project is inspired by techniques and design patterns from [Game Programming Patterns](https://gameprogrammingpatterns.com/). While still a work in progress, it showcases a variety of features and design principles aimed at creating an immersive and performant game.

🎮 **Check out a short demo here:**  
[Gameplay Demo](https://www.youtube.com/watch?v=zfADrx9wfsA)
[Level Editor](https://www.youtube.com/watch?v=1qH6dVuWXyU)

---

## Key Features
- **Complex Game Logic:**
  - Handles player actions such as movement, jumping, and attacking.
  - Includes interactions with environmental objects and enemies.

- **Custom Renderer:**
  - Manages background and game object rendering to ensure smooth visuals.

- **Sound and Texture Management:**
  - Integrated a **Sound Manager** and **Texture Manager** using the **Singleton Pattern** for centralized resource management.

- **Design Patterns:**
  - **Observer Pattern**: Manages event handling for decoupled and scalable systems.
  - **Command Pattern**: Implements input management for flexible control schemes.

- **Performance Optimization:**
  - Parallelized update loops to enhance gameplay responsiveness.

- **Debugging Tools:**
  - Built-in debug and developer menus using the **ImGui** library for rapid testing and fine-tuning.

- **Level Editing:**
  - Implemented TileMap editing live while in-game, as well as Save/Load levels to/from file. Full Level Editor is WIP.

---

## Controls
- **Arrow Keys:** Move the player.
- **Spacebar / Up Arrow:** Jump.
- **A Key:** Attack monsters.

---

## Development Roadmap

### Upcoming Features:
1. **Level Editor:**
   - A user-friendly tool to build and customize levels quickly.
2. **Advanced Enemy AI:**
   - Smarter and more dynamic behaviors for enemies.
3. **Additional Gameplay Mechanics:**
   - Power-ups, collectibles, and more!
4. **Game UI:**
   - Full game UI and start menu.

---

## Getting Started

### Prerequisites
To build and run the game, ensure you have the following installed:
- **C++ Compiler**: A modern compiler like GCC, Clang, or MSVC that supports C++17.
- **CMake**: Version 3.11 or newer.
- **Git**: Required to clone the repository and fetch dependencies.

### Installation

1. **Clone the Repository**  
   Clone the project and navigate into its directory:
   git clone https://github.com/BenEklundCS/The-Land-of-Boars.git
   cd The-Land-of-Boars

2. **Build the Project**  
   Use CMake to configure and build the project:
   mkdir build
   cd build
   cmake ..
   cmake --build .

    - On **Windows**, Visual Studio project files will be generated by default (if MSVC is installed).
    - On **Linux/macOS**, Makefiles (or Ninja files, if installed) will be generated.

3. **Run the Game**  
   After building, you can run the executable:
    - On **Windows**:
      The_Land_of_Boars.exe
    - On **Linux/macOS**:
      ./The_Land_of_Boars

---

### Notes
- **Dependencies**:
    - The project uses `FetchContent` to automatically download and build dependencies:
        - [Raylib](https://github.com/raysan5/raylib)
        - [ImGui](https://github.com/ocornut/imgui)
        - [rlImGui](https://github.com/raylib-extras/rlImGui)
    - No manual installation of these libraries is required.
- **Debug Builds**:
    - On Windows, necessary DLLs are automatically copied to the output directory when building in Debug mode.

### Additional Commands
- **Clean the Build Directory**:
  rm -rf build
- **Reconfigure and Rebuild**:
  mkdir build
  cd build
  cmake ..
  cmake --build .

---

## Contributions
Contributions are welcome! If you'd like to add new features or fix bugs, feel free to fork the repository and submit a pull request.

---

**Stay tuned for updates!** 🚀  
Want to discuss or collaborate? Feel free to reach out or open an issue on [GitHub](https://github.com/BenEklundCS/The-Land-of-Boars/issues).

