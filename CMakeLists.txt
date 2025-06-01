# Adapted from imgui's example_glfw_vulkan/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(mirage C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

# GLFW (expect that it's installed, use CMAKE_INSTALL_PREFIX to set if not)
# Did not pull the imgui glfw stuff into this repo
# NOTE: am not sure what min version of glfw3 I need for this
find_package(glfw3 REQUIRED)
# TODO: i feel like i want to delete all these?
# option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
# option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
# option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
# option(GLFW_INSTALL "Generate installation target" OFF)
# option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
# add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
include_directories(${GLFW_DIR}/include)

# Dear ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

# ImPlot
set(IMPLOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/implot)
include_directories(${IMPLOT_DIR})

# Libraries
find_package(Vulkan REQUIRED)
#find_library(VULKAN_LIBRARY
  #NAMES vulkan vulkan-1)
#set(LIBRARIES "glfw;${VULKAN_LIBRARY}")
# TODO: feel like i want to change this
set(LIBRARIES "glfw;Vulkan::Vulkan")

# Use vulkan headers from glfw:
include_directories(${GLFW_DIR}/deps)

add_executable(
  mirage
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMPLOT_DIR}/implot.cpp
  ${IMPLOT_DIR}/implot_demo.cpp
  ${IMPLOT_DIR}/implot_items.cpp
)
target_link_libraries(mirage ${LIBRARIES})

