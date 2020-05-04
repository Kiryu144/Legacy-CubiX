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
        source/core/cubix_assert.h
        source/core/cubix_assert.cpp
        source/core/io/window.cpp
        source/core/io/window.h
        source/core/opengl/shader_program.cpp
        source/core/opengl/shader_program.h
        source/core/cubix_log.cpp
        source/core/cubix_log.h
        source/core/opengl/opengl_helper.h
        source/core/opengl/opengl_helper.cpp
        source/core/opengl/attributebuffer.cpp
        source/core/opengl/attributebuffer.h
        source/core/event.h
        source/game/world/voxel/voxel.cpp
        source/game/world/voxel/voxel.h
        source/core/data/color.cpp
        source/core/data/color.h
        source/core/data/container3d.h
        source/core/math/transform.cpp
        source/core/math/transform.h
        source/core/data/multiple_facing.cpp
        source/core/data/multiple_facing.h
        source/core/io/riff_parser.cpp
        source/core/io/riff_parser.h
        source/game/cubix.cpp
        source/game/cubix.h
        source/game/world/chunk/world_chunk.cpp
        source/game/world/chunk/world_chunk.h
        source/game/world/world.cpp
        source/game/world/world.h
        source/defines.h
        source/game/rendering/moveable_view.cpp
        source/game/rendering/moveable_view.h
        source/core/math/view.cpp
        source/core/math/view.h
        source/core/math/glm_math.h
        source/core/time/game_time.cpp
        source/core/time/game_time.h
        source/core/net/net_client.cpp
        source/core/net/net_client.h
        source/core/net/net_server.cpp
        source/core/net/net_server.h
        source/core/net/net_instance.cpp
        source/core/net/net_instance.h
        source/game/cubix_client.cpp
        source/game/cubix_client.h
        source/game/cubix_server.cpp
        source/game/cubix_server.h
        source/game/packet/packet.h
        source/game/packet/packet.cpp
        source/game/packet/packet_client_information.cpp
        source/game/packet/packet_client_information.h
        source/game/packet/packet_server_information.cpp
        source/game/packet/packet_server_information.h
        source/core/data/static_string.h
        source/game/player/connected_client.cpp
        source/game/player/connected_client.h
        source/core/logic/serializeable.h
        source/core/logic/no_copy.h
        source/core/logic/memory.h
        source/game/rendering/renderer.cpp
        source/game/rendering/renderer.h
        source/game/world/chunk/world_chunk_container.cpp
        source/core/data/container2d.h
        source/core/cubix_macro.h
        source/core/logic/lockable.h
        source/core/io/user_input_handler.cpp
        source/core/io/user_input_handler.h
        source/core/math/axis_aligned_bb.cpp
        source/core/math/axis_aligned_bb.h
        source/core/opengl/data/attribute.h
        source/core/opengl/data/single_attribute.cpp
        source/core/opengl/data/single_attribute.h
        source/core/opengl/data/interleaved_attribute.cpp
        source/core/opengl/data/interleaved_attribute.h
        source/core/time/stop_watch.cpp
        source/core/time/stop_watch.h
        source/core/time/average_stop_watch.cpp
        source/core/time/average_stop_watch.h
        source/core/logic/singelton.h
        source/core/math/rigidbody.cpp
        source/core/math/rigidbody.h
        source/core/data/registry.h
        source/core/logic/string_cast.h
        source/core/logic/string_cast.cpp
        source/game/world/entity/entity.cpp
        source/game/world/entity/entity.h
        source/game/world/entity/player.cpp
        source/game/world/entity/player.h
        source/game/rendering/world/gizmo_renderer.cpp
        source/game/rendering/world/gizmo_renderer.h
        source/game/world/voxel/placed_voxel.cpp
        source/game/world/voxel/placed_voxel.h
        source/core/opengl/opengl_context.cpp
        source/core/opengl/opengl_context.h
        source/core/opengl/imgui_context.cpp
        source/core/opengl/imgui_context.h
        source/core/time/auto_stop_watch.cpp
        source/core/time/auto_stop_watch.h
        source/game/rendering/world/block_outline_renderer.cpp
        source/game/rendering/world/block_outline_renderer.h
        source/game/rendering/sub_renderer.h
        source/game/player/player_controller.cpp
        source/game/player/player_controller.h
        source/core/data/process_state.h
        source/game/rendering/world/world_chunk_renderer.cpp
        source/game/rendering/world/world_chunk_renderer.h
        source/game/world/chunk/world_chunk_layer.cpp
        source/game/world/chunk/world_chunk_layer.h source/game/world/chunk/world_chunk_mesh.cpp source/game/world/chunk/world_chunk_mesh.h)

add_executable(CubiX ${SOURCE_FILES} resources.rc)
target_link_libraries(CubiX ${LINKER_TARGETS})