cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  CodeTask
  VERSION 0.1.0
  DESCRIPTION "Small code task project"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----
add_library(
  CodeTask_lib OBJECT source/Window.cpp source/FadingStackedWidget.cpp
                      source/ProgressBarWidget.cpp source/ClockWidget.cpp)

target_include_directories(
  CodeTask_lib ${warning_guard}
  PUBLIC "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>")
target_compile_features(CodeTask_lib PUBLIC cxx_std_20)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

if(WIN32)
  target_link_libraries(CodeTask_lib PUBLIC Qt6::QWindowsIntegrationPlugin)
  target_compile_definitions(CodeTask_lib PUBLIC PLATFORM_WINDOWS)
endif()

if(UNIX AND NOT APPLE)
  target_link_libraries(CodeTask_lib PUBLIC Qt6::QXcbIntegrationPlugin)
  target_compile_definitions(CodeTask_lib PUBLIC PLATFORM_LINUX)
endif()

target_link_libraries(CodeTask_lib PUBLIC Qt6::Core Qt6::Widgets Qt6::Gui)
set_target_properties(CodeTask_lib PROPERTIES AUTOMOC ON)

# ---- Declare executable ----
qt_add_executable(CodeTask_exe source/main.cpp)

target_compile_features(CodeTask_exe PRIVATE cxx_std_20)
target_link_libraries(CodeTask_exe PRIVATE CodeTask_lib)
set_target_properties(CodeTask_exe PROPERTIES WIN32_EXECUTABLE ON OUTPUT_NAME
                                                                  CodeTask)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT CodeTask_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING "Developer mode is intended for developers of CodeTask")
endif()

include(cmake/dev-mode.cmake)
