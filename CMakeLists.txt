cmake_minimum_required(VERSION 3.15)
project(CubiX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# To reference files always from the root directory
include_directories(${PROJECT_SOURCE_DIR}/source/)

# GLAD (https://glad.dav1d.de/)
include_directories(${PROJECT_SOURCE_DIR}/../libraries/glad/include)

# GLFW (https://www.glfw.org/)
include_directories(${PROJECT_SOURCE_DIR}/../libraries/glfw/include)
link_directories(${PROJECT_SOURCE_DIR}/../libraries/glfw/lib-mingw/)

# GLM (https://glm.g-truc.net/)
include_directories(${PROJECT_SOURCE_DIR}/../libraries/glm/include)

# Set target_link_library targets
set(LINKER_TARGETS glfw3 gdi32 opengl32)

# List of all the source files to compile
set(SOURCE_FILES source/main.cpp)


add_executable(CubiX ${SOURCE_FILES})
target_link_libraries(CubiX ${LINKER_TARGETS})