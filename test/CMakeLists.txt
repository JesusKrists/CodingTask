# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(CodeTaskTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

qt_add_executable(CodeTask_test source/CodeTask_test.cpp)
target_link_libraries(CodeTask_test PRIVATE CodeTask_lib Catch2::Catch2WithMain)
target_compile_features(CodeTask_test PRIVATE cxx_std_20)

catch_discover_tests(CodeTask_test)

# ---- End-of-file commands ----

add_folders(Test)
