cmake_minimum_required(VERSION 3.1)
project(marvel_network)

include(CheckCXXCompilerFlag)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -s -O3 -DNDEBUG")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")

CHECK_CXX_COMPILER_FLAG("-fsanitize=address" HAS_ASAN_FLAG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/}")

if (HAS_ASAN_FLAG)
    message(STATUS "Enabling address sanitizer")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")
endif ()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/)

#======================OPENGL======================
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif ()
#======================OPENGL======================

#======================INI=====================
add_library(INIH STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/ini.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/ini.h)
#======================INI=====================

#======================GLEW=====================
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/include)

add_library(GLEW STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/src/glew.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/GLEW/include/GL/glew.h)

SET_TARGET_PROPERTIES(GLEW PROPERTIES
        COMPILE_FLAGS "-DGLEW_STATIC"
        )

target_link_libraries(GLEW ${OPENGL_LIBRARIES})
#======================GLEW=====================

#======================GLFW=====================
set(GLFW_BUILD_EXAMPLES NO)
set(GLFW_BUILD_TESTS NO)
set(GLFW_BUILD_DOCS NO)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/GLFW/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/GLFW/include)
#======================GLFW=====================

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

set(SOURCE_FILES
        main.cpp
        include/Graph.hpp
        src/Graph.cpp
        src/Drawable.cpp
        include/Drawable.hpp
        src/Shader.cpp
        include/Shader.hpp
        src/Scene.cpp
        include/Scene.hpp
        include/utils.hpp
        include/dbg.hpp
        src/FontAtlas.cpp
        include/FontAtlas.hpp
        src/Config.cpp
        include/Config.hpp)

add_executable(marvel_network ${SOURCE_FILES})

set_target_properties(marvel_network PROPERTIES OUTPUT_NAME "MarvelNetwork-${CMAKE_BUILD_TYPE}")

# habilita suporte para threads se a biblioteca pthreads está disponível
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if (THREADS_HAVE_PTHREAD_ARG)
    target_link_libraries(marvel_network Threads::Threads)
else ()
    add_definitions(-DCSV_IO_NO_THREAD)
endif ()

target_link_libraries(marvel_network GLEW ${FREETYPE_LIBRARIES} glfw ${GLFW_LIBRARIES} INIH)

add_custom_command(TARGET marvel_network POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:marvel_network>/shaders)

add_custom_command(TARGET marvel_network POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:marvel_network>)
