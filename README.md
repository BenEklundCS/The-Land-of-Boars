# The Land of Boars

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://cplusplus.com/) 
[![Raylib](https://img.shields.io/badge/Raylib-FA8B00?style=for-the-badge&logo=raylib&logoColor=white)](https://www.raylib.com/) 
[![ImGui](https://img.shields.io/badge/ImGui-009DFF?style=for-the-badge&logo=imgui&logoColor=white)](https://github.com/ocornut/imgui) 

## Overview
**The Land of Boars** is a platformer game built in **C++** using the **Raylib** graphics library. This project is inspired by techniques and design patterns from [Game Programming Patterns](https://gameprogrammingpatterns.com/). While still a work in progress, it showcases a variety of features and design principles aimed at creating an immersive and performant game.

🎮 **Check out a short demo here:**  
[Screencast.2024-08-22.07.46.42.mp4](https://github.com/user-attachments/assets/737d2435-87ed-494a-a426-5baf77388992)

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

---

## Controls
- **Arrow Keys:** Move the player.
- **Spacebar / Up Arrow:** Jump.
- **A Key:** Attack monsters.

---

## Development Roadmap
📆 **Current Status (Fall 2024):**  
Development is progressing at a slower pace due to the school semester. New features and improvements will resume after the term concludes.

### Upcoming Features:
1. **Level Editor:**
   - A user-friendly tool to build and customize levels quickly.
2. **Advanced Enemy AI:**
   - Smarter and more dynamic behaviors for enemies.
3. **Additional Gameplay Mechanics:**
   - Power-ups, collectibles, and more!

---

## Getting Started

### Prerequisites
- **C++ Compiler** (e.g., GCC, Clang, MSVC)
- **Raylib**: [Installation Guide](https://github.com/raysan5/raylib#installation)
- **ImGui**: Included in the project as a submodule.

### Installation
1. Clone the repository:
    ```bash
    git clone https://github.com/BenEklundCS/The-Land-of-Boars.git
    cd The-Land-of-Boars
    ```

2. Build the project using CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Run the game:
    ```bash
    ./TheLandOfBoars
    ```

---

## Screenshots (WIP)
*Add screenshots or GIFs showcasing the game in action!*

---

## Contributions
Contributions are welcome! If you'd like to add new features or fix bugs, feel free to fork the repository and submit a pull request.

---

## License
This project is licensed under the [MIT License](LICENSE).

---

**Stay tuned for updates!** 🚀  
Want to discuss or collaborate? Feel free to reach out or open an issue on [GitHub](https://github.com/BenEklundCS/The-Land-of-Boars/issues).

