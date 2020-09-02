cmake_minimum_required(VERSION 3.18)
project(Bolt VERSION 0.0.1 DESCRIPTION "Simple game library built upon SDL2")

set(CMAKE_CXX_STANDARD 20)
include(GenerateExportHeader)

add_library(Bolt SHARED src/component.h src/component.cpp src/game_object.cpp src/game_object.h src/texture.cpp src/texture.h src/sprite.cpp src/sprite.h src/sprite_renderer.cpp src/sprite_renderer.h src/window_manager.cpp src/window_manager.h src/transform.cpp src/transform.h src/events.h src/events.cpp src/collider.cpp src/collider.h src/utility.h src/geometry.cpp src/geometry.h src/utility.cpp src/text.cpp src/text.h src/font.cpp src/font.h src/text_renderer.cpp src/text_renderer.h src/camera.cpp src/camera.h)
set_target_properties(Bolt PROPERTIES VERSION 0.0.1)
generate_export_header(Bolt)
#set_target_properties(Bolt PROPERTIES PUBLIC_HEADER src/bolt.h)

target_link_libraries(Bolt)

install(TARGETS Bolt
        LIBRARY DESTINATION /home/jack/Documents/Bolt/out/lib
        PUBLIC_HEADER DESTINATION /home/jack/Documents/Bolt/out/include)