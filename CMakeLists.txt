cmake_minimum_required(VERSION 3.20)

project(mirage)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# Assume IMGUI_DIR is specified as environment variable
if (DEFINED ENV{IMGUI_DIR})
  message("IMGUI_DIR = " $ENV{IMGUI_DIR})
else()
  message(FATAL_ERROR "Please define the IMGUI_DIR environment variable.")
endif()

# Assume IMPLOT_DIR is specified as environment variable
if (DEFINED ENV{IMPLOT_DIR} )
  message("IMPLOT_DIR = " $ENV{IMPLOT_DIR})
else()
  message(FATAL_ERROR "Please define the IMPLOT_DIR environment variable.")
endif()

# Define all imgui sources
set(IMGUI_SRCS
  $(IMGUI_DIR)/imgui.cpp
  $(IMGUI_DIR)/imgui_demo.cpp
  $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
  $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
  $(IMGUI_DIR) 
)
