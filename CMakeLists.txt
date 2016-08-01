cmake_minimum_required(VERSION 3.1)
project(wxApp)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
  message(ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

set(wxWidgets_USE_LIBS)
set(WXWINDOWS_USE_GL)
find_package(wxWidgets COMPONENTS core base gl REQUIRED)
find_package(wxWindows)
include(${wxWidgets_USE_FILE})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(
  include
  third-party/tinyobjloader
  ${wxWidgets_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
)

add_library(glad
  src/glad.c)

add_library(gl3w
  src/gl3w.c)

# add_library(tinyobjloader
#   third-party/tinyobjloader/tiny_obj_loader.cc)

add_executable(${PROJECT_NAME}
  src/wxapp.cpp)

target_link_libraries(${PROJECT_NAME}
  ${wxWidgets_LIBRARIES}
  dl
  gl3w
)

add_executable(gladtest
  src/gladtest.cpp)

target_link_libraries(gladtest
  dl
  glad
  ${GLFW_LIBRARIES}
)

add_executable(gl3wtest
  src/gl3wtest.cpp)

target_link_libraries(gl3wtest
  dl
  gl3w
  ${GLFW_LIBRARIES}
)

add_executable(loadobj
  src/loadobj.cpp
  third-party/tinyobjloader/tiny_obj_loader.cc)

