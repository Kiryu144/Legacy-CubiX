cmake_minimum_required(VERSION 3.15)
project(CubiX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# To reference files always from the root directory
include_directories(${PROJECT_SOURCE_DIR}/source/)

# Library includes
include_directories(${PROJECT_SOURCE_DIR}/lib/enet/include/)
include_directories(${PROJECT_SOURCE_DIR}/lib/fast_noise/include/)
include_directories(${PROJECT_SOURCE_DIR}/lib/glad/include/)
include_directories(${PROJECT_SOURCE_DIR}/lib/glfw/include/)
include_directories(${PROJECT_SOURCE_DIR}/lib/glm/include/)
include_directories(${PROJECT_SOURCE_DIR}/lib/imgui/include/)
include_directories(${PROJECT_SOURCE_DIR}/lib/thread/include/)

# Library source files
set(LIBRARY_SOURCE_FILES ${LIBRARY_SOURCE_FILES} lib/enet/src/callbacks.c lib/enet/src/compress.c lib/enet/src/host.c lib/enet/src/list.c lib/enet/src/packet.c lib/enet/src/peer.c lib/enet/src/protocol.c lib/enet/src/unix.c lib/enet/src/win32.c)
set(LIBRARY_SOURCE_FILES ${LIBRARY_SOURCE_FILES} lib/fast_noise/src/FastNoise.cpp)
set(LIBRARY_SOURCE_FILES ${LIBRARY_SOURCE_FILES} lib/glad/src/glad.c)
set(LIBRARY_SOURCE_FILES ${LIBRARY_SOURCE_FILES} lib/imgui/src/imgui.cpp lib/imgui/src/imgui_draw.cpp lib/imgui/src/imgui_widgets.cpp lib/imgui/src/imgui_impl_glfw.cpp lib/imgui/src/imgui_impl_opengl3.cpp)

# Library links
link_directories(${PROJECT_SOURCE_DIR}/lib/glfw/lib)

# Set target_link_library targets
set(LINKER_TARGETS winmm ws2_32 glfw3 gdi32 opengl32)

# Project source files
set(SOURCE_FILES
        ${LIBRARY_SOURCE_FILES}
        source/main.cpp
        source/core/opengl/window.cpp
        source/core/opengl/buffer.cpp
        source/core/opengl/buffer.h
        source/core/util/nocopy.h
        source/core/opengl/texture.cpp
        source/core/opengl/texture.h
        source/core/opengl/shader.cpp
        source/core/opengl/shader.h
        source/core/opengl/helper.cpp
        source/core/opengl/helper.h
        source/core/io/files.cpp
        source/core/io/files.h
        source/core/io/file_path.cpp
        source/core/io/file_path.h
        )

add_executable(CubiX ${SOURCE_FILES} resources.rc)
target_link_libraries(CubiX ${LINKER_TARGETS})