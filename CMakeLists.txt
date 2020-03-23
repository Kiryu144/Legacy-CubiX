cmake_minimum_required(VERSION 3.15)
project(CubiX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# To reference files always from the root directory
include_directories(${PROJECT_SOURCE_DIR}/source/)

# To reference files from the lib directory
include_directories(${PROJECT_SOURCE_DIR}/lib/)

# GLAD (https://glad.dav1d.de/)
include_directories(${PROJECT_SOURCE_DIR}/../libraries/glad/include)

# GLFW (https://www.glfw.org/)
include_directories(${PROJECT_SOURCE_DIR}/../libraries/glfw/include)
link_directories(${PROJECT_SOURCE_DIR}/../libraries/glfw/lib-mingw/)

# GLM (https://glm.g-truc.net/)
include_directories(${PROJECT_SOURCE_DIR}/../libraries/glm/include)

# e-net (https://glm.g-truc.net/)
include_directories(${PROJECT_SOURCE_DIR}/../libraries/enet/include)

# Set target_link_library targets
set(LINKER_TARGETS glfw3 gdi32 opengl32)

# List of all the source files to compile
set(SOURCE_FILES ./../libraries/glad/src/glad.c source/main.cpp source/core/cubix_assert.h source/core/cubix_assert.cpp source/core/opengl/window.cpp source/core/opengl/window.h source/core/opengl/shader_program.cpp source/core/opengl/shader_program.h source/core/cubix_log.cpp source/core/cubix_log.h source/core/opengl/openg_error.h source/core/opengl/opengl_error.cpp source/core/opengl/opengl_helper.h source/core/opengl/opengl_helper.cpp source/core/opengl/attributebuffer.cpp source/core/opengl/attributebuffer.h source/core/event.h source/game/common/voxel/voxel.cpp source/game/common/voxel/voxel.h source/core/math/color.cpp source/core/math/color.h source/core/opengl/attribute.cpp source/core/opengl/attribute.h source/core/data/container3d.h source/game/common/voxel/voxel_group.cpp source/game/common/voxel/voxel_group.h source/core/math/transform.cpp source/core/math/transform.h source/core/data/facing.cpp source/core/data/facing.h source/core/io/riff_parser.cpp source/core/io/riff_parser.h source/game/cubix.cpp source/game/cubix.h source/game/common/world/world_chunk.cpp source/game/common/world/world_chunk.h source/game/common/world/world.cpp source/game/common/world/world.h source/defines.h source/game/client/moveable_view.cpp source/game/client/moveable_view.h source/core/math/view.cpp source/core/math/view.h)
set(SOURCE_FILES ${SOURCE_FILES} lib/fast_noise/FastNoise.cpp source/core/math/glm_math.h)

add_executable(CubiX ${SOURCE_FILES} resources.rc)
target_link_libraries(CubiX ${LINKER_TARGETS})