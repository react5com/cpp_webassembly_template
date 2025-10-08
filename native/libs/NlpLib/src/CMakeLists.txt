cmake_minimum_required(VERSION 3.15)

# Set the project name
project(NlpLib LANGUAGES CXX)

# Add the library target
add_library(NlpLib STATIC)

set_target_properties(NlpLib PROPERTIES
  DEBUG_POSTFIX "d"
)

# Specify the source files for the library
target_sources(NlpLib
  PRIVATE
    Point.cpp
    Point.hpp
    Tokenizer.cpp
    Tokenizer.hpp
)

# Add embind bindings for WebAssembly builds
if(EMSCRIPTEN)
    target_sources(NlpLib
      PRIVATE
        Tokenizer.embind.cpp
        Point.embind.cpp
    )
    target_compile_options(NlpLib PRIVATE
      #"SHELL:-fsanitize=address"
      #"SHELL:-s ASSERTIONS=2"
    )
    target_link_options(NlpLib
      PUBLIC
        "SHELL:--bind"
        "SHELL:-s ALLOW_MEMORY_GROWTH=1"
        #"SHELL:-s EXIT_RUNTIME=1"
        #"SHELL:-fsanitize=address"
    )
endif()

# target_link_libraries(NlpLib PUBLIC somelibs)

# Specify the include directories
target_include_directories(NlpLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Set C++ standard
target_compile_features(NlpLib PRIVATE cxx_std_20)
