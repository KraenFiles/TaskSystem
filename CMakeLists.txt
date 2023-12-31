cmake_minimum_required(VERSION 3.10)
project (TaskSystem VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  message("Release mode")
  set(RELEASE 1)
  set(TEST_MODE 0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Debug mode")
  set(RELEASE 0)
  set(TEST_MODE 0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Test")
  message("Test mode")
  set(RELEASE 0)
  set(TEST_MODE 1)
else()
  message("Default mode")
  set(RELEASE 0)
  set(TEST_MODE 0)
endif()
      

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
  "include/**.h"
  "include/**.hpp"
  "src/**.cpp"
  "src/**.c"
)

add_executable(TaskSystem ${SOURCES} ${TESTS})

if(RELEASE EQUAL 1)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wextra -Wpedantic -Wall")
  add_definitions(-DRELEASE)
else()
  add_definitions(-DDEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wextra -Wpedantic -Wall")
  if(TEST_MODE EQUAL 1)
  endif()
endif()
      
include_directories(include)
set(SOURCE_DIR src)
set(BUILD_DIR build)
set_target_properties(TaskSystem PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
