cmake_minimum_required(VERSION 2.8.12)
project(wxApp)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
else()
  message(ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

if(NOT DEFINED WX_INSTALL_PATH)
  set(WX_INSTALL_PATH "/home/clint/installs")
endif()

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WX_INSTALL_PATH})

set(wxWidgets_USE_LIBS)
set(WXWINDOWS_USE_GL)
find_package(wxWidgets 3.1 COMPONENTS core base gl REQUIRED)
find_package(wxWindows)
include(${wxWidgets_USE_FILE})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_subdirectory(third-party/nanogui)

include_directories(
  include
  third-party/tinyobjloader
  third-party/nanogui/include
  ${NANOGUI_EXTRA_INCS}
  ${wxWidgets_INCLUDE_DIRS}
  ${GLFW_INCLUDE_DIRS}
)

add_definitions(${NANOGUI_EXTRA_DEFS})

add_library(glad
  src/glad.c)

add_library(gl3w
  src/gl3w.c)

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

add_executable(nanoguitest
  src/nanoguitest.cpp)

target_link_libraries(nanoguitest
  nanogui
  ${NANOGUI_EXTRA_LIBS})

add_executable(nanoguiglfw
  src/nanoguiglfw.cpp)

target_link_libraries(nanoguiglfw
  nanogui
  gl3w
  ${NANOGUI_EXTRA_LIBS})
