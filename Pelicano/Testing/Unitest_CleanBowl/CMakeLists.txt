cmake_minimum_required(VERSION 3.14)
project(Unitest_CleanBowl)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  Unitest_CleanBowl
  Unitest_CleanBowl.cpp
  ValidatorPelicano.o
)

target_link_libraries(
  Unitest_CleanBowl
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Unitest_CleanBowl)