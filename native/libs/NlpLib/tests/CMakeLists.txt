cmake_minimum_required(VERSION 3.15)

# Set the project name
project(NlpLibTests)

find_package(Catch2 3 REQUIRED)
# Add Catch2 as a dependency
# include(FetchContent)
# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG v3.4.0 # Use the latest stable version
# )
# FetchContent_MakeAvailable(Catch2)

# Enable testing
enable_testing()

# Add the test executable
add_executable(NlpLibTests
  TokenizerTests.cpp
)

# Link Catch2 to the test executable
target_link_libraries(NlpLibTests PRIVATE NlpLib Catch2::Catch2WithMain)

target_compile_features(NlpLibTests PRIVATE cxx_std_20)

# Discover tests
include(CTest)
include(Catch)
catch_discover_tests(NlpLibTests)