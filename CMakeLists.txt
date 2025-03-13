cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
# Taken from: https://github.com/raysan5/raylib/blob/master/projects/CMake/CMakeLists.txt 
project(GamePhysics)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(sources ${sources}
  ${CMAKE_CURRENT_SOURCE_DIR}/LinearMath/Vector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/LinearMath/Matrix.cpp
)

add_executable(
  ${CMAKE_PROJECT_NAME}
  main.cpp
  ${sources}
  ${exsources}

)

include_directories(
  ${CMAKE_PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/LinearMath
)

# Tests
enable_testing()
include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(test_sources ${test_sources}
${CMAKE_CURRENT_SOURCE_DIR}/tests/LinearMath/Vector_tests.cpp
${CMAKE_CURRENT_SOURCE_DIR}/tests/LinearMath/Matrix_tests.cpp
)

add_executable(
    ${CMAKE_PROJECT_NAME}_test 
    main_test.cpp
    ${sources}
    ${test_sources}
)

target_link_libraries( 
    ${CMAKE_PROJECT_NAME}_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)
