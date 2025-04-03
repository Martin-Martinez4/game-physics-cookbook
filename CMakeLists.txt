cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
# Taken from: https://github.com/raysan5/raylib/blob/master/projects/CMake/CMakeLists.txt 
project(GamePhysics)


# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Raylib
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

# Project
set(sources ${sources}
  ${CMAKE_CURRENT_SOURCE_DIR}/LinearMath/Vector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/LinearMath/Matrix.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Geometry2D/Geometry2D.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/QuadTree/QuadTree.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/BVH/BVH.cpp
)

add_executable(
  ${CMAKE_PROJECT_NAME}
  main.cpp
  ${sources}

)


include_directories(
  ${CMAKE_PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/LinearMath
  ${CMAKE_CURRENT_SOURCE_DIR}/Geometry2D
  ${CMAKE_CURRENT_SOURCE_DIR}/QuadTree
  ${CMAKE_CURRENT_SOURCE_DIR}/BVH
)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)


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
${CMAKE_CURRENT_SOURCE_DIR}/tests/Geometry2D/Geometry2D_tests.cpp
${CMAKE_CURRENT_SOURCE_DIR}/tests/BVH/BVH_tests.cpp
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
