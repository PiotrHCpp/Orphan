cmake_minimum_required(VERSION 3.10)

# Set up project-name variable
project(orphan)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set up shortcut-variable for directory
set(ProjectDir ${CMAKE_CURRENT_SOURCE_DIR})

# Set source file lists
file(GLOB_RECURSE SRC_LIST RELATIVE ${ProjectDir} "src/*.cpp")
file(GLOB_RECURSE TEST_SRC_LIST RELATIVE ${ProjectDir} "tests/*.cpp")

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Create a library from source list
include_directories(src)
add_library(${PROJECT_NAME}-lib ${SRC_LIST})
# target_compile_options(${PROJECT_NAME}-lib PUBLIC -Wall -Wextra -Werror -Wpedantic -Wconversion -Wsign-conversion)

# Build main if main.cpp exists
if(EXISTS ${ProjectDir}/main.cpp)
  add_executable(${PROJECT_NAME} main.cpp)
  # target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror -Wpedantic -Wconversion -Wsign-conversion)
  target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib pthread)
endif()

# Build unit tests
add_executable(${PROJECT_NAME}-ut ${TEST_SRC_LIST})
# target_compile_options(${PROJECT_NAME}-ut PUBLIC -Wall -Wextra -Werror -Wpedantic -Wconversion -Wsign-conversion)
target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib gtest_main)

# Configure ctest
enable_testing()
add_test(NAME ${PROJECT_NAME}Tests COMMAND ${PROJECT_NAME}-ut)
