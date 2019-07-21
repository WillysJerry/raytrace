cmake_minimum_required(VERSION 2.8)
project(raytracer)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(include ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-g")

set(MATH_FILES
  lib/math/transform.cpp)

set(SOURCE_FILES
  src/main.cpp
  src/camera/camera.cpp
  src/entity/entity.cpp
  src/entity/sphere.cpp
  src/entity/plane.cpp
  src/light_model/phong_model.cpp)

add_library(mathlib STATIC ${MATH_FILES})

add_executable(raytracer ${SOURCE_FILES})
target_link_libraries(raytracer mathlib ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
