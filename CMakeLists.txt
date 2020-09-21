cmake_minimum_required(VERSION 3.12)
project(Bolt VERSION 0.0.1 DESCRIPTION "Simple game library built upon SDL2")

if(DEFINED ENV{STD_VERSION})
    set(CMAKE_CXX_STANDARD $ENV{STD_VERSION})
    message("Using C++$ENV{STD_VERSION}")
else()
    set(CMAKE_CXX_STANDARD 17)
    message("Using C++17")
endif()

message("using compiler: ${CMAKE_CXX_COMPILER}")

option(BUILD_SHARED "Build and install the shared library" ON)
option(BUILD_STATIC "Build and install the static library" ON)
option(INSTALL_STATIC "Build and install the static library" ON)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/extras/Chipmunk2D/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/extras/Chipmunk2D/lib)
add_subdirectory(extras/Chipmunk2D)

include_directories(extras/SDL2/include)
link_directories(extras/SDL2/lib)
include_directories(extras/Chipmunk2D/include)
link_directories(extras/Chipmunk2D/src)

include(GenerateExportHeader)

add_library(Bolt SHARED src/component.h src/component.cpp src/game_object.cpp src/game_object.h src/texture.cpp src/texture.h src/sprite.cpp src/sprite.h src/sprite_renderer.cpp src/sprite_renderer.h src/window_manager.cpp src/window_manager.h src/transform.cpp src/transform.h src/events.h src/events.cpp src/collider.h src/utility.h src/geometry.cpp src/geometry.h src/utility.cpp src/text.cpp src/text.h src/font.cpp src/font.h src/text_renderer.cpp src/text_renderer.h src/camera.cpp src/camera.h src/component_template_declaration_pseudo_macro.h src/component_template_definition_pseudo_macro.h src/filesystem_includes.h src/animation.cpp src/animation.h src/rect_collider.cpp src/rect_collider.h src/chipmunk_wrapper.cpp src/chipmunk_wrapper.h)
add_dependencies(Bolt chipmunk)
set_target_properties(Bolt PROPERTIES VERSION 0.0.1)
#export(TARGETS Bolt NAMESPACE Bolt FILE bolt.cmake)
#generate_export_header(Bolt)
#set_target_properties(Bolt PROPERTIES PUBLIC_HEADER src/bolt.h)

target_link_libraries(Bolt)
target_link_libraries(Bolt SDL2)
target_link_libraries(Bolt SDL2_image)
target_link_libraries(Bolt SDL2_ttf)
target_link_libraries(Bolt chipmunk)

install(TARGETS Bolt
        LIBRARY DESTINATION ${CMAKE_CURRENT_LIST_DIR}/out/lib
        PUBLIC_HEADER DESTINATION ${CMAKE_CURRENT_LIST_DIR}/out/include)