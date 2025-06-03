cmake_minimum_required(VERSION 3.10)

# Tell CMake to use vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(MiniSolarSystem)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Add GLAD manually
add_subdirectory(libs/glad)  # ← You need to clone GLAD here

# Add executable
add_executable(MiniSolarSystem src/main.cpp)

# Link libraries
target_link_libraries(MiniSolarSystem
    PRIVATE
        glad
        glfw
        glm::glm
)

# Include directories
target_include_directories(MiniSolarSystem PRIVATE libs/glad/include)
