# 🌌 Mini Solar System (OpenGL)

A simple interactive solar system visualization built using modern OpenGL (3.3), demonstrating shaders, transformations, and real-time animation.

## 🛰️ Features

- Static glowing Sun at the center
- Two planets orbiting at different speeds and distances
- One moon orbiting one of the planets
- Custom GLSL shaders for color and effects
- Camera controls:
  - Mouse drag to rotate view
  - Scroll to zoom in/out
- Efficient rendering with VAOs/VBOs

---

## 🛠️ Tech Stack

- **Language:** C++17
- **Graphics:** OpenGL 3.3 Core Profile
- **Libraries:**
  - GLAD (manual include)
  - GLFW (via vcpkg)
  - GLM (via vcpkg)
- **Build System:** CMake
- **Dependency Manager:** vcpkg

---

## 📁 Project Structure

solar-system/
├── CMakeLists.txt
├── src/
│ └── main.cpp
├── shaders/
│ ├── vertex.glsl
│ └── fragment.glsl
├── libs/
│ └── glad/
│ ├── include/
│ └── src/
└── vcpkg/


---

## 🚀 Getting Started

### 1. Clone the repo

```bash
git clone https://github.com/yourusername/solar-system.git
cd solar-system

2. Install Dependencies with vcpkg
# If not already initialized
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install glfw3 glm


3. Download & Add GLAD
Generate from glad.sh (OpenGL 3.3, Core profile, C/C++)
Then extract into libs/glad/ with this structure:

libs/glad/
├── include/glad/glad.h
├── include/KHR/khrplatform.h
└── src/glad.c

Create a libs/glad/CMakeLists.txt:
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

🔧 Build Instructions
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build .

▶️ Run
From the root directory (so shaders load correctly):
.\build\Debug\MiniSolarSystem.exe

🎮 Controls
Left mouse drag → Rotate camera

Scroll wheel → Zoom in/out

Enjoy watching planets and the moon orbit in real time!

For hashmap.cpp and lru_implementation.cpp (present in root)
paste it in any c++ compiler and run it.
