cmake_minimum_required(VERSION 3.15)
project(CubiX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
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
set(LINKER_TARGETS winmm ws2_32 glfw3 gdi32 opengl32)

# List of all the source files to compile

set(SOURCE_FILES lib/enet/callbacks.c lib/enet/compress.c lib/enet/host.c lib/enet/list.c lib/enet/packet.c lib/enet/peer.c lib/enet/protocol.c lib/enet/unix.c lib/enet/win32.c)
set(SOURCE_FILES ${SOURCE_FILES} lib/fast_noise/FastNoise.cpp)

set(SOURCE_FILES
        ${SOURCE_FILES}
        ./../libraries/glad/src/glad.c
        source/main.cpp
        source/core/cubix_assert.h
        source/core/cubix_assert.cpp
        source/core/opengl/window.cpp
        source/core/opengl/window.h
        source/core/opengl/shader_program.cpp
        source/core/opengl/shader_program.h
        source/core/cubix_log.cpp
        source/core/cubix_log.h
        source/core/opengl/openg_error.h
        source/core/opengl/opengl_error.cpp
        source/core/opengl/opengl_helper.h
        source/core/opengl/opengl_helper.cpp
        source/core/opengl/attributebuffer.cpp
        source/core/opengl/attributebuffer.h
        source/core/event.h
        source/game/common/voxel/voxel.cpp
        source/game/common/voxel/voxel.h
        source/core/math/color.cpp
        source/core/math/color.h
        source/core/opengl/attribute.cpp
        source/core/opengl/attribute.h
        source/core/data/container3d.h
        source/game/common/voxel/voxel_group.cpp
        source/game/common/voxel/voxel_group.h
        source/core/math/transform.cpp
        source/core/math/transform.h
        source/core/data/facing.cpp
        source/core/data/facing.h
        source/core/io/riff_parser.cpp
        source/core/io/riff_parser.h
        source/game/common/cubix.cpp
        source/game/common/cubix.h
        source/game/common/world/world_chunk.cpp
        source/game/common/world/world_chunk.h
        source/game/common/world/world.cpp
        source/game/common/world/world.h
        source/defines.h
        source/game/client/moveable_view.cpp
        source/game/client/moveable_view.h
        source/core/math/view.cpp
        source/core/math/view.h
        source/core/math/glm_math.h
        source/core/math/game_time.cpp
        source/core/math/game_time.h
        source/core/net/net_client.cpp
        source/core/net/net_client.h
        source/core/net/net_server.cpp
        source/core/net/net_server.h
        source/core/net/net_instance.cpp
        source/core/net/net_instance.h
        source/game/client/cubix_client.cpp
        source/game/client/cubix_client.h
        source/game/server/cubix_server.cpp
        source/game/server/cubix_server.h
        source/game/proxy.h
        source/game/common/entity/entity.cpp
        source/game/common/entity/entity.h
        source/game/common/entity/player.cpp
        source/game/common/entity/player.h
        source/game/common/entity/living_entity.cpp
        source/game/common/entity/living_entity.h
        source/game/common/entity/entitytype.h
        source/game/common/packet/packet.h
        source/game/common/packet/packet.cpp
        source/game/common/packet/packet_client_information.cpp
        source/game/common/packet/packet_client_information.h
        source/game/common/packet/packet_server_information.cpp
        source/game/common/packet/packet_server_information.h
        source/core/data/static_string.h
        source/game/server/connected_client.cpp
        source/game/server/connected_client.h
        source/core/data/serializeable.h
        source/core/data/no_copy.h
        source/core/data/memory.h source/game/client/renderer.cpp source/game/client/renderer.h source/game/common/world/chunk_worker.cpp source/game/common/world/chunk_worker.h source/game/common/worldgenerator/world_generator.cpp source/game/common/worldgenerator/world_generator.h source/game/common/worldgenerator/world_generator_perlin.cpp source/game/common/worldgenerator/world_generator_perlin.h source/game/common/world/world_chunk_column.cpp source/game/common/world/world_chunk_column.h source/core/data/container2d.h source/core/cubix_macro.h source/core/data/lockable.h)


add_executable(CubiX ${SOURCE_FILES} resources.rc)
target_link_libraries(CubiX ${LINKER_TARGETS})
#add_compile_definitions(CubiX ENET_DEBUG)