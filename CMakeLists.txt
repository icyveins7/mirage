cmake_minimum_required(VERSION 3.20)

project(mirage)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# Assume IMGUI_DIR is specified as environment variable
if (DEFINED ENV{IMGUI_DIR})
  set(IMGUI_DIR $ENV{IMGUI_DIR})
  message("IMGUI_DIR = " ${IMGUI_DIR})
else()
  message(FATAL_ERROR "Please define the IMGUI_DIR environment variable.")
endif()

# Assume IMPLOT_DIR is specified as environment variable
if (DEFINED ENV{IMPLOT_DIR})
  set(IMPLOT_DIR $ENV{IMPLOT_DIR})
  message("IMPLOT_DIR = " ${IMPLOT_DIR})
else()
  message(FATAL_ERROR "Please define the IMPLOT_DIR environment variable.")
endif()

# Note that a lot of the following is referenced from the makefiles
# In particular I referenced example_glfw_opengl3,
# since that's what I intend to use most of the time

# Define all imgui sources
set(IMGUI_SRCS
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp
)
# message("imgui srcs = ${IMGUI_SRCS}")
set(IMGUI_DEMO_SRC ${IMGUI_DIR}/imgui_demo.cpp)
set(IMGUI_IMPL_SRCS
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

# Define implot sources
set(IMPLOT_SRCS
  ${IMPLOT_DIR}/implot.cpp
  ${IMPLOT_DIR}/implot_items.cpp
)
set(IMPLOT_DEMO_SRC ${IMPLOT_DIR}/implot_demo.cpp)
include_directories(${IMPLOT_DIR})

# Handle OS types
if (APPLE)
  find_library(COCOA_LIBRARY Cocoa)
  find_library(IOKIT_LIBRARY IOKit)
  find_library(COREVIDEO_LIBRARY CoreVideo)
  find_library(OPENGL_LIBRARY OpenGL)
  find_package(glfw3 3.4 REQUIRED) # from homebrew
  include_directories(/opt/homebrew/include) # For glfw3.h
  set(CMAKE_OSX_ARCHITECTURES "arm64") # For M1 and later
else()
  message(FATAL_ERROR "No other system type recognised for now.")
endif()

# Test compile of the imgui_demo
add_executable(imgui_demo
  ${IMGUI_DEMO_SRC}
  ${IMGUI_SRCS}
  ${IMGUI_IMPL_SRCS}
  ${IMGUI_DIR}/examples/example_glfw_opengl3/main.cpp
)
target_link_libraries(imgui_demo PUBLIC ${OPENGL_LIBRARY} glfw)

# Test compile of our implot demo (internally written)
add_executable(implot_demo
  ${IMGUI_SRCS}
  ${IMGUI_IMPL_SRCS}
  ${IMPLOT_SRCS}
  ${IMPLOT_DEMO_SRC}
  src/glfw_opengl3/main.cpp
)
target_link_libraries(implot_demo PUBLIC ${OPENGL_LIBRARY} glfw)
