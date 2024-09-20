cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    CodeTask
    VERSION 0.1.0
    DESCRIPTION "Small code task project"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    CodeTask_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    CodeTask_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(CodeTask_lib PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(CodeTask_lib PRIVATE fmt::fmt)

# ---- Declare executable ----

add_executable(CodeTask_exe source/main.cpp)
add_executable(CodeTask::exe ALIAS CodeTask_exe)

set_property(TARGET CodeTask_exe PROPERTY OUTPUT_NAME CodeTask)

target_compile_features(CodeTask_exe PRIVATE cxx_std_20)

target_link_libraries(CodeTask_exe PRIVATE CodeTask_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT CodeTask_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of CodeTask"
  )
endif()

include(cmake/dev-mode.cmake)
